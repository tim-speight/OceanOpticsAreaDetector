/*****************************************************
 * @file    bitutils.h
 * @date    January 2022
 * @author  Ocean Optics, Inc.
 *
 * General purpose bit utilities that are used in multiples places.
 */
/************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2022] Ocean Insight Incorporated
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

#ifndef OCEAN_DIRECT_BIT_UTILS_H
#define OCEAN_DIRECT_BIT_UTILS_H

#include <vector>
#include "common/OceanDirect.h"


namespace oceandirect {
    // Convert an unsigned 32 bit integer to a byte vector with LSB first
    std::vector<std::uint8_t> ToByteVector(const std::uint32_t x);

    // Convert a byte vector to 32 bit integer assuming LSB first
    std::uint32_t FromByteVector(const std::vector<std::uint8_t> &in);

    // Return the result of setting or unsetting the specified bit of in.
    std::uint32_t SetBit(const unsigned char bit, const std::uint32_t in, const bool setBit);

    // Return true if the bit in the input is set
    bool IsBitSet(const unsigned char bit, const std::uint16_t in);
    bool IsBitSet(const unsigned char bit, const std::uint32_t in);
}
#endif /* OCEAN_DIRECT_BIT_UTILS_H */
