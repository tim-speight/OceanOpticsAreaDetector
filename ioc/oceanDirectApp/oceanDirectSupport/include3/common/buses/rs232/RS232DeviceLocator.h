/*******************************************************
 * @file    RS232DeviceLocator.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This class encapsulates the information needed to open
 * a device on an RS232 bus.
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

#ifndef RS232DEVICELOCATOR_H
#define RS232DEVICELOCATOR_H

#include "common/buses/DeviceLocatorInterface.h"
#include <string>

namespace oceandirect {

    class RS232DeviceLocator : public DeviceLocatorInterface {
    public:
        RS232DeviceLocator(std::string devicePath, int baudRate);
        virtual ~RS232DeviceLocator();

        std::string &getDevicePath();
        int getBaudRate();

        /* Inherited from DeviceLocatorInterface */
        virtual unsigned long getUniqueLocation() const;
        virtual bool equals(DeviceLocatorInterface &that);
        virtual std::string getDescription();
        virtual BusFamily getBusFamily() const;
        virtual DeviceLocatorInterface *clone() const;

    private:
        void computeLocationHash();
        std::string devicePath;
        int baudRate;
        unsigned long locationHash;
    };

}

#endif /* RS232DEVICELOCATOR_H */
