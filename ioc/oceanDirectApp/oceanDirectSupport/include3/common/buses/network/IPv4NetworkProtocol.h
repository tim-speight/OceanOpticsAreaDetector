/*******************************************************
 * @file    IPv4NetworkProtocol.h
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

#ifndef OCEANDIRECT_IPV4NETWORKPROTOCOL_H
#define OCEANDIRECT_IPV4NETWORKPROTOCOL_H

#include <string>
#include <vector>

namespace oceandirect {
    class IPv4NetworkProtocol {
    public:
        virtual ~IPv4NetworkProtocol();
        virtual std::string getName() const;
        virtual bool equals(const IPv4NetworkProtocol &that) const;

    protected:
        IPv4NetworkProtocol(std::string name, int id);

    private:
        std::string protocolName;
        int type;
    };
    
    class TCP_IPv4 : public IPv4NetworkProtocol {
    public:
        TCP_IPv4();
        virtual ~TCP_IPv4();
    };
    
    class UDP_IPv4 : public IPv4NetworkProtocol {
    public:
        UDP_IPv4();
        virtual ~UDP_IPv4();
    };

    class IPv4NetworkProtocols {
    public:
        const TCP_IPv4 TCP_IP4;
        const UDP_IPv4 UDP_IP4;

        IPv4NetworkProtocols();
        ~IPv4NetworkProtocols();
        std::vector<IPv4NetworkProtocol *> getAllIPv4NetworkProtocols();
    };
}

#endif /* OCEANDIRECT_IPV4NETWORKPROTOCOL_H */

