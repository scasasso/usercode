#include "DataFormats/Common/interface/Wrapper.h"

#include "HZZ4lAnalysis/DataFormats/interface/CompoundTypesHZZ4l.h"

#include <vector>

namespace {
  struct HZZ4lAnalysis_DataFormats {

    cmg::DiGenParticle dg_;
    std::vector<cmg::DiGenParticle> dgv;
    edm::Wrapper<cmg::DiGenParticle> edg;
    edm::Wrapper<std::vector<cmg::DiGenParticle> > edgv;

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

    /* COMMENTED BECAUSE HIGGSCANDIDATEFACTORY CLASS NOT YET IMPLEMENTED
    cmg::DiMuonDiMuonHiggs dmdmh_;
    std::vector<cmg::DiMuonDiMuonHiggs> dmdmhv;
    edm::Wrapper<cmg::DiMuonDiMuonHiggs> edmdmh;
    edm::Wrapper<std::vector<cmg::DiMuonDiMuonHiggs> > edmdmhv;

    cmg::DiElectronDiElectronHiggs dzeh_;
    std::vector<cmg::DiElectronDiElectronHiggs> dzevh;
    edm::Wrapper<cmg::DiElectronDiElectronHiggs> edezh;
    edm::Wrapper<std::vector<cmg::DiElectronDiElectronHiggs> > edzevh;

    cmg::DiGenParticleDiGenParticleHiggs dgdgh_;
    std::vector<cmg::DiGenParticleDiGenParticleHiggs> dgdghv;
    edm::Wrapper<cmg::DiGenParticleDiGenParticleHiggs> edgdgh;
    edm::Wrapper<std::vector<cmg::DiGenParticleDiGenParticleHiggs> > edgdghv;
    */

    cmg::GenParticlePtr gpptr_;

  };
  

}
