/*****************************************************
 * @file    Protocol.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This is a simple identifier cookie that will allow two
 * objects to agree on whether they support a given command
 * set (protocol).  Each will hold Protocol objects that they
 * can then compare to see if they agree.  This allows a loose
 * binding between sets of Exchanges (elsewhere called protocols)
 * and buses.
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

#ifndef OCEANDIRECT_PROTOCOL_H
#define OCEANDIRECT_PROTOCOL_H

#include "common/protocols/ProtocolFamily.h"

namespace oceandirect {

    class Protocol {
    public:
        Protocol(int id);
        /* Copy constructor */
        Protocol(Protocol const &that);
        virtual ~Protocol();
        bool equals(Protocol const &that);

        virtual ProtocolFamily getProtocolFamily() = 0;

    protected:
        /* Protected for derived classes to use. */
        Protocol();
        int id;
    };

}

#endif
