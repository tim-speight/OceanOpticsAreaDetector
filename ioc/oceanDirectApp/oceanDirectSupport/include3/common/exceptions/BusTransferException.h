/*****************************************************
 * @file    BusTransferException.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This exception should be used when an error is
 * encountered when trying to read from or write to
 * a bus.
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

#ifndef BUSTRANSFEREXCEPTION_H
#define BUSTRANSFEREXCEPTION_H

#include "common/exceptions/BusException.h"

namespace oceandirect {

    class BusTransferException : public BusException {
    public:
        BusTransferException(const std::string &error);
    };

}

#endif /* BUSTRANSFEREXCEPTION_H */
