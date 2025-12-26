/*****************************************************
 * @file    Transfer.h
 * @date    January 2022
 * @author  Ocean Optics, Inc.
 *
 * The Transfer class captures a simplex
 * data transfer to or from a device.  At this
 * level, there is no notion of a particular bus,
 * just data, length, and direction.
 *
 * The bus aspects are encapsulated in a "helper"
 * object that must be provided when the Transfer
 * is executed.  The helper must provide send() and
 * receive() methods taking a buffer and length
 * only.  All of the details in getting the transfer to
 * or from the other end must be handled by the helper.
 * The helper is expected to be created by some aspect
 * of the driver for the device in question.  It contains
 * information about the connection and the particulars
 * about routing data in and out.
 *
 * Note that the Transfer class is completely orthagonal to any
 * particular protocol.  It is expected that a protocol may be
 * built up as a collection of related Transfer types.
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

#ifndef OCEANDIRECT_TRANSFER_H
#define OCEANDIRECT_TRANSFER_H

#include <vector>
#include "common/protocols/Exchange.h"
#include "common/protocols/ProtocolHint.h"
#include "common/public/SpectrumWithMetadata.h"

typedef unsigned int direction_t;

namespace oceandirect {

    class Transfer : public Exchange {

    public:

        /* Note that the size of the provided buffer and the specified length
         * of the transfer itself do not need to agree.  If the transfer requires
         * more space than the buffer provides, the buffer will be resized.
         * If the buffer is created larger than is needed, only the given length
         * will be sent or received.  This allows for some freedom in buffer
         * management.
         */
        Transfer(std::vector<ProtocolHint *> *hints, std::vector<std::uint8_t>&& buff, direction_t dir, unsigned int len);

        virtual ~Transfer();
        virtual void transferToDevice(TransferHelper *helper) override;
        virtual std::vector<std::uint8_t> transferFromDevice(TransferHelper *helper) override;

        static const direction_t TO_DEVICE;
        static const direction_t FROM_DEVICE;

    protected:
        Transfer();
        void checkBufferSize();

        std::vector<std::uint8_t> buffer;
        direction_t direction;
        unsigned int length;

        SpectrumWithMetadata *formattedMetadata;
    };

}

#endif /* OCEANDIRECT_TRANSFER_H */

