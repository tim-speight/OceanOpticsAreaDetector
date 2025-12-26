/*******************************************************
 * @file    USBInterface.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This is an abstract base class intended to be an interface
 * for USB control objects.  This allows USB devices to
 * be opened generically (just by providing the index of
 * the device on the bus) without any concern for
 * the vendor ID, product ID, or underlying USB implementation.
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

#ifndef USBINTERFACE_H
#define USBINTERFACE_H

#include "common/buses/Bus.h"
#include "native/usb/NativeUSB.h"
#include "native/usb/USB.h"
#include "common/exceptions/IllegalArgumentException.h"

namespace oceandirect {

    class USBInterface : public Bus {
    public:
        USBInterface();
        virtual ~USBInterface();
        virtual USB *getUSBDescriptor() const;
        virtual DeviceLocatorInterface *getLocation() override;
        virtual void setLocation(const DeviceLocatorInterface &location) override;
        virtual BusFamily getBusFamily() const override;
        virtual std::string getStringDescriptor(int index) const override;
        virtual bool open() override;
        virtual void close() override;
        virtual std::vector<XDevice> discovery() override;

    protected:
        USB *usb;
        DeviceLocatorInterface *deviceLocator;
    };

}

#endif /* USBINTERFACE_H */
