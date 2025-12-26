/*****************************************************
 * @file    Feature.h
 * @date    February 2018
 * @author  Ocean Optics, Inc.
 *
 * This is an abstract interface that other feature types will
 * implement.  A Feature is taken to be some capability of
 * a Device that is relatively self-contained.  For instance,
 * an analog output voltage would be a Feature.  Features can
 * also contain multiple functions; for instance, a TEC may
 * be able to report a temperature, take a temperature as a
 * set point, and turn on or off.  These capabilities are
 * interrelated, and would be considered a single feature.
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

#ifndef FEATURE_H
#define FEATURE_H

#include "common/OceanDirect.h"
#include "common/buses/Bus.h"
#include "common/features/FeatureFamily.h"
#include "common/exceptions/FeatureException.h"
#include "common/protocols/Protocol.h"
#include <vector>

namespace oceandirect {

    class Feature {
    public:
        virtual ~Feature() = 0;

        /* Allow the object that represents a given feature to initialize
         * itself by reading from the corresponding feature on the real
         * device, and/or put the real device feature into a known state.
         * This should return true if the feature is ready to be used, and false
         * otherwise.
         */
        virtual bool initialize(const Protocol &protocol, const Bus &bus) = 0;

        virtual FeatureFamily getFeatureFamily() = 0;
    };

    /* Default implementation for (otherwise) pure virtual destructor */
    inline Feature::~Feature() {}
}

#endif /* FEATURE_H */
