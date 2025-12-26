#ifndef LH_EXCEPTION_H
#define LH_EXCEPTION_H
/*******************************************************
 * @file    LHException.h
 * @date    March 2024
 * @author  Ocean Insight, Inc.
 *
 * LHException is the class used to propagate exceptions up to the level of the API.
 * The exception carries an enum value that is exposed at the API level that has
 * a documented explanation of what the error code means. This design associates
 * the exception directly with the error code in a way that was done manually previously.
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2024] Ocean Insight Incorporated
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
#include <exception>
#include "lighthouse/api/LHErrorCode.h"
#include "lighthouse/api/LighthouseDllDecl.h"
namespace oceandirect {
    namespace api {
        class LIGHTHOUSE_DLL_DECL LHException : std::exception {
            LHErrorCode errorCode;
        public:
            // we always want to have the exception associated with an error code so force it
            // to be constructed with a code
            LHException() = delete;
            LHException(LHErrorCode code);
            virtual ~LHException() = default;

            // retrieve the associated error code
            LHErrorCode Code() const;
        };
    }
}

#endif // !LH_EXCEPTION_H
