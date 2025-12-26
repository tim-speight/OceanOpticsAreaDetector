/*****************************************************
 * @file    EthernetAPI.h
 * @date    May 2022
 * @author  Ocean Insight, Inc.
 *
 * This is an interface to OceanDirect that allows
 * the user to read and write user strin to device.
 * This is intended as a usable and extensible API.
 */
 /************************************************************************
 *
 * OCEAN INSIGHT CONFIDENTIAL
 * __________________
 *
 * [2018] - [2022] Ocean Insight Incorporated
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

#ifndef ETHERNET_API_H
#define ETHERNET_API_H

#include "api/DllDecl.h"
#include <cstdint>
 /*!
    @brief  This is an interface to advanced features of
            OceanDirect that allow access to less common
            controls. This is intended as a usable and
            extensible API.
 */
namespace oceandirect {
	namespace api {

        class DLL_DECL EthernetAPI {
        public:
            EthernetAPI() = default;
            virtual ~EthernetAPI() = default;
            static EthernetAPI *getInstance();

            static void shutdown();

            virtual bool getGigabitEthernetEnableStatus(long deviceID, int* errorCode, std::uint32_t interfaceIndex);
            virtual void setGigabitEthernetEnableStatus(long deviceID, int* errorCode, std::uint32_t interfaceIndex, bool enable);

            virtual void getMACAddress(long deviceID, int* errorCode, std::uint32_t interfaceIndex, std::uint8_t *macAddress, std::uint32_t macAddressLength);
            virtual void setMACAddress(long deviceID, int* errorCode, std::uint32_t interfaceIndex, std::uint8_t* macAddress, std::uint32_t macAddressLength);

        protected:
            static EthernetAPI *instance;
        };
    }
}
#endif /* ETHERNET_API_H */
