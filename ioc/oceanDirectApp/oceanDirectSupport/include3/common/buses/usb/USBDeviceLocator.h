/*******************************************************
 * @file    USBDeviceLocator.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This class encapsulates the information needed to open
 * a device on a USB bus.
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

#ifndef USBDEVICELOCATOR_H
#define USBDEVICELOCATOR_H

#include "common/buses/DeviceLocatorInterface.h"
#include <string>

namespace oceandirect {

    class USBDeviceLocator : public DeviceLocatorInterface {
    public:
        USBDeviceLocator(unsigned long ID);
        virtual ~USBDeviceLocator();

        /* Inherited from DeviceLocatorInterface */
        virtual unsigned long getUniqueLocation() const;
        virtual bool equals(DeviceLocatorInterface &that);
        virtual std::string getDescription();
        virtual BusFamily getBusFamily() const;
        virtual DeviceLocatorInterface *clone() const;

    private:
        unsigned long deviceID;
    };

}

#endif /* USBDEVICELOCATOR_H */
