/*****************************************************
 * @file    ProtocolHelper.h
 * @date    July 2018
 * @author  Ocean Optics, Inc.
 *
 * Feature instances may look up an implementation object
 * that matches a particular Protocol.  All such implementations
 * should in some way derive from ProtocolHelper so that
 * Feature's look up mechanism can return them.  It is
 * expected that each Feature will have a corresponding
 * interface at the Protocol layer; those interface classes
 * should derive from this class, and their implementations
 * will thus extend this as well.
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

#ifndef OCEANDIRECT_PROTOCOLHELPER_H
#define OCEANDIRECT_PROTOCOLHELPER_H

#include "common/protocols/Protocol.h"

namespace oceandirect {

    class ProtocolHelper {
    public:
        ProtocolHelper(Protocol *proto);
        virtual ~ProtocolHelper();
        Protocol &getProtocol();

    protected:
        /* Protected for derived classes to use. */
        ProtocolHelper();
        Protocol *protocol;
    };

}

#endif
