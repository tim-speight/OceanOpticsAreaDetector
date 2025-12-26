/*****************************************************
 * @file    ProtocolHint.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * Hints are used to identify particular characteristics about
 * protocol Transfer objects.  A hint may be used to indicate
 * to a bus some detail it needs about making a transfer, e.g.
 * what endpoint would be appropriate for USB.  Note that the
 * bus (or its helpers) are under no obligation to respect hints.
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

#ifndef OCEANDIRECT_PROTOCOLHINT_H
#define OCEANDIRECT_PROTOCOLHINT_H

#include "common/OceanDirect.h"
#include <string>

namespace oceandirect {

    class ProtocolHint {
    public:
        ProtocolHint(int id, std::string desc);

        /* For derived classes that will fill in their own values
         * and for containers to be able to initialize themselves.
         * This does not set any meaningful values and should not be
         * relied on to create a proper instance.
         */
        ProtocolHint();

        virtual ~ProtocolHint();
        std::string getDescription();
        int getID() const;

        /* Overloading the equality operator so that this can be
         * used as a key for hash_map associations without the actual
         * key objects having to be identical.
         */
        bool operator==(const ProtocolHint &that);

    protected:
        int id;
        std::string description;
    };

}

#endif /* OCEANDIRECT_PROTOCOLHINT_H */

