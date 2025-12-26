/*****************************************************
 * @file    FeatureImpl.h
 * @date    March 2018
 * @author  Ocean Optics, Inc.
 *
 * This is a simple base class that other feature types will
 * extend.  A Feature is taken to be some capability of
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

#ifndef FEATUREIMPL_H
#define FEATUREIMPL_H

#include "common/OceanDirect.h"
#include "common/exceptions/FeatureProtocolNotFoundException.h"
#include "common/features/Feature.h"
#include "common/protocols/ProtocolHelper.h"
#include <vector>

namespace oceandirect {
    /* This does virtual inheritance from Feature because it is assumed that
     * in some cases there will be diamond inheritance.  This will generally
     * only happen where one top-level Feature is implemented by deriving from
     * another Feature.
     */
    class FeatureImpl : public virtual Feature {
    public:
        FeatureImpl();
        virtual ~FeatureImpl();

        /* Allow the object that represents a given feature to initialize
         * itself by reading from the corresponding feature on the real
         * device, and/or put the real device feature into a known state.
         * Overriding this is not required.  This should return true if
         * the feature is ready to be used, and false otherwise.
         */
        virtual bool initialize(const Protocol &protocol, const Bus &bus) override;

    protected:
        std::vector<ProtocolHelper *> protocols;

        /* Protocols are described by their base class (Protocol)
         * and may be designated that way.  However, different
         * functionality within a given command set may be broken
         * into different implementation types, all of which extend
         * the base Protocol class.  This is a simple lookup mechanism
         * to use the Protocol that some anonymous caller might
         * provide as a point of reference to then find the extended
         * Protocol class that can be used to access certain features.
         */
        ProtocolHelper *lookupProtocolImpl(const Protocol &protocol);
    };

}

#endif /* FEATUREIMPL_H */
