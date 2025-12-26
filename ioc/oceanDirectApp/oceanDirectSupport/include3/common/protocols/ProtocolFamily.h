/*****************************************************
 * @file    ProtocolFamily.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This provides a way to describe different kinds
 * protocols (e.g. OOI, OBP) generically.
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

#ifndef OCEANDIRECT_PROTOCOLFAMILY_H
#define OCEANDIRECT_PROTOCOLFAMILY_H

#include <string>

namespace oceandirect {
    class ProtocolFamily {
    public:
        virtual ~ProtocolFamily();
        virtual std::string getName();
        virtual bool equals(const ProtocolFamily &that);
        virtual unsigned short getType();

    protected:
        ProtocolFamily(std::string name, unsigned short id);

    private:
        std::string protocolName;
        unsigned short type;
    };
}

#endif
