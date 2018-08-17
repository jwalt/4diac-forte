/*******************************************************************************
 * Copyright (c) 2006-2015 ACIN, Profactor GmbH, fortiss GmbH
 *                      2018 Johannes Kepler University
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    Rene Smodic, Thomas Strasser, Alois Zoitl, Michael Hofmann,
 *    Martin Melik-Merkumians, Ingo Hegny, Patrick Smejkal
 *      - initial implementation and rework communication infrastructure
 *    Alois Zoitl - introduced new CGenFB class for better handling generic FBs
 *******************************************************************************/
#ifndef _COMMFB_H_
#define _COMMFB_H_

#include <forte_config.h>
#include "basecommfb.h"
#include "comtypes.h"

namespace forte {
  namespace com_infra {

    class CCommFB : public CBaseCommFB {
    public:
      virtual ~CCommFB();

      virtual EMGMResponse changeFBExecutionState(EMGMCommandType pa_unCommand);

    protected:
      CCommFB(const CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes, forte::com_infra::EComServiceType pa_eCommServiceType);

      void executeEvent(int pa_nEIID);

      static const TEventID scm_nEventINITID = 0;
      static const TEventID scm_nEventINITOID = 0;
      static const TEventID scm_nSendNotificationEventID = 1;
      static const TEventID scm_nReceiveNotificationEventID = 1;

      static const char * const scmDefaultIDPrefix;
      static const char * const scmDefaultIDSuffix;

      static char *extractLayerIdAndParams(char **paRemainingID, char **paLayerParams);

      char *getDefaultIDString(const char *paID);

      virtual EComResponse receiveData();
      virtual EComResponse sendData();

    private:
      static const CStringDictionary::TStringId scm_aunRequesterEventInputNameIds[];
      static const CStringDictionary::TStringId scm_aunRequesterEventOutputNameIds[];

      static const CStringDictionary::TStringId scm_aunResponderEventInputNameIds[];
      static const CStringDictionary::TStringId scm_aunResponderEventOutputNameIds[];

      static const TForteInt16 scm_anEIWithIndexes[];
      static const TForteInt16 scm_anEOWithIndexes[];

      virtual SFBInterfaceSpecforGenerics *createInterfaceSpec(const char *paConfigString);
    };

  }
}

#endif //_COMMFB_H_
