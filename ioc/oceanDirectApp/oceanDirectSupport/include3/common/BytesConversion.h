 /*****************************************************
  * @file    BytesConversion.h
  * @date    February 2022
  * @author  Ocean Optics, Inc.
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

#ifndef OCEANDIRECT_BYTES_CONVERSION_H
#define OCEANDIRECT_BYTES_CONVERSION_H

#include <vector>
#include "common/OceanDirect.h"

using namespace std;

namespace oceandirect {

    class BytesConversion {
    public:
        /* Convert a 4 bytes array into unsigned long */
        static unsigned long fromU32BytesToULong(const std::vector<std::uint8_t> &data);

        /* Convert byte to bool. 0 is false otherwise its true */
        static bool fromByteToBool(std::uint8_t data);

        /* Convert 4 bytes data into float. */
        static float fromFourBytesToFloat(const std::vector<std::uint8_t> &data);
    };
}

#endif /* OCEANDIRECT_BYTES_CONVERSION_H */
