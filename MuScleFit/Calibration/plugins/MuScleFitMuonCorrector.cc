
//
// $Id: MuScleFitMuonCorrector.cc,v 1.1 2013/04/05 14:18:33 scasasso Exp $
//

/**
  \class    modules::MuScleFitMuonCorrectorT MuScleFitMuonCorrectorT.h 
  \brief    Applies MuScleFit corrections to muons            
  \author   Giovanni Petrucciani (modified by Stefano Casasso)
  \version  $Id: MuScleFitMuonCorrector.cc,v 1.1 2013/04/05 14:18:33 scasasso Exp $
*/


#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "MuScleFit/Calibration/interface/MuScleFitCorrector.h"

namespace modules {

  template<typename T>
  class MuScleFitMuonCorrectorT : public edm::EDProducer {
    public:
      explicit MuScleFitMuonCorrectorT(const edm::ParameterSet & iConfig);
      virtual ~MuScleFitMuonCorrectorT() { }

      virtual void produce(edm::Event & iEvent, const edm::EventSetup & iSetup);

    private:
      /// Labels for input collections
      edm::InputTag src_;
      bool is2012_;
      bool is42X_;
      bool isMC_;
      bool debug_;
      bool applySmearing_;
      bool fakeSmearing_;

      // MuScleFit corrector
      MuScleFitCorrector* corrector_;
  };

} // namespace


template<typename T>
modules::MuScleFitMuonCorrectorT<T>::MuScleFitMuonCorrectorT(const edm::ParameterSet & iConfig) :
  src_(iConfig.getParameter<edm::InputTag>("src")),
  is2012_(iConfig.getParameter<bool>("is2012")),
  isMC_(iConfig.getParameter<bool>("isMC")),
  debug_(iConfig.getParameter<bool>("debug")),
  applySmearing_(iConfig.getParameter<bool>("applySmearing")),
  fakeSmearing_(iConfig.getParameter<bool>("fakeSmearing"))
{

  is2012_=false;
  is42X_=false;
  char * base = getenv("CMSSW_VERSION");
  if (base!=NULL) {
    std::string baseDir(base);
    if (baseDir.find("CMSSW_5_")!=std::string::npos)
      is2012_=true;
    if (baseDir.find("CMSSW_4_2")!=std::string::npos)
      is42X_=true;

  }
  else {
    printf("NO CMSSW Version found\n");
  }


  TString fileName = "";
  if (is2012_ && isMC_){ // MC 2012
    fileName.Append("ZZAnalysis/AnalysisStep/data/MuScleFit_2012_MC_52X_type57_270313.txt");
  }
  else if (is2012_ && !isMC_){ // DATA 2012
    fileName.Append("ZZAnalysis/AnalysisStep/data/MuScleFit_2012_DATA_53X_type57_270313.txt");
  }
  else if (!is2012_ && is42X_ && isMC_){ // MC 2011 (42X)
    fileName.Append("ZZAnalysis/AnalysisStep/data/MuScleFit_2011_MC_42X_type57_270313.txt");
  }
  else if (!is2012_ && !is42X_ && isMC_){ // MC 2011 (44X)
    fileName.Append("ZZAnalysis/AnalysisStep/data/MuScleFit_2011_MC_44X_type57_270313.txt");
  }
  else if (!is2012_ && is42X_ && !isMC_){ // DATA 2011 (42X)
    fileName.Append("ZZAnalysis/AnalysisStep/data/MuScleFit_2011_DATA_42X_type57_270313.txt");
  }
  else if (!is2012_ && !is42X_ && !isMC_){ // DATA 2011 (44X)
    fileName.Append("ZZAnalysis/AnalysisStep/data/MuScleFit_2011_DATA_42X_type57_270313.txt");
  }

  edm::FileInPath fileWithFullPath(fileName.Data());
  corrector_ = new MuScleFitCorrector(fileWithFullPath.fullPath());
  
  produces<std::vector<T> >(); 
}

template<typename T>
void 
modules::MuScleFitMuonCorrectorT<T>::produce(edm::Event & iEvent, const edm::EventSetup & iSetup) {
    using namespace edm;
    using namespace std;

    Handle<View<T> > src;
    iEvent.getByLabel(src_, src);

    unsigned int nsrc = src->size();
    auto_ptr<vector<T> > out(new vector<T>());
    out->reserve(nsrc);

    unsigned int event = (unsigned int)iEvent.id().event(); 

    for (unsigned int i = 0; i < nsrc; ++i) {
        T mu = (*src)[i];
	double chg = mu.charge();
	TLorentzVector* p4 = new TLorentzVector(mu.px(),mu.py(),mu.pz(),mu.energy());


     if(debug_ && event%100==0) {
       cout<<"### RAW MOMENTA ###"<<endl;
       cout<<"   Muon: "<<"px = "<<p4->Px()<<", py = "<<p4->Py()<<", pz = "<<p4->Pz()<<", pT = "<<p4->Pt()<<endl;
     }

	corrector_->applyPtCorrection(*p4,chg);
	corrector_->applyPtCorrection(*p4,chg);	 


     if(debug_ && event%100==0) {
       cout<<"### CORRECTED MOMENTA ###"<<endl;
       cout<<"   Muon: "<<"px = "<<p4->Px()<<", py = "<<p4->Py()<<", pz = "<<p4->Pz()<<", pT = "<<p4->Pt()<<endl;
     }

     
     if (isMC_ && applySmearing_){
       corrector_->applyPtSmearing(*p4,chg,fakeSmearing_);
       corrector_->applyPtSmearing(*p4,chg,fakeSmearing_);
       
       if(debug_ && event%100==0) {
	 cout<<"### SMEARED MOMENTA ###"<<endl;
	 cout<<"   Muon: "<<"px = "<<p4->Px()<<", py = "<<p4->Py()<<", pz = "<<p4->Pz()<<", pT = "<<p4->Pt()<<endl;
       }
     }

     
     math::XYZTLorentzVector newP4(p4->Px(),p4->Py(),p4->Pz(),p4->Energy());
     mu.setP4(newP4);
     
     
     out->push_back(mu);
     
     
    }
    
    iEvent.put(out);
}


namespace modules {
    //typedef modules::MuScleFitMuonCorrectorT<reco::Muon>  MuScleFitMuonCorrector;
    typedef modules::MuScleFitMuonCorrectorT<pat::Muon>   MuScleFitPATMuonCorrector;
}

#include "FWCore/Framework/interface/MakerMacros.h"
using namespace modules;
//DEFINE_FWK_MODULE(MuScleFitMuonCorrector);
DEFINE_FWK_MODULE(MuScleFitPATMuonCorrector);
