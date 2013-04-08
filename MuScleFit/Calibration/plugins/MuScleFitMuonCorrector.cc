
//
// $Id: MuScleFitMuonCorrector.cc,v 1.4 2013/04/05 16:11:35 scasasso Exp $
//

/**
  \class    modules::MuScleFitMuonCorrectorT MuScleFitMuonCorrectorT.h 
  \brief    Applies MuScleFit corrections to muons            
  \author   Giovanni Petrucciani (modified by Stefano Casasso)
  \version  $Id: MuScleFitMuonCorrector.cc,v 1.4 2013/04/05 16:11:35 scasasso Exp $
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
      std::string identifier_;
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
  identifier_(iConfig.getParameter<std::string>("identifier")),
  debug_(iConfig.getParameter<bool>("debug")),
  applySmearing_(iConfig.getParameter<bool>("applySmearing")),
  fakeSmearing_(iConfig.getParameter<bool>("fakeSmearing"))
{

  TString fileName = "";
  if (identifier_=="Summer12_DR53X"){ // MC 2012
    fileName.Append("MuScleFit/Calibration/data/MuScleFit_2012_MC_53X.txt");
  }
  else if (identifier_=="Data2012_53X"){ // DATA 2012
    fileName.Append("MuScleFit/Calibration/data/MuScleFit_2012_DATA_53X.txt");
  }
  else if (identifier_=="Fall11_START42"){ // MC 2011 (42X)
    fileName.Append("MuScleFit/Calibration/data/MuScleFit_2011_MC_42X.txt");
  }
  else if (identifier_=="Fall11_START44"){ // MC 2011 (44X)
    fileName.Append("MuScleFit/Calibration/data/MuScleFit_2011_MC_44X.txt");
  }
  else if (identifier_=="Data2011_42X"){ // DATA 2011 (42X)
    fileName.Append("MuScleFit/Calibration/data/MuScleFit_2011_DATA_42X.txt");
  }
  else if (identifier_=="Data2011_44X"){ // DATA 2011 (44X)
    fileName.Append("MuScleFit/Calibration/data/MuScleFit_2011_DATA_42X.txt");
  }
  else {
    std::cout<<"%MuScleFitCorrector% wrong identifier, choose among:"<<std::endl;
    std::cout<<"  data: 'Data2012_53X', 'Data2011_42X', 'Data2011_44X'"<<std::endl;
    std::cout<<"   MC : 'Summer12_DR53X', 'Fall11_START44', 'Fall11_START42'"<<std::endl;
    exit(0);
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
    
    
     if (applySmearing_){
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
