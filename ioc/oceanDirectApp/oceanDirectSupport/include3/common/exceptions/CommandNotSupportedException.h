/*****************************************************
 * @file    CommandNotSupportedException.h
 * @date    March 2020
 * @author  Ocean Insight, Inc.
 *
 * This is a base class for a family of exceptions that
 * arise from errors in protocols.  These may be thrown
 * at the protocol layer, and all exceptions thrown at
 * that layer must extend this class so that they can be
 * uniformly handled.
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

#ifndef OCEANDIRECT_COMMANDNOTSUPPORTEDEXCEPTION_H
#define OCEANDIRECT_COMMANDNOTSUPPORTEDEXCEPTION_H

#include <stdexcept>
#include <string>

namespace oceandirect {

    class CommandNotSupportedException :
        public std::runtime_error {
    public:
        CommandNotSupportedException(const std::string &error);
    };
}

#endif
