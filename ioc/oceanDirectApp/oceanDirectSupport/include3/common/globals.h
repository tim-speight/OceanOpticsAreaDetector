/**
* @file     globals.h
* @author   Mark Zieg <mark.zieg@oceanoptics.com>
* @date     Sep 26, 2018
* @brief    Provides a single point of maintenance for anything you want
*           included, defined, or set across every file in the application
*           (such as memory profiling, etc).  Normally empty.
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

#ifndef OCEANDIRECT_GLOBALS_H
#define OCEANDIRECT_GLOBALS_H

// change to "#if 1" to enable memory heap debugging under Visual Studio
#if 0
    #ifdef _WINDOWS

        // For these to work right, you need to #define _CRTDBG_MAP_ALLOC and
        // _CRTDBG_MAP_ALLOC_NEW in your Visual Studio project (i.e., Project
        // -> Configuration Properties -> C/C++ -> Preprocessor -> Preprocessor
        // Definitions).  #Defining them here in your header files DOES NOT
        // WORK, because Visual Studio will internally include many system
        // headers (including stdafx.h) long before you get here.
        //
        // @see http://msdn.microsoft.com/en-us/library/e5ewb1h3%28v=vs.80%29.aspx
        // @see http://social.msdn.microsoft.com/Forums/en/vcgeneral/thread/ebc7dd7a-f3c6-49f1-8a60-e381052f21b6,

        #pragma message("  (Windows memory debugging enabled)")

        // these will provide leak profiling for C malloc(), etc
        #include <stdlib.h>
        #include <crtdbg.h>

        // these will provide leak profiling for C++ 'new'
        #ifndef DBG_NEW
            #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
            #define new DBG_NEW
        #endif

    #endif
#endif

#endif
