/*****************************************************
 * @file    OceanDirect.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This provides some project-wide constants and definitions.
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

#ifndef OCEANDIRECT_H
#define OCEANDIRECT_H

#include <string>

//typedef unsigned char byte;

class XDevice
{
public:
    XDevice() {};
    XDevice(std::string x1, std::string x2, std::uint32_t portNum) {
        serial_number = x1;
        ip_addr       = x2;
        portNumber    = portNum;
    }

    XDevice(const XDevice &copy) {
        serial_number = copy.serial_number;
        ip_addr       = copy.ip_addr;
        portNumber    = copy.portNumber;
    }

    void operator=(const XDevice &right) {
        serial_number = right.serial_number;
        ip_addr       = right.ip_addr;
        portNumber    = right.portNumber;
    }

    bool operator< (const XDevice &right) const
    {
        return serial_number < right.serial_number;
    }
    std::string ip_addr;
    std::string serial_number;
    std::uint32_t portNumber;
};

#ifdef WINDOWS
/* Visual studio does not implement declared exception
 * specification but accepts it with a warning.  This
 * suppresses the warning (4290).
 */
#pragma warning( disable : 4290 )

//std::string convert2s(wstring wconv) {
//}

#endif /* WINDOWS */

#endif /* OCEANDIRECT_H */
