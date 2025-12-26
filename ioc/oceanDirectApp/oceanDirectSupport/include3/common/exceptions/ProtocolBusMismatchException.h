/*****************************************************
 * @file    ProtocolBusMismatchException.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This exception should be used when a protocol is
 * specified, but the bus and protocol are not suited to
 * each other (e.g. there is no bus helper for the hints
 * the protocol can provide).
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

#ifndef PROTOCOLBUSMISMATCHEXCEPTION_H
#define PROTOCOLBUSMISMATCHEXCEPTION_H

#include "common/exceptions/ProtocolException.h"

namespace oceandirect {

    class ProtocolBusMismatchException : public ProtocolException {
    public:
        ProtocolBusMismatchException(const std::string &error);
    };

}

#endif /* PROTOCOLBUSMISMATCHEXCEPTION_H */
