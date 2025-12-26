/*******************************************************
 * @file    RS232Interface.h
 * @date    April 2018
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

#ifndef RS232INTERFACE_H
#define RS232INTERFACE_H

#include "common/buses/Bus.h"
#include "native/rs232/NativeRS232.h"
#include "native/rs232/RS232.h"
#include "common/exceptions/IllegalArgumentException.h"

namespace oceandirect {

    class RS232Interface : public Bus {
    public:
        RS232Interface();
        virtual ~RS232Interface();
        virtual RS232 *getRS232Descriptor();
        virtual DeviceLocatorInterface *getLocation() override;
        virtual void setLocation(const DeviceLocatorInterface &location) override;
        virtual BusFamily getBusFamily() const override;
        // Default empty response for now
        virtual std::string getStringDescriptor(int index) const override { return "";}
        
        /* Pure virtual methods */
        virtual TransferHelper *getHelper(
                const std::vector<ProtocolHint *> &hints) const override;
        virtual bool open() override;
        virtual void close() override;
        virtual std::vector<XDevice> discovery() override;

    protected:
        RS232 *rs232;
        DeviceLocatorInterface *deviceLocator;
    };

}

#endif /* RS232INTERFACE_H */
