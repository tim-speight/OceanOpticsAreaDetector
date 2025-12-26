/*****************************************************
 * @file    Exchange.h
 * @date    January 2022
 * @author  Ocean Optics, Inc.
 *
 * This is simply an interface that other classes will
 * extend to have a common transfer() and getHints methods
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

#ifndef OCEANDIRECT_EXCHANGE_H
#define OCEANDIRECT_EXCHANGE_H

#include <vector>
#include "common/buses/TransferHelper.h"
#include "common/protocols/ProtocolHint.h"
#include "common/exceptions/ProtocolException.h"

namespace oceandirect {

    class Exchange {
    public:
        Exchange();
        Exchange(std::vector<ProtocolHint *> *hints);
        virtual ~Exchange();

        virtual void transferToDevice(TransferHelper *helper) = 0;
        virtual std::vector<std::uint8_t> transferFromDevice(TransferHelper *helper) = 0;
        virtual const std::vector<ProtocolHint *> &getHints();

    protected:
        std::vector<ProtocolHint *> *hints;
    };

}

#endif /* OCEANDIRECT_EXCHANGE_H */

