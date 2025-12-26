/*****************************************************
 * @file    TransferHelper.h
 * @date    January 2022
 * @author  Ocean Optics, Inc.
 *
 * This is effectively an interface for wrappers around bus
 * activity.  These wrappers may be selected from a Bus
 * based on certain hints provided by a Protocol or its
 * various Exchanges.  All that this specifies is that a
 * given object must be able to send() and receive() data
 * across its particular (encapsulated) Bus.
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

#ifndef OCEANDIRECT_TRANSFER_HELPER_H
#define OCEANDIRECT_TRANSFER_HELPER_H

#include <vector>
#include "common/OceanDirect.h"
#include "common/exceptions/BusTransferException.h"

namespace oceandirect {

    class TransferHelper {
    public:
        TransferHelper();
        virtual ~TransferHelper();
        virtual int receive(std::vector<std::uint8_t> &buffer, unsigned int length) = 0;
        virtual int send(const std::vector<std::uint8_t> &buffer, unsigned int length) const = 0;
    };

}

#endif /*OCEANDIRECT_TRANSFER_HELPER_H*/
