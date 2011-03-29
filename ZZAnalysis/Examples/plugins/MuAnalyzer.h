#ifndef MuAnalyzer_H
#define MuAnalyzer_H

//class MuAnalyzer

// Base Class Headers
#include "FWCore/Framework/interface/EDAnalyzer.h"

namespace edm {
  class ParameterSet;
  class Event;
  class EventSetup;
  class LuminosityBlock;
}

class TH1I;
class TH1F;
class TH2F;

class MuAnalyzer: public edm::EDAnalyzer {
public:
  /// Constructor
  MuAnalyzer(const edm::ParameterSet& pset);

  /// Destructor
  virtual ~MuAnalyzer();

  // Operations

  void analyze(const edm::Event & event, const edm::EventSetup& eventSetup);
  void endLuminosityBlock(const edm::LuminosityBlock &, const edm::EventSetup&);


  virtual void beginJob() ;
  virtual void endJob() ;
protected:

private:

  int nTKandSTA_;
  int NMuCounter_;

  // Filter studies
  std::vector<std::string> numEventsNames_;
  TH1F *h1SelectedEvts_;

  // Muon studies
  std::string theMuonLabel_;
  std::string theZllLabel_;
  std::string theJetPFLabel_;
  
  TH1I *h1NMuons_;
  TH1I *h1NZll_;

  TH1F *h1CheckMu_;

  TH1F *h1DiMuMassAll_;
  TH1F *h1DiMuMassPresel_;
  TH1F *h1MuType_;

  //All muons
  TH1F *h1PtRecoAllMuon_;  
  TH1F *h1EtaRecoAllMuon_;
  TH1F *h1PhiRecoAllMuon_;
  TH1F *h1DxyRecoAllMuon_;
  TH1F *h1DzRecoAllMuon_;
  TH2F *h2EtaPtRecoAllMuon_;
  //Global muons
  TH1F *h1PtRecoGlobalMuon_;  
  TH1F *h1EtaRecoGlobalMuon_;
  TH1F *h1PhiRecoGlobalMuon_;
  TH1F *h1DxyRecoGlobalMuon_;
  TH1F *h1DzRecoGlobalMuon_;
  TH2F *h2EtaPtRecoGlobalMuon_;
  //GlobalPresel muons
  TH1F *h1PtRecoGlobalPreselMuon_;  
  TH1F *h1EtaRecoGlobalPreselMuon_;
  TH1F *h1PhiRecoGlobalPreselMuon_;
  TH1F *h1DxyRecoGlobalPreselMuon_;
  TH1F *h1DzRecoGlobalPreselMuon_;
  TH2F *h2EtaPtRecoGlobalPreselMuon_;
  //GlobalNjet muons
  TH1F *h1PtRecoGlobalNjetMuon_;  
  TH1F *h1EtaRecoGlobalNjetMuon_;
  TH1F *h1PhiRecoGlobalNjetMuon_;
  TH1F *h1DxyRecoGlobalNjetMuon_;
  TH1F *h1DzRecoGlobalNjetMuon_;
  TH2F *h2EtaPtRecoGlobalNjetMuon_;
  //GlobalZllmass muons
  TH1F *h1PtRecoGlobalZllmassMuon_;  
  TH1F *h1EtaRecoGlobalZllmassMuon_;
  TH1F *h1PhiRecoGlobalZllmassMuon_;
  TH1F *h1DxyRecoGlobalZllmassMuon_;
  TH1F *h1DzRecoGlobalZllmassMuon_;
  TH2F *h2EtaPtRecoGlobalZllmassMuon_;
  //GlobalNmu muons
  TH1F *h1PtRecoGlobalNmuMuon_;  
  TH1F *h1EtaRecoGlobalNmuMuon_;
  TH1F *h1PhiRecoGlobalNmuMuon_;
  TH1F *h1DxyRecoGlobalNmuMuon_;
  TH1F *h1DzRecoGlobalNmuMuon_;
  TH2F *h2EtaPtRecoGlobalNmuMuon_;
  //Tracker muons
  TH1F *h1PtRecoTrackerMuon_;  
  TH1F *h1EtaRecoTrackerMuon_;
  TH1F *h1PhiRecoTrackerMuon_;
  TH1F *h1DxyRecoTrackerMuon_;
  TH1F *h1DzRecoTrackerMuon_;
  TH2F *h2EtaPtRecoTrackerMuon_;
  //StandAlone muons
  TH1F *h1PtRecoStandAloneMuon_;  
  TH1F *h1EtaRecoStandAloneMuon_;
  TH1F *h1PhiRecoStandAloneMuon_;
  TH1F *h1DxyRecoStandAloneMuon_;
  TH1F *h1DzRecoStandAloneMuon_;
  TH2F *h2EtaPtRecoStandAloneMuon_;
  //!(Global) but TK && SA muons
  TH1F *h1PtRecoTKandSAMuon_;  
  TH1F *h1EtaRecoTKandSAMuon_;
  TH1F *h1PhiRecoTKandSAMuon_;
  TH1F *h1DxyRecoTKandSAMuon_;
  TH1F *h1DzRecoTKandSAMuon_;
  TH2F *h2EtaPtRecoTKandSAMuon_;
};
#endif

