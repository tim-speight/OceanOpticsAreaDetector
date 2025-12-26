/*****************************************************
 * @file    NumberFormatException.h
 * @date    March 2018
 * @author  Ocean Optics, Inc.
 *
 * This is an exception for use when a string is to be
 * parsed into a number but the string does not contain
 * a recognizable number.
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

#ifndef OCEANDIRECT_NUMBERFORMATEXCEPTION_H
#define OCEANDIRECT_NUMBERFORMATEXCEPTION_H

#include <stdexcept>
#include <string>

namespace oceandirect {

    class NumberFormatException : public std::runtime_error {
    public:
        NumberFormatException(const std::string &error);
    };

}

#endif
