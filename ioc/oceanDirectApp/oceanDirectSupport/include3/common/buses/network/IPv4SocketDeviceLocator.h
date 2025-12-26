/*******************************************************
 * @file    IPv4SocketDeviceLocator.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2020] Ocean Insight Incorporated
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

#ifndef OCEANDIRECT_IPV4SOCKETDEVICELOCATOR_H
#define OCEANDIRECT_IPV4SOCKETDEVICELOCATOR_H

#include "common/buses/DeviceLocatorInterface.h"
#include "common/buses/network/IPv4NetworkProtocol.h"
#include <string>

namespace oceandirect {
    class IPv4SocketDeviceLocator : public DeviceLocatorInterface {
    public:
        IPv4SocketDeviceLocator(const IPv4NetworkProtocol &proto, std::string ip,
            int portNumber);
        virtual ~IPv4SocketDeviceLocator();
        
        std::string getIPv4Address();
        int getPort();
        IPv4NetworkProtocol getIPv4NetworkProtocol();
        
        /* Inherited from DeviceLocatorInterface */
        virtual unsigned long getUniqueLocation() const;
        virtual bool equals(DeviceLocatorInterface &that);
        virtual std::string getDescription();
        virtual BusFamily getBusFamily() const;
        virtual DeviceLocatorInterface *clone() const;
        
    protected:
        unsigned long computeLocationHash();
        
        IPv4NetworkProtocol protocol;
        std::string ipAddr;
        int port;
        unsigned long locationHash;
    };
}

#endif /* OCEANDIRECT_IPV4SOCKETDEVICELOCATOR_H */

