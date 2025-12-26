/*****************************************************
 * @file    IntegerConversion.h
 * @date    September 2023
 * @author  Ocean Insight, Inc.
 * 
 * Provides templated conversion functions for converting between integer types and the encoding used in OBP2 frames.
 * OBP2 encodes integer values as a sequences of 8 bit integers with LSB first.
 * 
 */
 /************************************************************************
  *
  * OCEAN INSIGHT CONFIDENTIAL
  * __________________
  *
  * [2018] - [2023] Ocean Insight Incorporated
  * All Rights Reserved.
  *
  * NOTICE:  All information contained herein is, and remains
  * the property of Ocean Insight Incorporated and its suppliers,
  * if any.  The intellectual and technical concepts contained
  * herein are proprietary to Ocean Insight Incorporated
  * and its suppliers and may be covered by U.S. and Foreign Patents,
  * patents in process, and are protected by trade secret or copyright law.
  * Dissemination of this information or reproduction of this material
  * is strictly forbidden unless prior written permission is obtained
  * from Ocean Insight Incorporated.
  *
  **************************************************************************/

#ifndef OCEANDIRECT_INTEGER_CONVERSION_H
#define OCEANDIRECT_INTEGER_CONVERSION_H

#include <vector>
#include <cstdint>
#include <climits>
#include <type_traits>
#include <iterator>

namespace oceandirect {
    namespace intconvert {

        constexpr auto EightBits = CHAR_BIT;
        constexpr std::uint8_t EightBitsMask = UCHAR_MAX;

        /* Convert a sequence of std::uint8_t to an integer TargetType. The sequence is accessed by iterator.
        */
        template<typename TargetType, typename SourceTypeIterator>
        TargetType convert(const SourceTypeIterator begin, const SourceTypeIterator end) {

            // enforce the TargetType and SourceTypeIterator requirements
            static_assert(std::is_integral<TargetType>::value);
            static_assert(std::is_same<std::uint8_t, typename std::iterator_traits<SourceTypeIterator>::value_type>::value);

            TargetType result(0);
            int shift = 0;
            for (auto it = begin; it < end; ++it, shift += EightBits) {
                result |= static_cast<TargetType>(*it) << shift;
            }
            return result;
        }

        /* Convert a value of integer SourceType to a vector of std::uint8_t
        */
        template<typename SourceType>
        std::vector<std::uint8_t> convert(const SourceType t) {

            // enforce the integer SourceType requirement
            static_assert(std::is_integral<SourceType>::value);

            std::vector<std::uint8_t> result(sizeof(SourceType));
            for (size_t i = 0, shift = 0; i < sizeof(SourceType); ++i, shift += EightBits) {
                result.at(i) = ((t >> shift) & EightBitsMask);
            }
            return result;
        }

        /* Convert a sequence of std::uint8_t to a vector of integer TargetType
        *  We need the extra template argument to differentiate this from another convert that only
        *  differs in the return type.
        */
        template<typename ResultType, typename SourceTypeIterator>
        ResultType arr_convert(const SourceTypeIterator begin, const SourceTypeIterator end) {

            // enforce the requirements on the template type arguments
            typedef typename ResultType::value_type ResultElementType;
            static_assert(std::is_integral<ResultElementType>::value);
            static_assert(std::is_same<std::uint8_t, typename std::iterator_traits<SourceTypeIterator>::value_type>::value);

            // get the size in bytes of the target type
            const auto targetTypeSize = sizeof(ResultElementType);
            // and work out the length of the result vector
            const auto resultSize = std::distance(begin, end) / targetTypeSize;

            std::vector<ResultElementType> result(resultSize);
            auto current = begin;
            for (auto out = result.begin(); out < result.end(); ++out) {
                *out = 0;
                for (size_t i = 0, shift = 0; i < targetTypeSize; ++i, shift += EightBits, ++current) {
                    *out |= static_cast<ResultElementType>(*current) << shift;
                }
            }
            return result;
        }

        /* Convert a sequence of integer SourceType to a vector of std::uint8_t
        */
        template<typename SourceTypeIterator>
        std::vector<std::uint8_t> arr_convert(const SourceTypeIterator begin, const SourceTypeIterator end) {

            // enforce the type requirements
            typedef typename std::iterator_traits<SourceTypeIterator>::value_type SourceType;
            static_assert(std::is_integral<SourceType>::value);

            // get the size in bytes of the source type
            const auto sourceTypeSize = sizeof(SourceType);
            // and work out the length of the result vector
            const auto resultSize = std::distance(begin, end) * sourceTypeSize / sizeof(std::uint8_t);

            std::vector<std::uint8_t> result(resultSize);

            size_t k = 0;
            for (auto current = begin; current < end; ++current) {
                for (size_t i = 0, shift = 0; i < sourceTypeSize; ++i, shift += EightBits, ++k) {
                    result.at(k) = ((*current >> shift) & EightBitsMask);
                }
            }
            return result;
        }

    }
}

#endif /* OCEANDIRECT_INTEGER_CONVERSION_H */
