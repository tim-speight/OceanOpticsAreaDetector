/*******************************************************
 * @file    TCPIPv4SocketTransferHelper.h
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

#ifndef OCEANDIRECT_TCP_IP_V4_SOCKET_TRANSFER_HELPER_H
#define OCEANDIRECT_TCP_IP_V4_SOCKET_TRANSFER_HELPER_H

#include "common/buses/TransferHelper.h"
#include "native/network/Socket.h"

namespace oceandirect {
    class TCPIPv4SocketTransferHelper : public TransferHelper {
    public:
        TCPIPv4SocketTransferHelper(Socket *sock);
        virtual ~TCPIPv4SocketTransferHelper();
        
        virtual int receive(std::vector<std::uint8_t> &buffer, unsigned int length);
        virtual int send(const std::vector<std::uint8_t> &buffer, unsigned int length) const;
        
    protected:
        Socket *socket;
    };
}

#endif /* OCEANDIRECT_TCP_IP_V4_SOCKET_TRANSFER_HELPER_H */
