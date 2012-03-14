#ifndef HIGGSCANDIDATE_H_
#define HIGGSCANDIDATE_H_

#include "AnalysisDataFormats/CMGTools/interface/DiObject.h"

#include "AnalysisDataFormats/CMGTools/interface/UnSet.h"


namespace cmg {

  template <typename T, typename U> class HiggsCandidateFactory;

  template< typename TL1, typename TL2 > class HiggsCandidate : public DiObject<TL1,TL2>{
  public:
    HiggsCandidate(): 
      DiObject<TL1,TL2>(),
      costhetastar_(UnSet(Double_t)),
      helphi_(UnSet(Double_t)),
      helphiZ1_(UnSet(Double_t)),
      helphiZ2_(UnSet(Double_t)),
      helcosthetaZ1_(UnSet(Double_t)),
      helcosthetaZ2_(UnSet(Double_t)),
      phistarZ1_(UnSet(Double_t)),
      phistarZ2_(UnSet(Double_t)),
      userFloatLabels_(),
      userFloats_(){      
    }
    HiggsCandidate(const HiggsCandidate<TL1,TL2>& other):
      DiObject<TL1,TL2>(other),
      costhetastar_(other.costhetastar_),
      helphi_(other.helphi_),
      helphiZ1_(other.helphiZ1_),
      helphiZ2_(other.helphiZ2_),
      helcosthetaZ1_(other.helcosthetaZ1_),
      helcosthetaZ2_(other.helcosthetaZ2_),
      phistarZ1_(other.phistarZ1_),
      phistarZ2_(other.phistarZ2_),
      userFloatLabels_(other.userFloatLabels_),
      userFloats_(other.userFloats_){
    }
    HiggsCandidate(const DiObject<TL1,TL2>& other):
      DiObject<TL1,TL2>(other),
      costhetastar_(UnSet(Double_t)),
      helphi_(UnSet(Double_t)),
      helphiZ1_(UnSet(Double_t)),
      helphiZ2_(UnSet(Double_t)),
      helcosthetaZ1_(UnSet(Double_t)),
      helcosthetaZ2_(UnSet(Double_t)),
      phistarZ1_(UnSet(Double_t)),
      phistarZ2_(UnSet(Double_t)),
      userFloatLabels_(),
      userFloats_(){
   }

    virtual ~HiggsCandidate(){}

    Double_t costhetastar() const{ return costhetastar_;}
    Double_t helphi() const{ return helphi_;}
    Double_t helphiZl1() const{ return helphiZ1_;}
    Double_t helphiZl2() const{ return helphiZ2_;}
    Double_t helcosthetaZl1() const{ return helcosthetaZ1_;}
    Double_t helcosthetaZl2() const{ return helcosthetaZ2_;}
    Double_t phistarZl1() const{ return phistarZ1_;}
    Double_t phistarZl2() const{ return phistarZ2_;}

    float userFloat( const std::string & key ) const;
    float userFloat( const char* key ) const {return userFloat(std::string(key));};
    void addUserFloat( const  std::string & label, float data );
    const std::vector<std::string> & userFloatNames() const  { return userFloatLabels_; }
    bool hasUserFloat( const char * key ) const { return hasUserFloat(std::string(key)); }
    bool hasUserFloat( const std::string & key ) const {
      return std::find(userFloatLabels_.begin(), userFloatLabels_.end(), key) != userFloatLabels_.end();
    }
        
  private:
    Double_t costhetastar_;
    Double_t helphi_;
    Double_t helphiZ1_;
    Double_t helphiZ2_;
    Double_t helcosthetaZ1_;
    Double_t helcosthetaZ2_;
    Double_t phistarZ1_;
    Double_t phistarZ2_;

    std::vector<std::string>      userFloatLabels_;
    std::vector<float>            userFloats_;

    friend class cmg::HiggsCandidateFactory<TL1,TL2>;
    
  };

  template< typename TL1, typename TL2 >
  float HiggsCandidate<TL1,TL2>::userFloat( const std::string &key ) const
  {
    std::vector<std::string>::const_iterator it = std::find(userFloatLabels_.begin(), userFloatLabels_.end(), key);
    if (it != userFloatLabels_.end()) {
    return userFloats_[it - userFloatLabels_.begin()];
    }
    return 0.0;
  }
  
  template< typename TL1, typename TL2 >
  void HiggsCandidate<TL1,TL2>::addUserFloat( const std::string & label, float data )
  {
    userFloatLabels_.push_back(label);
    userFloats_.push_back( data );
  }
  
}

#endif
