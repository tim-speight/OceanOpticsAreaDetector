/*******************************************************
 * @file    UDPSocketBus.h
 * @date    February 2019
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

#ifndef OCEANDIRECT_UDPSOCKETBUS_H
#define OCEANDIRECT_UDPSOCKETBUS_H

#include "common/buses/Bus.h"
#include "common/exceptions/IllegalArgumentException.h"
#include "native/network/Socket.h"
#include <vector>

namespace oceandirect {
    class UDPSocketBus : public Bus {
    public:
		UDPSocketBus();
        virtual ~UDPSocketBus();
        
        virtual Socket *getSocketDescriptor();
        
        virtual BusFamily getBusFamily() const override;
        
        virtual void setLocation(const DeviceLocatorInterface &location) override;
        virtual DeviceLocatorInterface *getLocation() override;
        virtual TransferHelper *getHelper(
                const std::vector<ProtocolHint *> &hints) const override;
        virtual std::string getStringDescriptor(int index) const override;
        
        /* Pure virtual methods */
        virtual bool open() override;
        virtual void close() override;
        virtual std::vector<XDevice> discovery() override;

        int receive(OBP2Transaction* transaction, std::vector<std::uint8_t>& buffer) override;
        int send(OBP2Transaction* transaction, const std::vector<std::uint8_t>& buffer) const override;

    protected:
        void addHelper(ProtocolHint *hint, TransferHelper *helper);
        void clearHelpers();
        
        Socket *socket;
        DeviceLocatorInterface *deviceLocator;
        
        /* These vectors should really be in a map, but that didn't want to
         * work easily.  Since there will likely be about 2 entries in here,
         * storing in a pair of vectors for now won't hurt anything.
         */
        std::vector<ProtocolHint *> helperKeys;
        std::vector<TransferHelper *> helperValues;
    };
}

#endif /* OCEANDIRECT_UDPSOCKETBUS_H */
