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
#include "TLorentzVector.h"

namespace cmg{

  template< typename T, typename U > class HiggsCandidateFactory : public cmg::Factory< cmg::HiggsCandidate<T,U> >,  public cmg::SettingTool<cmg::DiObject<T,U> ,cmg::HiggsCandidate<T,U> > {

  public:

    HiggsCandidateFactory(const edm::ParameterSet& ps):
      inLabel_(ps.getParameter<edm::InputTag>("inputs")){
    }

    //need to override from Factory to insert "typename"
    typedef typename cmg::Factory<typename cmg::HiggsCandidate<T,U> >::event_ptr event_ptr;
    virtual event_ptr create(const edm::Event&, const edm::EventSetup&);
    
    ///Set angular variables etc
    virtual void set(const cmg::DiObject<T,U>& pair, cmg::HiggsCandidate<T,U>* const obj) const;
    
  private:       
    const edm::InputTag inLabel_;
  };


}
template< typename T, typename U > typename cmg::HiggsCandidateFactory<T,U>::event_ptr cmg::HiggsCandidateFactory<T,U>::create(const edm::Event& iEvent, const edm::EventSetup&) {
  
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

//new implementation (Sara Mon 2 Apr) to be 100% consistent with PDF definition
template<typename T, typename U> void cmg::HiggsCandidateFactory<T, U>::set(const cmg::DiObject<T,U>& in, cmg::HiggsCandidate<T,U>* const obj) const{
	
  //will convert to TLorentzVector
  math::XYZTLorentzVector leg1 = obj->leg1().p4();
  math::XYZTLorentzVector leg2 = obj->leg2().p4();
  math::XYZTLorentzVector leg11 = obj->leg1().leg1().p4();
  math::XYZTLorentzVector leg12 = obj->leg1().leg2().p4();
  math::XYZTLorentzVector leg21 = obj->leg2().leg1().p4();
  math::XYZTLorentzVector leg22 = obj->leg2().leg2().p4();

  TLorentzVector Z1(leg1.x(),leg1.y(),leg1.z(),leg1.t());
  TLorentzVector Z2(leg2.x(),leg2.y(),leg2.z(),leg2.t()) ;
  TLorentzVector thep4H = Z1+Z2;
  
  //define Z1 as the one nearest to nominal Z mass
  const double PDGZmass = 91.2;
  TLorentzVector thep4Z1; TLorentzVector thep4M11; TLorentzVector thep4M12;
  TLorentzVector thep4Z2; TLorentzVector thep4M21; TLorentzVector thep4M22;
  
  
  if ( fabs(PDGZmass-Z1.M()) > fabs(PDGZmass-Z2.M()) ){	  			
    thep4Z1 = Z2; 
    if(obj->leg2().leg1().charge()<0){
      thep4M11 = TLorentzVector(leg21.x(),leg21.y(),leg21.z(),leg21.t());// obj->leg2().leg1().p4(); 
      thep4M12 = TLorentzVector(leg22.x(),leg22.y(),leg22.z(),leg22.t());//obj->leg2().leg2().p4();
    }
    else{
      thep4M11 = TLorentzVector(leg22.x(),leg22.y(),leg22.z(),leg22.t());//obj->leg2().leg2().p4();
      thep4M12 = TLorentzVector(leg21.x(),leg21.y(),leg21.z(),leg21.t());// obj->leg2().leg1().p4(); 
    }
      
    thep4Z2 = Z1; 
    if(obj->leg1().leg1().charge()<0){
      thep4M21 = TLorentzVector(leg11.x(),leg11.y(),leg11.z(),leg11.t());//obj->leg1().leg1().p4(); 
      thep4M22 = TLorentzVector(leg12.x(),leg12.y(),leg12.z(),leg12.t());//obj->leg1().leg2().p4();
    }
    else{
      thep4M21 = TLorentzVector(leg12.x(),leg12.y(),leg12.z(),leg12.t());//obj->leg1().leg2().p4(); 
      thep4M22 = TLorentzVector(leg11.x(),leg11.y(),leg11.z(),leg11.t());//obj->leg1().leg1().p4();
    }
  }
  else {
    thep4Z1 = Z1; 
    if(obj->leg1().leg1().charge()<0){
      thep4M11 =TLorentzVector(leg11.x(),leg11.y(),leg11.z(),leg11.t());// obj->leg1().leg1().p4(); 
      thep4M12 = TLorentzVector(leg12.x(),leg12.y(),leg12.z(),leg12.t());//obj->leg1().leg2().p4();
    }
    else{
      thep4M11 = TLorentzVector(leg12.x(),leg12.y(),leg12.z(),leg12.t());//obj->leg1().leg2().p4(); 
      thep4M12 = TLorentzVector(leg11.x(),leg11.y(),leg11.z(),leg11.t());//obj->leg1().leg1().p4();
    }
   thep4Z2 = Z2; 
   if(obj->leg2().leg1().charge()<0){
     thep4M21 = TLorentzVector(leg21.x(),leg21.y(),leg21.z(),leg21.t());// obj->leg2().leg1().p4(); 
     thep4M22 = TLorentzVector(leg22.x(),leg22.y(),leg22.z(),leg22.t());//obj->leg2().leg2().p4();
   }
   else{
     thep4M21 = TLorentzVector(leg22.x(),leg22.y(),leg22.z(),leg22.t());//obj->leg2().leg2().p4(); 
     thep4M22 = TLorentzVector(leg21.x(),leg21.y(),leg21.z(),leg21.t());//obj->leg2().leg1().p4();
   }
  }
  double norm;
  double costheta1=-99;
  double costheta2=-99;
  double phi=-99; 
  double costhetastar=-99; 
  double phistar1=-99 ;
  double phistar2 =-99;
  double phistar12 = -99; 
  double phi1=-99; 
  double phi2=-99;
  
  TVector3 boostX = -(thep4H.BoostVector());
  TLorentzVector thep4Z1inXFrame( thep4Z1 );
  TLorentzVector thep4Z2inXFrame( thep4Z2 );	
  thep4Z1inXFrame.Boost( boostX );
  thep4Z2inXFrame.Boost( boostX );
  TVector3 theZ1X_p3 = TVector3( thep4Z1inXFrame.X(), thep4Z1inXFrame.Y(), thep4Z1inXFrame.Z() );
  TVector3 theZ2X_p3 = TVector3( thep4Z2inXFrame.X(), thep4Z2inXFrame.Y(), thep4Z2inXFrame.Z() );
  
  // calculate phi1, phi2, costhetastar
  phi1 = theZ1X_p3.Phi();
  phi2 = theZ2X_p3.Phi();
  
  ///////////////////////////////////////////////
  // check for z1/z2 convention, redefine all 4 vectors with convention
  ///////////////////////////////////////////////	
  TLorentzVector p4H, p4Z1, p4M11, p4M12, p4Z2, p4M21, p4M22;
  p4H = thep4H;
  if ((phi1 < 0)&&(phi1 >= -TMath::Pi())){
    p4Z1 = thep4Z2; p4M11 = thep4M21; p4M12 = thep4M22;
    p4Z2 = thep4Z1; p4M21 = thep4M11; p4M22 = thep4M12;		
    costhetastar = theZ2X_p3.CosTheta();
  }
  else{
    p4Z1 = thep4Z1; p4M11 = thep4M11; p4M12 = thep4M12;
    p4Z2 = thep4Z2; p4M21 = thep4M21; p4M22 = thep4M22;
    costhetastar = theZ1X_p3.CosTheta();
  }
  
  
  //std::cout << "phi1: " << phi1 << ", phi2: " << phi2 << std::endl;
	
  // now helicity angles................................
  // ...................................................
  TVector3 boostZ1 = -(p4Z1.BoostVector());
  TLorentzVector p4Z2Z1(p4Z2);
  p4Z2Z1.Boost(boostZ1);
  //find the decay axis
  /////TVector3 unitx_1 = -Hep3Vector(p4Z2Z1);
  TVector3 unitx_1( -p4Z2Z1.X(), -p4Z2Z1.Y(), -p4Z2Z1.Z() );
  norm = 1/(unitx_1.Mag());
  unitx_1*=norm;
  //boost daughters of z2
  TLorentzVector p4M21Z1(p4M21);
  TLorentzVector p4M22Z1(p4M22);
  p4M21Z1.Boost(boostZ1);
  p4M22Z1.Boost(boostZ1);
  //create z and y axes
  /////TVector3 unitz_1 = Hep3Vector(p4M21Z1).cross(Hep3Vector(p4M22Z1));
  TVector3 p4M21Z1_p3( p4M21Z1.X(), p4M21Z1.Y(), p4M21Z1.Z() );
  TVector3 p4M22Z1_p3( p4M22Z1.X(), p4M22Z1.Y(), p4M22Z1.Z() );
  TVector3 unitz_1 = p4M21Z1_p3.Cross( p4M22Z1_p3 );
  norm = 1/(unitz_1.Mag());
  unitz_1 *= norm;
  TVector3 unity_1 = unitz_1.Cross(unitx_1);
	
  //caculate theta1
  TLorentzVector p4M11Z1(p4M11);
  p4M11Z1.Boost(boostZ1);
  TVector3 p3M11( p4M11Z1.X(), p4M11Z1.Y(), p4M11Z1.Z() );
  TVector3 unitM11 = p3M11.Unit();
  double x_m11 = unitM11.Dot(unitx_1); double y_m11 = unitM11.Dot(unity_1); double z_m11 = unitM11.Dot(unitz_1);
  TVector3 M11_Z1frame(y_m11, z_m11, x_m11);
  costheta1 = M11_Z1frame.CosTheta();
  //std::cout << "theta1: " << M11_Z1frame.Theta() << std::endl;
  //////-----------------------old way of calculating phi---------------/////////
  phi = M11_Z1frame.Phi();
	
  //set axes for other system
  TVector3 boostZ2 = -(p4Z2.BoostVector());
  TLorentzVector p4Z1Z2(p4Z1);
  p4Z1Z2.Boost(boostZ2);
  TVector3 unitx_2( -p4Z1Z2.X(), -p4Z1Z2.Y(), -p4Z1Z2.Z() );
  norm = 1/(unitx_2.Mag());
  unitx_2*=norm;
  //boost daughters of z2
  TLorentzVector p4M11Z2(p4M11);
  TLorentzVector p4M12Z2(p4M12);
  p4M11Z2.Boost(boostZ2);
  p4M12Z2.Boost(boostZ2);
  TVector3 p4M11Z2_p3( p4M11Z2.X(), p4M11Z2.Y(), p4M11Z2.Z() );
  TVector3 p4M12Z2_p3( p4M12Z2.X(), p4M12Z2.Y(), p4M12Z2.Z() );
  TVector3 unitz_2 = p4M11Z2_p3.Cross( p4M12Z2_p3 );
  norm = 1/(unitz_2.Mag());
  unitz_2*=norm;
  TVector3 unity_2 = unitz_2.Cross(unitx_2);
  //calcuate theta2
  TLorentzVector p4M21Z2(p4M21);
  p4M21Z2.Boost(boostZ2);
  TVector3 p3M21( p4M21Z2.X(), p4M21Z2.Y(), p4M21Z2.Z() );
  TVector3 unitM21 = p3M21.Unit();
  double x_m21 = unitM21.Dot(unitx_2); double y_m21 = unitM21.Dot(unity_2); double z_m21 = unitM21.Dot(unitz_2);
  TVector3 M21_Z2frame(y_m21, z_m21, x_m21);
  costheta2 = M21_Z2frame.CosTheta();
	
  // calculate phi
  //calculating phi_n
  TLorentzVector n_p4Z1inXFrame( p4Z1 );
  TLorentzVector n_p4M11inXFrame( p4M11 );
  n_p4Z1inXFrame.Boost( boostX );
  n_p4M11inXFrame.Boost( boostX );        
  TVector3 n_p4Z1inXFrame_unit = n_p4Z1inXFrame.Vect().Unit();
  TVector3 n_p4M11inXFrame_unit = n_p4M11inXFrame.Vect().Unit();  
  TVector3 n_unitz_1( n_p4Z1inXFrame_unit );
  //// y-axis is defined by neg lepton cross z-axis
  //// the subtle part is here...
  //////////TVector3 n_unity_1 = n_p4M11inXFrame_unit.Cross( n_unitz_1 );
  TVector3 n_unity_1 = n_unitz_1.Cross( n_p4M11inXFrame_unit );
  TVector3 n_unitx_1 = n_unity_1.Cross( n_unitz_1 );
	
  TLorentzVector n_p4M21inXFrame( p4M21 );
  n_p4M21inXFrame.Boost( boostX );
  TVector3 n_p4M21inXFrame_unit = n_p4M21inXFrame.Vect().Unit();
  //rotate into other plane
  TVector3 n_p4M21inXFrame_unitprime( n_p4M21inXFrame_unit.Dot(n_unitx_1), n_p4M21inXFrame_unit.Dot(n_unity_1), n_p4M21inXFrame_unit.Dot(n_unitz_1) );
	
  ///////-----------------new way of calculating phi-----------------///////
  //double phi_n =  n_p4M21inXFrame_unitprime.Phi();
  /// and then calculate phistar1
  TVector3 n_p4PartoninXFrame_unit( 0.0, 0.0, 1.0 );
  TVector3 n_p4PartoninXFrame_unitprime( n_p4PartoninXFrame_unit.Dot(n_unitx_1), n_p4PartoninXFrame_unit.Dot(n_unity_1), n_p4PartoninXFrame_unit.Dot(n_unitz_1) );
  // negative sign is for arrow convention in paper
  phistar1 = (n_p4PartoninXFrame_unitprime.Phi());
	
  // and the calculate phistar2
  TLorentzVector n_p4Z2inXFrame( p4Z2 );
  n_p4Z2inXFrame.Boost( boostX );
  TVector3 n_p4Z2inXFrame_unit = n_p4Z2inXFrame.Vect().Unit();
  ///////TLorentzVector n_p4M21inXFrame( p4M21 );
  //////n_p4M21inXFrame.Boost( boostX );        
  ////TVector3 n_p4M21inXFrame_unit = n_p4M21inXFrame.Vect().Unit();  
  TVector3 n_unitz_2( n_p4Z2inXFrame_unit );
  //// y-axis is defined by neg lepton cross z-axis
  //// the subtle part is here...
  //////TVector3 n_unity_2 = n_p4M21inXFrame_unit.Cross( n_unitz_2 );
  TVector3 n_unity_2 = n_unitz_2.Cross( n_p4M21inXFrame_unit );
  TVector3 n_unitx_2 = n_unity_2.Cross( n_unitz_2 );
  TVector3 n_p4PartoninZ2PlaneFrame_unitprime( n_p4PartoninXFrame_unit.Dot(n_unitx_2), n_p4PartoninXFrame_unit.Dot(n_unity_2), n_p4PartoninXFrame_unit.Dot(n_unitz_2) );
  phistar2 = (n_p4PartoninZ2PlaneFrame_unitprime.Phi());
	
  double phistar12_0 = phistar1 + phistar2;
  if (phistar12_0 > TMath::Pi()) phistar12 = phistar12_0 - 2*TMath::Pi();
  else if (phistar12_0 < (-1.)*TMath::Pi()) phistar12 = phistar12_0 + 2*TMath::Pi();
  else phistar12 = phistar12_0;
	
  obj->costhetastar_ = costhetastar;
  obj->helphi_ = phi;
  obj->helphiZ1_ = phi1;
  obj->helphiZ2_ = phi2;
  obj->helcosthetaZ1_ = costheta1;
  obj->helcosthetaZ2_ = costheta2;
  obj->phistarZ1_ = phistar1;
  obj->phistarZ2_ = phistar2; 
}



/* initial implementation on the example of 2l2j
template<typename T, typename U> void cmg::HiggsCandidateFactory<T, U>::set(const cmg::DiObject<T,U>& in, cmg::HiggsCandidate<T,U>* const obj) const{
  double costhetastar=-77.0;
  double helphi=-77.0;
  double helphiZ1=-77.0;
  double helphiZ2=-77.0;
  double helcosthetaZ1=-77.0;
  double helcosthetaZ2=-77.0;
  double phistarZ1=+33.0, phistarZ2=-33.0;

  ///////////////////////////////////////
  //TO DO: implement the choice of Z1
  //////////////////////////////////////

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
*/
#endif
