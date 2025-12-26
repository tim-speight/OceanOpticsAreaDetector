/*******************************************************
 * @file    RS232TransferHelper.h
 * @date    February 2022
 * @author  Ocean Optics, Inc.
 *
 * This provides an abstraction around the RS232 bus.
 * RS232 is pretty simple once the port is opened and
 * configured, so this mostly just takes care of ensuring
 * that all bytes are sent and received as required.
 *
 * This will effectively block on reads and writes until
 * they are complete.  A non-blocking transfer helper
 * could be created to complement this if there was
 * some need, but it is not clear who would be responsible
 * for delayed reads or retransmits.
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

#ifndef RS232_TRANSFER_HELPER_H
#define RS232_TRANSFER_HELPER_H

#include "common/buses/TransferHelper.h"
#include "native/rs232/RS232.h"

namespace oceandirect {

    class RS232TransferHelper : public TransferHelper {
    public:
        RS232TransferHelper(RS232 *rs232Descriptor);
        virtual ~RS232TransferHelper() = default;

        virtual int receive(std::vector<std::uint8_t> &buffer, unsigned int length);
        virtual int send(const std::vector<std::uint8_t> &buffer, unsigned int length) const;

    protected:
        RS232 *rs232;
    };

}

#endif /* RS232_TRANSFER_HELPER_H */
