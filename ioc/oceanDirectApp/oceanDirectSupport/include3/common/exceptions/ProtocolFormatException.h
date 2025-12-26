/*****************************************************
 * @file    ProtocolFormatException.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This exception should be used when a protocol message
 * cannot be decoded, fails a checksum, or otherwise is
 * out of spec.  This may indicate that the driver is now
 * out of synch with this code and that measures should be
 * taken to re-establish communications.
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

#ifndef PROTOCOLFORMATEXCEPTION_H
#define PROTOCOLFORMATEXCEPTION_H

#include "common/exceptions/ProtocolException.h"

namespace oceandirect {

    class ProtocolFormatException : public ProtocolException {
    public:
        ProtocolFormatException(const std::string &error);
    };

}

#endif /* PROTOCOLFORMATEXCEPTION_H */
