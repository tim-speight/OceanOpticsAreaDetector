/*****************************************************
 * @file    BusFamilies.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This provides a way to get references to different kinds of buses
 * (e.g. USB, Ethernet, serial) generically.
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

#ifndef BUSFAMILIES_H
#define BUSFAMILIES_H

#include "common/buses/BusFamily.h"
#include <vector>

namespace oceandirect {

    class USBBusFamily : public BusFamily {
    public:
        USBBusFamily();
        virtual ~USBBusFamily();
    };

    class EthernetBusFamily : public BusFamily {
    public:
        EthernetBusFamily();
        virtual ~EthernetBusFamily();
    };

    class RS232BusFamily : public BusFamily {
    public:
        RS232BusFamily();
        virtual ~RS232BusFamily();
    };
    
    class TCPIPv4BusFamily : public BusFamily {
    public:
        TCPIPv4BusFamily();
        virtual ~TCPIPv4BusFamily();
    };
    
    class UDPIPv4BusFamily : public BusFamily {
    public:
        UDPIPv4BusFamily();
        virtual ~UDPIPv4BusFamily();
    };

    class BusFamilies {
    public:
        const USBBusFamily USB;
        const EthernetBusFamily ETHERNET;
        const RS232BusFamily RS232;
        const TCPIPv4BusFamily TCPIPv4;
        const UDPIPv4BusFamily UDPIPv4;

        BusFamilies();
        ~BusFamilies();
        std::vector<BusFamily *> getAllBusFamilies();
    };

}

#endif /* BUSFAMILIES_H */
