#include "DataFormats/Common/interface/Wrapper.h"

#include "HZZ4lAnalysis/DataFormats/interface/CompoundTypesHZZ4l.h"

#include <vector>

namespace  {
  struct HZZ4lAnalysis_DataFormats {

    cmg::DiGenParticle dg_;
    std::vector<cmg::DiGenParticle> dgv;
    edm::Wrapper<cmg::DiGenParticle> edg;
    edm::Wrapper<std::vector<cmg::DiGenParticle> > edgv;

    cmg::EMu em_;
    std::vector<cmg::EMu> emv;
    edm::Wrapper<cmg::EMu> eem;
    edm::Wrapper<std::vector<cmg::EMu> > eemv;

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

    cmg::DiGenParticleDiGenParticle dgdg_;
    std::vector<cmg::DiGenParticleDiGenParticle> dgdgv;
    edm::Wrapper<cmg::DiGenParticleDiGenParticle> edgdg;
    edm::Wrapper<std::vector<cmg::DiGenParticleDiGenParticle> > edgdgv;
    
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
