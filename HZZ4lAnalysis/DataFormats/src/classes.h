#include "DataFormats/Common/interface/Wrapper.h"

#include "HZZ4lAnalysis/DataFormats/interface/CompoundTypesHZZ4l.h"

#include <vector>

namespace  {
  struct HZZ4lAnalysis_DataFormats {
    
    //DiObjects
    cmg::DiGenParticle dg_;
    std::vector<cmg::DiGenParticle> dgv;
    edm::Wrapper<cmg::DiGenParticle> edg;
    edm::Wrapper<std::vector<cmg::DiGenParticle> > edgv;

    cmg::EMu em_;
    std::vector<cmg::EMu> emv;
    edm::Wrapper<cmg::EMu> eem;
    edm::Wrapper<std::vector<cmg::EMu> > eemv;

    //TriObjects
    cmg::DiMuonMu dmm_;
    std::vector<cmg::DiMuonMu> dmmv;
    edm::Wrapper<cmg::DiMuonMu> edmm;
    edm::Wrapper<std::vector<cmg::DiMuonMu> > edmmv;

    cmg::DiMuonE dme_;
    std::vector<cmg::DiMuonE> dmev;
    edm::Wrapper<cmg::DiMuonE> edme;
    edm::Wrapper<std::vector<cmg::DiMuonE> > edmev;

    cmg::DiElectronE dee_;
    std::vector<cmg::DiElectronE> deev;
    edm::Wrapper<cmg::DiElectronE> edee;
    edm::Wrapper<std::vector<cmg::DiElectronE> > edeev;

    cmg::DiElectronMu dem_;
    std::vector<cmg::DiElectronMu> demv;
    edm::Wrapper<cmg::DiElectronMu> edem;
    edm::Wrapper<std::vector<cmg::DiElectronMu> > edemv;

    //QuadriObjects
    cmg::DiMuonDiMuon dmdm_;
    std::vector<cmg::DiMuonDiMuon> dmdmv;
    edm::Wrapper<cmg::DiMuonDiMuon> edmdm;
    edm::Wrapper<std::vector<cmg::DiMuonDiMuon> > edmdmv;

    cmg::DiElectronDiElectron dede_;
    std::vector<cmg::DiElectronDiElectron> dedev;
    edm::Wrapper<cmg::DiElectronDiElectron> edede;
    edm::Wrapper<std::vector<cmg::DiElectronDiElectron> > ededev;

    cmg::DiElectronDiMuon dedm_;
    std::vector<cmg::DiElectronDiMuon> dedmv;
    edm::Wrapper<cmg::DiElectronDiMuon> ededm;
    edm::Wrapper<std::vector<cmg::DiElectronDiMuon> > ededmv;

    cmg::DiMuonEMu dmem_;
    std::vector<cmg::DiMuonEMu> dmemv;
    edm::Wrapper<cmg::DiMuonEMu> edmem;
    edm::Wrapper<std::vector<cmg::DiMuonEMu> > edmemv;

    cmg::DiElectronEMu deem_;
    std::vector<cmg::DiElectronEMu> deemv;
    edm::Wrapper<cmg::DiElectronEMu> edeem;
    edm::Wrapper<std::vector<cmg::DiElectronEMu> > edeemv;

    cmg::DiGenParticleDiGenParticle dgdg_;
    std::vector<cmg::DiGenParticleDiGenParticle> dgdgv;
    edm::Wrapper<cmg::DiGenParticleDiGenParticle> edgdg;
    edm::Wrapper<std::vector<cmg::DiGenParticleDiGenParticle> > edgdgv;
    
    //Higgs Candidates
    /*
    cmg::DiGenParticleDiGenParticleHiggs dgdgh_;
    std::vector<cmg::DiGenParticleDiGenParticleHiggs> dgdghv;
    edm::Wrapper<cmg::DiGenParticleDiGenParticleHiggs> edgdgh;
    edm::Wrapper<std::vector<cmg::DiGenParticleDiGenParticleHiggs> > edgdghv;
    */

    cmg::DiMuonDiMuonHiggs dmdmh_;
    std::vector<cmg::DiMuonDiMuonHiggs> dmdmhv;
    edm::Wrapper<cmg::DiMuonDiMuonHiggs> edmdmh;
    edm::Wrapper<std::vector<cmg::DiMuonDiMuonHiggs> > edmdmhv;

    cmg::DiElectronDiElectronHiggs dedeh_;
    std::vector<cmg::DiElectronDiElectronHiggs> dedehv;
    edm::Wrapper<cmg::DiElectronDiElectronHiggs> ededeh;
    edm::Wrapper<std::vector<cmg::DiElectronDiElectronHiggs> > ededehv;

    cmg::DiElectronDiMuonHiggs dedmh_;
    std::vector<cmg::DiElectronDiMuonHiggs> dedmhv;
    edm::Wrapper<cmg::DiElectronDiMuonHiggs> ededmh;
    edm::Wrapper<std::vector<cmg::DiElectronDiMuonHiggs> > ededmhv;

    cmg::GenParticlePtr gpptr_;

  };
  

}
