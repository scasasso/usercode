#ifndef COMPOUNDTYPESHZZ4L_H_
#define COMPOUNDTYPESHZZ4L_H_

#include "AnalysisDataFormats/CMGTools/interface/BaseJet.h"
#include "AnalysisDataFormats/CMGTools/interface/DiObject.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"
#include "AnalysisDataFormats/CMGTools/interface/PFJet.h"
#include "AnalysisDataFormats/CMGTools/interface/CompoundTypes.h"

#include "AnalysisDataFormats/CMGTools/interface/GenericTypes.h"


namespace cmg{

  typedef cmg::DiObject<cmg::GenParticle,cmg::GenParticle> DiGenParticle;
    
  typedef cmg::DiObject<cmg::DiMuon,cmg::DiMuon> DiMuonDiMuon;
  typedef cmg::DiObject<cmg::DiElectron,cmg::DiElectron> DiElectronDiElectron;
  typedef cmg::DiObject<cmg::DiElectron,cmg::DiMuon> DiElectronDiMuon;
  typedef cmg::DiObject<cmg::DiGenParticle,cmg::DiGenParticle> DiGenParticleDiGenParticle;


}

#endif /*COMPOUNDTYPESHZZ4L_H_*/
