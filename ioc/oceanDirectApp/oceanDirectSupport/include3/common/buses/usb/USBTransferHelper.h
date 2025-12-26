/*******************************************************
 * @file    USBTransferHelper.h
 * @date    January 2022
 * @author  Ocean Optics, Inc.
 *
 * This is a TransferHelper intended for USB communications.
 * Each USBTransferHelper must specify a sending and
 * receiving endpoint, which will tend to vary according to
 * the type of data transfer being conducted.  This adapts
 * the send() and receive() methods required of a TransferHelper
 * according to a particular type of transfer, which may be
 * inferred from a ProtocolHint.
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

#ifndef USB_TRANSFER_HELPER_H
#define USB_TRANSFER_HELPER_H

#include "common/buses/TransferHelper.h"
#include "native/usb/USB.h"

namespace oceandirect {

    class USBTransferHelper : public TransferHelper {
    public:
        USBTransferHelper(USB *usbDescriptor, int sendEndpoint, int receiveEndpoint);
        USBTransferHelper(USB *usbDescriptor);
        virtual ~USBTransferHelper();

        virtual int receive(std::vector<std::uint8_t> &buffer, unsigned int length);
        virtual int send(const std::vector<std::uint8_t> &buffer, unsigned int length) const;

    protected:
        USB *usb;
        int sendEndpoint;
        int receiveEndpoint;
    };

}

#endif /* USB_TRANSFER_HELPER_H */
