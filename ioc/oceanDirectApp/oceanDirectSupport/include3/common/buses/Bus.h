/*****************************************************
 * @file    Bus.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This provides a base class for all sorts of buses.  A bus
 * is a mechanism for transferring a stream of data from one
 * point to another.  The bus does not concern itself with the
 * contents of the data stream.  At most, it may use hints to
 * determine how a particular message will be moved if this
 * is necessary to complete the operation.
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

#ifndef OCEANDIRECT_BUS_H
#define OCEANDIRECT_BUS_H

//#include "common/protocols/ProtocolHint.h"
//#include "common/buses/TransferHelper.h"
#include "common/OceanDirect.h"
#include "common/buses/BusFamily.h"
//#include "common/buses/DeviceLocatorInterface.h"
//#include "common/exceptions/IllegalArgumentException.h"
#include <vector>
#include <cstdint>
namespace oceandirect {
    /*
    * Design note: adding the supported protocols here as part of the move to a simpler design.
    * The buses and protocols supported will always be a well-defined and short list that will
    * hardly (if ever) change. The anticipated buses and protocols can be declared in advance
    * and implemented at a later date making the transition more of an incremental process.
    */
    namespace oceanBinaryProtocol {
        class OBP2Transaction;
        
    }
    using oceanBinaryProtocol::OBP2Transaction;

    class TransferHelper;
    class ProtocolHint;
    class DeviceLocatorInterface;

    class Bus {
    public:
        virtual ~Bus() = default;
        virtual TransferHelper *getHelper(const std::vector<ProtocolHint *> &hints) const = 0;
        virtual BusFamily getBusFamily() const = 0;
        /* Associate this Bus instance with a particular device location.
         * This MUST be done before open or close can be used.
         */
        virtual void setLocation(const DeviceLocatorInterface &location) = 0;
        virtual bool open() = 0;
        virtual void close() = 0;
        virtual std::vector<XDevice> discovery() = 0;
        virtual DeviceLocatorInterface *getLocation() = 0;
        virtual std::string getStringDescriptor(int index) const = 0;

        // The declaration of a receive and send slightly departs from the design document but the
        // visitor design pattern still applies
        virtual int receive(OBP2Transaction * transaction, std::vector<std::uint8_t>&buffer) = 0;
        virtual int send(OBP2Transaction * transaction, const std::vector<std::uint8_t>&buffer) const = 0;
    };

}

#endif
