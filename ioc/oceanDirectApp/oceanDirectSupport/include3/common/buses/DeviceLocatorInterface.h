/*****************************************************
 * @file    DeviceLocatorInterface.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * DeviceLocatorInterface provides a base interface for
 * classes that allow the location of a device to be
 * specified in a bus-specific way.  For instance, a
 * USB DeviceLocator might include a device path or
 * index, and a socket DeviceLocator might include an
 * IP address and port number.  This allows
 * devices that cannot be identified by probing to still
 * be found easily.
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

#ifndef DEVICELOCATORINTERFACE_H
#define DEVICELOCATORINTERFACE_H

#include <string>
#include "common/buses/BusFamily.h"

namespace oceandirect {

    class DeviceLocatorInterface {
    public:
        virtual ~DeviceLocatorInterface() = 0;

        /**
         * Get a unique identifier for this location.  This can be any value
         * as long as it is globally unique.
         */
        virtual unsigned long getUniqueLocation() const = 0;

        /**
         * Determine whether this DeviceLocator refers to the same device
         * as another.
         */
        virtual bool equals(DeviceLocatorInterface &that) = 0;

        /**
         * Get a human-readable string that describes the location
         */
        virtual std::string getDescription() = 0;

        /**
         * Get a description of the type of bus that the device is associated with
         */
        virtual BusFamily getBusFamily() const = 0;

        /* Get an exact copy of this instance */
        virtual DeviceLocatorInterface *clone() const = 0;
    };

    /* Default implementation for (otherwise) pure virtual destructor */
    inline DeviceLocatorInterface::~DeviceLocatorInterface() {}

}

#endif /* DEVICELOCATORINTERFACE_H */
