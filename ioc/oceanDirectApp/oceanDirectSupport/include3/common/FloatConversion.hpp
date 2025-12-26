/*****************************************************
 * @file    FloatConversion.h
 * @date    September 2023
 * @author  Ocean Insight, Inc.
* 
* Provides templated conversion functions for converting between floating point types and the encoding used in OBP2 frames.
* OBP2 encodes floating point values as a sequences of 8 bit integers. The encoding assumes single precision (32 bit i.e. float)
* values so higher precision values supplied will be narrowed implicitly by the encoding. Decoding will widen the values but this
* is OK because a float should be stored without loss of precision...HOWEVER a value supplied that loses precision during encoding
* will not result in the same value if it is subsequently decoded. For example:
* double::epsilon -> encoded -> decoded does not result in double::epsilon because double::epsilon is not representable as a float.
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

#ifndef OCEANDIRECT_FLOAT_CONVERSION_H
#define OCEANDIRECT_FLOAT_CONVERSION_H

#include <vector>
#include <cstdint>
#include <climits>
#include <type_traits>
#include <iterator>

namespace oceandirect {
    namespace floatconvert {

        constexpr auto EightBits = CHAR_BIT;
        constexpr std::uint8_t EightBitsMask = UCHAR_MAX;

        /* Convert a source sequence of std::uint8_t from an encoded type (default to float) to a floating point target type
        */
        template<typename TargetType, typename SourceTypeIterator, typename EncodedType = float>
        TargetType convert(const SourceTypeIterator begin, const SourceTypeIterator end) {

            // enforce a floating point target type
            static_assert(std::is_floating_point<TargetType>::value);
            // enforce the source type of the sequence to be std::uint8_t
            static_assert(std::is_same<std::uint8_t, typename std::iterator_traits<SourceTypeIterator>::value_type>::value);

            EncodedType result(0.0);
            memcpy(&result, &(*begin), sizeof(EncodedType));
            return static_cast<TargetType>(result);
        }

        /* Convert a floating point source type to a vector of std::uint8_t, default encoded as float
        */
        template<typename SourceType, typename EncodedType = float>
        std::vector<std::uint8_t> convert(const SourceType value) {

            const EncodedType v = static_cast<EncodedType>(value);
            const std::uint8_t *encoded = reinterpret_cast<const std::uint8_t*>(&v);

            return std::vector<std::uint8_t>(encoded, encoded + sizeof(EncodedType));
        }

        /* Convert a sequence of std::uint8_t (pointer or vector iterator) to a vector of ResultType.
        * OBP2 frames encode floating point types as float but we typically return doubles so we need the
        * extra type parameter to specify the encoded type.
        */
        template<typename ResultType, typename SourceTypeIterator, typename EncodedType = float>
        ResultType arr_convert(const SourceTypeIterator begin, const SourceTypeIterator end) {

            // enforce the source type of the sequence to be std::uint8_t
            static_assert(std::is_same<std::uint8_t, typename std::iterator_traits<SourceTypeIterator>::value_type>::value);
            // enforce the encoded type and the elements of the result type should be floating point types
            static_assert(std::is_floating_point<EncodedType>::value);
            typedef typename ResultType::value_type ResultElementType;
            static_assert(std::is_floating_point<ResultElementType>::value);

            // encoded type should be float for OBP2
            const auto resultSize = std::distance(begin, end) / sizeof(EncodedType);
            ResultType result(resultSize);

            auto current = begin;
            for (size_t i = 0; i < resultSize; ++i, current += sizeof(EncodedType)) {
                EncodedType conversion(0.0);
                memcpy(&conversion, &(*current), sizeof(EncodedType));
                result[i] = conversion;
            }
            return result;
        }

        /* Convert a sequence of floating point SourceType to a vector of std::uint8_t
        * The default encoding type for OBP2 is float
        */
        template<typename SourceTypeIterator, typename EncodedType = float>
        std::vector<std::uint8_t> arr_convert(const SourceTypeIterator begin, const SourceTypeIterator end) {

            // get the size in bytes of the encoded type, should be a float for OBP2
            const auto encodedTypeSize = sizeof(EncodedType);
            // and work out the length of the result vector
            const auto resultSize = std::distance(begin, end) * encodedTypeSize / sizeof(std::uint8_t);

            std::vector<std::uint8_t> result(resultSize);

            size_t k = 0;
            for (auto current = begin; current < end; ++current) {
                const EncodedType value = static_cast<EncodedType>(*current);
                const std::uint8_t *encoded = reinterpret_cast<const std::uint8_t*>(&value);
                for (size_t i = 0; i < sizeof(EncodedType); ++i, ++k) {
                    result[k] = encoded[i];
                }
            }
            return result;
        }
    }
}

#endif /* OCEANDIRECT_FLOAT_CONVERSION_H */
