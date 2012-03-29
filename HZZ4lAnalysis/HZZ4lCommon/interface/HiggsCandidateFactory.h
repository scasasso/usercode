#ifndef HIGGSCANDIDATEFACTORY_H_
#define HIGGSCANDIDATEFACTORY_H_

#include "HZZ4lAnalysis/DataFormats/interface/HiggsCandidate.h"
#include "CMGTools/Common/interface/Factory.h"
#include "CMGTools/Common/interface/SettingTool.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Handle.h"
#include "AnalysisDataFormats/CMGTools/interface/DiObject.h"
#include "CommonTools/CandUtils/interface/CenterOfMassBooster.h"
#include "CommonTools/CandUtils/interface/cloneDecayTree.h"
#include <cmath>


namespace cmg{

  template< typename T, typename U > class HiggsCandidateFactory : public cmg::Factory< cmg::HiggsCandidate<T,U> >,  public cmg::SettingTool<cmg::DiObject<T,U> ,cmg::HiggsCandidate<T,U> > {

  public:

    HiggsCandidateFactory(const edm::ParameterSet& ps):
      inLabel_(ps.getParameter<edm::InputTag>("inputs")){
    }

    //need to override from Factory to insert "typename"
    typedef typename cmg::Factory<typename cmg::HiggsCandidate<T,U> >::event_ptr event_ptr;
    virtual event_ptr create(const edm::Event&, const edm::EventSetup&) const;
    
    ///Set angular variables etc
    virtual void set(const cmg::DiObject<T,U>& pair, cmg::HiggsCandidate<T,U>* const obj) const;
    
  private:       
    const edm::InputTag inLabel_;
  };


}
template< typename T, typename U > typename cmg::HiggsCandidateFactory<T,U>::event_ptr cmg::HiggsCandidateFactory<T,U>::create(const edm::Event& iEvent, const edm::EventSetup&) const{
  
  typedef  std::vector< cmg::HiggsCandidate<T,U> > collection;
  typedef  edm::View< cmg::DiObject<T,U> > diOcollection;
  
  edm::Handle<diOcollection> diCands;
  iEvent.getByLabel(inLabel_,diCands);
    
  
  typename cmg::HiggsCandidateFactory<T,U>::event_ptr result(new collection);
  for(typename diOcollection::const_iterator it = diCands->begin(); it != diCands->end(); ++it){
    cmg::HiggsCandidate<T, U> cmgTmp(*it);
    cmg::HiggsCandidateFactory<T, U>::set(cmgTmp,&cmgTmp);
    result->push_back(cmgTmp);
  }
  return result;
}

template<typename T, typename U> void cmg::HiggsCandidateFactory<T, U>::set(const cmg::DiObject<T,U>& in, cmg::HiggsCandidate<T,U>* const obj) const{
  double costhetastar=-77.0;
  double helphi=-77.0;
  double helphiZ1=-77.0;
  double helphiZ2=-77.0;
  double helcosthetaZ1=-77.0;
  double helcosthetaZ2=-77.0;
  double phistarZ1=+33.0, phistarZ2=-33.0;

  //*********************************
  //TO DO: implement the choice of Z1
  //*********************************

  // create boosters to various objects
  CenterOfMassBooster boostX( in );
  CenterOfMassBooster boostZ1( in.leg1() );
  CenterOfMassBooster boostZ2( in.leg2() );
  
  //clone Zs so that they are not const any more, then boots the Higgs frame
  std::auto_ptr<reco::Candidate> Z1boostedX =cloneDecayTree( in.leg1() );
  std::auto_ptr<reco::Candidate> Z2boostedX =cloneDecayTree( in.leg2() );
  
  boostX.set(*Z1boostedX);
  boostX.set(*Z2boostedX);

  phistarZ1=Z1boostedX->p4().phi();
  phistarZ2=Z2boostedX->p4().phi();
 

  bool Z1is1=false;
  int sign_Z1=-1;
  if(phistarZ1>=0.0 && phistarZ1<M_PI){Z1is1=true; sign_Z1=+1;}
  else{
    if(phistarZ2<0.0&&phistarZ2>-M_PI){//uh-oh,this should not be...
      std::cout<<"ERROR in phi assignment !!!!!!"<<std::endl;
    }
  }


  costhetastar=cos(Z1boostedX->p4().theta()); //Z are distinguishable, Z1 is always what Z1 is in the 4l case
  
  math::XYZVector v_pbeamLAB( 0.0, 0.0, 1.0 );
  //cross prod beam x Z1
  math::XYZVector v_1 = (v_pbeamLAB.Cross(  (Z1boostedX->momentum()).unit()) ).unit();//versor normal to z-z' plane

  math::XYZVector v_2(0.,-33333.,999.);//dummy init
  int negLeptInd_Z1=-1;
  if(Z1boostedX->daughter(0)->charge()<0.0) negLeptInd_Z1=0;
  else  negLeptInd_Z1=+1;
  const reco::Candidate *NegLeptboostedX_Z1 = Z1boostedX->daughter(negLeptInd_Z1); // XXX check for double boost

  if( abs(NegLeptboostedX_Z1->pdgId())!=11 && abs(NegLeptboostedX_Z1->pdgId())!=13  )
    std::cout<<"WARNING: 1st Lepton is neither an electron nor a muon !!!  PdgId="<<NegLeptboostedX_Z1->pdgId()<<std::endl;
  //   cout<<"L1 4-mom before boost to X (0): "<<Z1->daughter(negLeptInd_Z1)->p4().x()<<", "<<Z1->daughter(negLeptInd_Z1)->p4().y()<<", " <<Z1->daughter(negLeptInd_Z1)->p4().z()<<", "<<Z1->daughter(negLeptInd_Z1)->p4().P()<<endl;
  //   cout<<"L1 4-mom after boost to X (1): "<<NegLeptboostedX_Z1->p4().x()<<", "<<NegLeptboostedX_Z1->p4().y()<<", " <<NegLeptboostedX_Z1->p4().z()<<", "<<NegLeptboostedX_Z1->p4().P()<<endl;
  
  //v_2 = cross prod l1 x l2 = versor normal to Z1 decay plane
  // careful to the order: L1, the z-axis and Z->ll make a right-handed (non-orthogonal) frame (xyz); at the end we want the angle btw x and y
  
  v_2=(Z1boostedX->momentum().Cross(NegLeptboostedX_Z1->momentum().unit())).unit();

  //the sign is undefined (impossible to distinguish q from qbar)
  math::XYZVector v_3(0.,-22222.,888.);

  //possible convention: take the jet with highest pt in LAB
  //is it really a good idea? are we losing resolution ? possible pT mismatch GEN vs RECO
  //other idea: just pick the jet with pos azim angle in the Z2 rest frame
  std::auto_ptr<reco::Candidate> Z2boostedZ2 =cloneDecayTree( in.leg2() );
  boostZ2.set(*Z2boostedZ2);
  int negLeptInd_Z2=-1;
  if(Z2boostedX->daughter(0)->charge()<0.0) negLeptInd_Z2=0;
  else  negLeptInd_Z2=+1;
  const reco::Candidate *NegLeptboostedX_Z2 = Z2boostedX->daughter(negLeptInd_Z2); // XXX check for double boost
 
  //v_3 = similar to v_2, BUT
  //now, if we want a right-handed set of unit-vectors, keeping the same direction of the z-axis
  //we must swap the direction of one of the other two vectors of the Z bosons.
  //Keeping the same direction of the z-axis
  //means measuring phiZ1 and phiZ2 w.r.t. to the same v_1 vector (i.e. w.r.t. the same z'-Z1 plane)
  v_3=   ((-1.0*Z2boostedX->momentum()).Cross(NegLeptboostedX_Z2->momentum().unit())).unit() ;

  //in other terms: we can define v_3 as above and then do the crss prod with v_1
  //or define v_3 in a way consistent with v_2 and then do the cross product with a newly defined
  //unit vector v_4 =  (v_pbeamLAB.Cross(  (Z2boostedX->momentum()).unit()) ).unit();//versor normal to z-Z2 plane

  //phi1 and phi2
  helphiZ1=fabs( acos(v_1.Dot(v_2)) );//two-fold ambiguity when doing the acos
  helphiZ2=fabs( acos(v_1.Dot(v_3)) );//two-fold ambiguity when doing the acos
  //phi
  helphi    =fabs( acos(v_2.Dot(v_3)) );//two-fold ambiguity when doing the acos + pi ambiguity from sign of v_3
  
  //resolve sign ambiguities: clockwise rotation around Z1boostedX flight direction
  if(v_pbeamLAB.Dot(v_2)>0.0)helphiZ1=-1.0*helphiZ1;
  else helphiZ1=+1.0*helphiZ1;

  if(v_pbeamLAB.Dot(v_3)>0.0)helphiZ2=+1.0*helphiZ2;
  else helphiZ2=-1.0*helphiZ2;
  if(NegLeptboostedX_Z1->momentum().Dot(v_3)>0.0)helphi= +1.0 * helphi;
  else helphi= -1.0 * helphi;

  //std::cout << "cloning" << std::endl;
  //cosThetaZ1
  std::auto_ptr<reco::Candidate> XboostedZ1 =cloneDecayTree( in );
  std::auto_ptr<reco::Candidate> Z1boostedZ1 =cloneDecayTree( in.leg1() );
  boostZ1.set(*Z1boostedZ1);
  boostZ1.set(*XboostedZ1);
  const reco::Candidate& lepton_neg_Z1=(*Z1boostedZ1->daughter(negLeptInd_Z1));
  helcosthetaZ1 = (-1.0*(lepton_neg_Z1.p4().x()* XboostedZ1->p4().x()+
			  lepton_neg_Z1.p4().y()* XboostedZ1->p4().y()+
			  lepton_neg_Z1.p4().z()* XboostedZ1->p4().z())/
		    (lepton_neg_Z1.p4().P()* XboostedZ1->p4().P())  );

  //calc cosThetaZ2
  std::auto_ptr<reco::Candidate> XboostedZ2 =cloneDecayTree( in );
  boostZ2.set(*XboostedZ2);
  const reco::Candidate& lepton_neg_Z2=(*Z2boostedZ2->daughter(negLeptInd_Z2));
  helcosthetaZ2 = fabs((lepton_neg_Z2.p4().x()* XboostedZ2->p4().x()+
			 lepton_neg_Z2.p4().y()* XboostedZ2->p4().y()+
			 lepton_neg_Z2.p4().z()* XboostedZ2->p4().z())/
			(lepton_neg_Z2.p4().P()* XboostedZ2->p4().P())  );

  //sanity check
  if(fabs(helphi+helphiZ1+helphiZ2) > 0.001){
    if( (helphi+helphiZ1+helphiZ2 - 2*M_PI > 0.001) && (helphi+helphiZ1-helphiZ2 + 2*M_PI > 0.001) ){
      std::cout <<">>>>> WARNING !!!! Error when calculating Helicity angles ! Sum of HelPhi different from zero ! -> HelPhi = "<<helphi<<" HelPhiZ1 = "<<helphiZ1<<" HelPhiZ2 = "<<helphiZ2<<"  SUM = "<< helphi+helphiZ1+helphiZ2 <<"  Phi+Phi1-Phi2 = "<<helphi+helphiZ1-helphiZ2 <<std::endl;

    }
  }

    obj->costhetastar_ = costhetastar;
    obj->helphi_ = helphi;
    obj->helphiZ1_ = helphiZ1;
    obj->helphiZ2_ = helphiZ2;
    obj->helcosthetaZ1_ = helcosthetaZ1;
    obj->helcosthetaZ2_ = helcosthetaZ2;
    obj->phistarZ1_ = phistarZ1;
    obj->phistarZ2_ = phistarZ2; 
}

#endif
