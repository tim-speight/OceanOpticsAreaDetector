/*****************************************************
 * @file    ValueNotFoundException.h
 * @date    May 2022
 * @author  Ocean Insight, Inc.
 *
 * This is an exception for use when a value is passed to
 * a method that is not permitted.  This may include
 * specifying a parameter that is out of bounds or of
 * the wrong type.
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

#ifndef OCEANDIRECT_VALUENOTFOUNDEXCEPTION_H
#define OCEANDIRECT_VALUENOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <string>

namespace oceandirect {

    class ValueNotFoundException : public std::runtime_error {
    public:
        ValueNotFoundException(const std::string& error);
    };

}

#endif
