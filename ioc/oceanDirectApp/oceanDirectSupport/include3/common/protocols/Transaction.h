/*****************************************************
 * @file    Transaction.h
 * @date    January 2022
 * @author  Ocean Optics, Inc.
 *
 * The Transaction class is simply a wrapper
 * around one or more Transfer objects that must
 * be executed in a particular order.  This is
 * provided for convenience.  Some transfers
 * to Ocean Optics spectrometers put the spectrometer
 * into a particular state where it expects another
 * action to be taken, and Transaction objects can
 * be used to ensure that all expected operations occur.
 *
 * Some actions, like requesting a spectrum, do not
 * necessarily require that the next action be a read
 * operation.  Thus, some Transfers that appear to follow
 * a causal chain may not in fact make good Transactions.
 * In this case, reading the status of the device until
 * it reports data ready is a common operation before
 * reading the spectrum.
 *
 * Note that the Transaction class has no notion of buses
 * or protocols, and this is by design.
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

#ifndef OCEANDIRECT_TRANSACTION_H
#define OCEANDIRECT_TRANSACTION_H

#include <vector>
#include "common/protocols/Exchange.h"
#include "common/protocols/Transfer.h"
#include "common/buses/TransferHelper.h"
#include "common/protocols/ProtocolHint.h"

namespace oceandirect {

    class Transaction : public Exchange {
    public:
        Transaction();
        virtual ~Transaction();
        void addTransfer(Transfer *xfer);

        /* Inherited from Exchange */
        virtual void transferToDevice(TransferHelper *helper) override;
        virtual std::vector<std::uint8_t> transferFromDevice(TransferHelper *helper) override;
        virtual std::vector<std::uint8_t> batchTransfer(TransferHelper *helper);

    protected:
        std::vector<Transfer *> transfers;

    private:
        void updateHints();
    };

}

#endif /* OCEANDIRECT_TRANSACTION_H */

