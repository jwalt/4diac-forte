/*******************************************************************************
 * Copyright (c) 2006 - 2011 ACIN, Profactor GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer, Ingo Hegny
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once

#include "basicfb.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_E_D_FF: public CBasicFB {
  DECLARE_FIRMWARE_FB(FORTE_E_D_FF)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  static const TEventID scm_nEventCLKID = 0;
  static const TDataIOID scm_anEIWith[];
  static const TForteInt16 scm_anEIWithIndexes[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];
  static const TEventID scm_nEventEOID = 0;
  static const TDataIOID scm_anEOWith[]; 
  static const TForteInt16 scm_anEOWithIndexes[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;
  CIEC_ANY *getVarInternal(size_t) override;
  void alg_LATCH(void);
  static const TForteInt16 scm_nStateSTART = 0;
  static const TForteInt16 scm_nStateSET = 1;
  static const TForteInt16 scm_nStateRESET = 2;
  
  void enterStateSTART(void);
  void enterStateSET(void);
  void enterStateRESET(void);

  void executeEvent(int pa_nEIID) override;

  void readInputData(size_t pa_nEIID) override;
  void writeOutputData(size_t pa_nEIID) override;

public:
  FORTE_E_D_FF(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes);

  CIEC_BOOL var_D;
  CIEC_BOOL var_Q;
  CIEC_BOOL var_conn_Q;
  CEventConnection conn_EO;
  CDataConnection *conn_D;
  CDataConnection conn_Q;
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  void evt_CLK(const CIEC_BOOL &pa_D, CIEC_BOOL &pa_Q) {
    var_D = pa_D;
    receiveInputEvent(scm_nEventCLKID, nullptr);
    pa_Q = var_Q;
  }
  void operator()(const CIEC_BOOL &pa_D, CIEC_BOOL &pa_Q) {
    evt_CLK(pa_D, pa_Q);
  }
};



