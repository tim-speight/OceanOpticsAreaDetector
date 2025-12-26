/*****************************************************
 * @file    DeviceLocationProberInterface.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * DeviceLocatorInterface provides a base interface for
 * classes that allow the location of a device to be
 * probed in a bus-specific way.
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

#ifndef DEVICELOCATIONPROBERINTERFACE_H
#define DEVICELOCATIONPROBERINTERFACE_H

#include <vector>
#include "common/buses/DeviceLocatorInterface.h"

namespace oceandirect {

    class DeviceLocationProberInterface {
    public:
        virtual ~DeviceLocationProberInterface() = default;

        /* Report how many devices of this type are available */
        virtual std::vector<DeviceLocatorInterface *> probeDevices() = 0;
    };
}
#endif /* DEVICELOCATIONPROBERINTERFACE_H */
