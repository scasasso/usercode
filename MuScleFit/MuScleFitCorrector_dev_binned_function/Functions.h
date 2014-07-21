/**
 * Scale function classes
 * Author M. De Mattia - 18/11/2008
 * Author S. Casasso   - 25/10/2012
 * Author E. Migliore  - 25/10/2012
 */

#include <iostream>
#include <vector>
#include <cmath>
#include "TMath.h"
#include "TString.h"
#include "TF1.h"
#include "TRandom.h"

/**
 * Used to define parameters inside the functions.
 */

  struct ParSet
  {
    ParSet() {}
    ParSet(const TString & inputName, const double & inputStep, const double & inputMini, const double & inputMaxi) :
      step(inputStep),
      mini(inputMini),
      maxi(inputMaxi)
    {
      std::cout << "setting name = " << inputName << std::endl;
      name = inputName;
    }
    TString name;
    double step, mini, maxi;
  };
  
  
// ----------------------- //
//     Scale functors      //
// ----------------------- //

template <class T>
class scaleFunctionBase {
 public:
  virtual double scale(const double & pt, const double & eta, const double & phi, const int chg, const T & parScale) const = 0;
  virtual ~scaleFunctionBase() = 0;
  virtual int parNum() const { return parNum_; }
 protected:
  int parNum_;
  virtual void setPar(double* Start, double* Step, double* Mini, double* Maxi, int* ind,
		      TString* parname, const T & parResol, const std::vector<int> & parResolOrder, const std::vector<ParSet> & parSet ) {
    if( int(parSet.size()) != this->parNum_ ) {
      std::cout << "Error: wrong number of parameter initializations = " << parSet.size() << ". Number of parameters is " << this->parNum_ << std::endl;
      exit(1);
    }
    for( int iPar=0; iPar<this->parNum_; ++iPar ) {
      Start[iPar] = parResol[iPar];
      Step[iPar] = parSet[iPar].step;
      Mini[iPar] = parSet[iPar].mini;
      Maxi[iPar] = parSet[iPar].maxi;
      ind[iPar] = parResolOrder[iPar];
      parname[iPar] = parSet[iPar].name;
    }
  }
};
  
template <class T> inline scaleFunctionBase<T>::~scaleFunctionBase() { }  // defined even though it's pure virtual; should be faster this way.
  
  
  
//
// Curvature: (linear eta + sinusoidal in phi (both in 5 eta bins)) * global scale 
// ------------------------------------------------------------
template <class T>
class scaleFunction50 : public scaleFunctionBase<T> {
 public:
  scaleFunction50() { this->parNum_ = 27; }
  virtual double scale(const double & pt, const double & eta, const double & phi, const int chg, const T & parScale) const {    
    double ampl(0), phase(0), twist(0), ampl2(0), freq2(0), phase2(0);
      
    // very bwd bin
    if ( eta  < parScale[4] ) {
      ampl = parScale[1]; phase = parScale[2]; ampl2 = parScale[21]; freq2 = parScale[22]; phase2 = parScale[23];
      twist = parScale[3]*(eta-parScale[4])+parScale[7]*(parScale[4]-parScale[8])+parScale[11]*parScale[8]; 
      // bwd bin
    } else if ( parScale[4] <= eta && eta < parScale[8] ) {
      ampl = parScale[5]; phase = parScale[6];
      twist = parScale[7]*(eta-parScale[8])+parScale[11]*parScale[8] ; 
      // barrel bin
    } else if ( parScale[8] <= eta && eta < parScale[12] ) {
      ampl = parScale[9]; phase = parScale[10];
      twist = parScale[11]*eta; 
      // fwd bin
    } else if ( parScale[12] <= eta && eta < parScale[16] ) {
      ampl = parScale[13]; phase = parScale[14];
      twist = parScale[15]*(eta-parScale[12])+parScale[11]*parScale[12]; 
      // very fwd bin
    } else if ( parScale[16] < eta ) {
      ampl = parScale[17]; phase = parScale[18]; ampl2 = parScale[24]; freq2 = parScale[25]; phase2 = parScale[26];
      twist = parScale[19]*(eta-parScale[16])+parScale[15]*(parScale[16]-parScale[12])+parScale[11]*parScale[12]; 
    }
      
    // apply the correction
    double curv = (1.+parScale[0])*((double)chg/pt
				    -twist
				    -ampl*sin(phi+phase)
				    -ampl2*sin(freq2*phi+phase2)
				    -0.5*parScale[20]);
    return 1./((double)chg*curv);
  }
    
};


//
// Curvature: binned function 
// Same as type60 (good results on Legacy 2011 MC), but different binning
// - phi bins = [8,8,8,8,8,8,8] in 7 eta bins
// ------------------------------------------------------------
template <class T>
class scaleFunction62 : public scaleFunctionBase<T> {
 public:
  scaleFunction62() { 
    this->parNum_ = 57; 
  }
  virtual double scale(const double & pt, const double & eta, const double & phi, const int chg, const T & parScale) const {    
    double deltaK(0);
    double p0 = parScale[0];
    
    
    if ( eta<-2.1 && eta>-2.4 && phi<-2.35619449019 && phi>-3.14159265359 ) deltaK = parScale[1];
    else if ( eta<-2.1 && eta>-2.4 && phi<-1.57079632679 && phi>-2.35619449019 ) deltaK = parScale[2];
    else if ( eta<-2.1 && eta>-2.4 && phi<-0.785398163397 && phi>-1.57079632679 ) deltaK = parScale[3];
    else if ( eta<-2.1 && eta>-2.4 && phi<0.0 && phi>-0.785398163397 ) deltaK = parScale[4];
    else if ( eta<-2.1 && eta>-2.4 && phi<0.785398163397 && phi>0.0 ) deltaK = parScale[5];
    else if ( eta<-2.1 && eta>-2.4 && phi<1.57079632679 && phi>0.785398163397 ) deltaK = parScale[6];
    else if ( eta<-2.1 && eta>-2.4 && phi<2.35619449019 && phi>1.57079632679 ) deltaK = parScale[7];
    else if ( eta<-2.1 && eta>-2.4 && phi<3.14159265359 && phi>2.35619449019 ) deltaK = parScale[8];
    else if ( eta<-1.5 && eta>-2.1 && phi<-2.35619449019 && phi>-3.14159265359 ) deltaK = parScale[9];
    else if ( eta<-1.5 && eta>-2.1 && phi<-1.57079632679 && phi>-2.35619449019 ) deltaK = parScale[10];
    else if ( eta<-1.5 && eta>-2.1 && phi<-0.785398163397 && phi>-1.57079632679 ) deltaK = parScale[11];
    else if ( eta<-1.5 && eta>-2.1 && phi<0.0 && phi>-0.785398163397 ) deltaK = parScale[12];
    else if ( eta<-1.5 && eta>-2.1 && phi<0.785398163397 && phi>0.0 ) deltaK = parScale[13];
    else if ( eta<-1.5 && eta>-2.1 && phi<1.57079632679 && phi>0.785398163397 ) deltaK = parScale[14];
    else if ( eta<-1.5 && eta>-2.1 && phi<2.35619449019 && phi>1.57079632679 ) deltaK = parScale[15];
    else if ( eta<-1.5 && eta>-2.1 && phi<3.14159265359 && phi>2.35619449019 ) deltaK = parScale[16];
    else if ( eta<-0.9 && eta>-1.5 && phi<-2.35619449019 && phi>-3.14159265359 ) deltaK = parScale[17];
    else if ( eta<-0.9 && eta>-1.5 && phi<-1.57079632679 && phi>-2.35619449019 ) deltaK = parScale[18];
    else if ( eta<-0.9 && eta>-1.5 && phi<-0.785398163397 && phi>-1.57079632679 ) deltaK = parScale[19];
    else if ( eta<-0.9 && eta>-1.5 && phi<0.0 && phi>-0.785398163397 ) deltaK = parScale[20];
    else if ( eta<-0.9 && eta>-1.5 && phi<0.785398163397 && phi>0.0 ) deltaK = parScale[21];
    else if ( eta<-0.9 && eta>-1.5 && phi<1.57079632679 && phi>0.785398163397 ) deltaK = parScale[22];
    else if ( eta<-0.9 && eta>-1.5 && phi<2.35619449019 && phi>1.57079632679 ) deltaK = parScale[23];
    else if ( eta<-0.9 && eta>-1.5 && phi<3.14159265359 && phi>2.35619449019 ) deltaK = parScale[24];
    else if ( eta<0.9 && eta>-0.9 && phi<-2.35619449019 && phi>-3.14159265359 ) deltaK = parScale[25];
    else if ( eta<0.9 && eta>-0.9 && phi<-1.57079632679 && phi>-2.35619449019 ) deltaK = parScale[26];
    else if ( eta<0.9 && eta>-0.9 && phi<-0.785398163397 && phi>-1.57079632679 ) deltaK = parScale[27];
    else if ( eta<0.9 && eta>-0.9 && phi<0.0 && phi>-0.785398163397 ) deltaK = parScale[28];
    else if ( eta<0.9 && eta>-0.9 && phi<0.785398163397 && phi>0.0 ) deltaK = parScale[29];
    else if ( eta<0.9 && eta>-0.9 && phi<1.57079632679 && phi>0.785398163397 ) deltaK = parScale[30];
    else if ( eta<0.9 && eta>-0.9 && phi<2.35619449019 && phi>1.57079632679 ) deltaK = parScale[31];
    else if ( eta<0.9 && eta>-0.9 && phi<3.14159265359 && phi>2.35619449019 ) deltaK = parScale[32];
    else if ( eta<1.5 && eta>0.9 && phi<-2.35619449019 && phi>-3.14159265359 ) deltaK = parScale[33];
    else if ( eta<1.5 && eta>0.9 && phi<-1.57079632679 && phi>-2.35619449019 ) deltaK = parScale[34];
    else if ( eta<1.5 && eta>0.9 && phi<-0.785398163397 && phi>-1.57079632679 ) deltaK = parScale[35];
    else if ( eta<1.5 && eta>0.9 && phi<0.0 && phi>-0.785398163397 ) deltaK = parScale[36];
    else if ( eta<1.5 && eta>0.9 && phi<0.785398163397 && phi>0.0 ) deltaK = parScale[37];
    else if ( eta<1.5 && eta>0.9 && phi<1.57079632679 && phi>0.785398163397 ) deltaK = parScale[38];
    else if ( eta<1.5 && eta>0.9 && phi<2.35619449019 && phi>1.57079632679 ) deltaK = parScale[39];
    else if ( eta<1.5 && eta>0.9 && phi<3.14159265359 && phi>2.35619449019 ) deltaK = parScale[40];
    else if ( eta<2.1 && eta>1.5 && phi<-2.35619449019 && phi>-3.14159265359 ) deltaK = parScale[41];
    else if ( eta<2.1 && eta>1.5 && phi<-1.57079632679 && phi>-2.35619449019 ) deltaK = parScale[42];
    else if ( eta<2.1 && eta>1.5 && phi<-0.785398163397 && phi>-1.57079632679 ) deltaK = parScale[43];
    else if ( eta<2.1 && eta>1.5 && phi<0.0 && phi>-0.785398163397 ) deltaK = parScale[44];
    else if ( eta<2.1 && eta>1.5 && phi<0.785398163397 && phi>0.0 ) deltaK = parScale[45];
    else if ( eta<2.1 && eta>1.5 && phi<1.57079632679 && phi>0.785398163397 ) deltaK = parScale[46];
    else if ( eta<2.1 && eta>1.5 && phi<2.35619449019 && phi>1.57079632679 ) deltaK = parScale[47];
    else if ( eta<2.1 && eta>1.5 && phi<3.14159265359 && phi>2.35619449019 ) deltaK = parScale[48];
    else if ( eta<2.4 && eta>2.1 && phi<-2.35619449019 && phi>-3.14159265359 ) deltaK = parScale[49];
    else if ( eta<2.4 && eta>2.1 && phi<-1.57079632679 && phi>-2.35619449019 ) deltaK = parScale[50];
    else if ( eta<2.4 && eta>2.1 && phi<-0.785398163397 && phi>-1.57079632679 ) deltaK = parScale[51];
    else if ( eta<2.4 && eta>2.1 && phi<0.0 && phi>-0.785398163397 ) deltaK = parScale[52];
    else if ( eta<2.4 && eta>2.1 && phi<0.785398163397 && phi>0.0 ) deltaK = parScale[53];
    else if ( eta<2.4 && eta>2.1 && phi<1.57079632679 && phi>0.785398163397 ) deltaK = parScale[54];
    else if ( eta<2.4 && eta>2.1 && phi<2.35619449019 && phi>1.57079632679 ) deltaK = parScale[55];
    else if ( eta<2.4 && eta>2.1 && phi<3.14159265359 && phi>2.35619449019 ) deltaK = parScale[56];
    else {
      std::cout << "This should really not happen, this muon has eta = " << eta << "and phi = " << phi << std::endl;
      exit(1);
    }
    
    // apply the correction
    double curv = (double)chg/pt;
    return 1./((double)chg*(1+p0)*(curv+deltaK));
  }

};

  
  
// ----------------------- //
//   Resolution functors   //
// ----------------------- //
  
template <class T>
class resolutionFunctionBase {
 public:
  virtual double sigmaPt(const double & pt, const double & eta, const T & parval) = 0;
    
  resolutionFunctionBase() {}
  virtual ~resolutionFunctionBase() = 0;
  virtual int parNum() const { return parNum_; }
    
 protected:
  int parNum_;
};
template <class T> inline resolutionFunctionBase<T>::~resolutionFunctionBase() { }  // defined even though it's pure virtual; should be faster this way.
  
  
template <class T>
class resolutionFunction45 : public resolutionFunctionBase<T> {
 public:
  resolutionFunction45() { this->parNum_ = 13; }

  inline double getGEO(const double & pt, const double & eta, const T & parval){
    return parval[0];
  }

  inline double getMS(const double & pt, const double & eta, const T & parval){
    if( eta < -2.0 ) return( parval[1] );
    if( eta < -1.8 ) return( parval[2] );
    if( eta < -1.6 ) return( parval[3] );
    if( eta < -1.2 ) return( parval[4] );
    if( eta < -0.8 ) return( parval[5] );
    if( eta < 0. )   return( parval[6] );
    if( eta < 0.8 )  return( parval[7] );
    if( eta < 1.2 )  return( parval[8] );
    if( eta < 1.6 )  return( parval[9] );
    if( eta < 1.8 )  return( parval[10] );
    if( eta < 2.0 )  return( parval[11] );
    return( parval[12] );      
  }
    
  virtual double sigmaPt(const double & pt, const double & eta, const T & parval)
  {
    return pt*getGEO(pt,eta,parval) + getMS(pt,eta,parval);
  }
    
};
  
template <class T>
class resolutionFunction46 : public resolutionFunctionBase<T> {
 public:
  resolutionFunction46() { this->parNum_ = 13; }
    
  int etaBin(const double & eta)
  {
      
    // std::cout << "for eta = " << eta << ", bin = " << bin << std::endl;
      
    if( eta < -2.0 ) return 1;
    if( eta < -1.8 ) return 2;
    if( eta < -1.6 ) return 3;
    if( eta < -1.2 ) return 4;
    if( eta < -0.8 ) return 5;
    if( eta < 0. )  return 6;
    if( eta < 0.8 ) return 7;
    if( eta < 1.2 ) return 8;
    if( eta < 1.6 ) return 9;
    if( eta < 1.8 ) return 10;
    if( eta < 2.0 ) return 11;
    return 12;
  }
    
  virtual double sigmaPt(const double & pt, const double & eta, const T & parval)
  {
    return sqrt(pow(parval[0]*pt,2) + pow(parval[etaBin(eta)],2));
  }
    
};
  
  
// parametrization as sum in quadrature
// Geometric and MSC both as function of eta, adding straight lines between parabolas wrt type51
template <class T>
class resolutionFunction57 : public resolutionFunctionBase<T> {
 public:
  resolutionFunction57() { this->parNum_ = 17; }
    
  inline double getGEO(const double & pt, const double & eta, const T & parval){
    // geometrical term
    double qGEO(0);
    if ( eta < parval[0] ) {
      qGEO = parval[10]*(eta-parval[0])*(eta-parval[0])+parval[11];
    } else if ( parval[0] <= eta && eta < parval[3] ) {
      qGEO = parval[11];
    } else {
      qGEO = parval[12]*(eta-parval[3])*(eta-parval[3])+parval[11];
    }
    return qGEO;
  }
    
  inline double centralParabola(const double & pt, const double & eta, const T & parval){
    return parval[4] + parval[5]*eta*eta;
  }
    
  inline double middleParabola(const double & pt, const double & eta, const T & parval){
    return parval[15] + parval[16]*eta*eta;
  }
    
  inline double leftParabola(const double & pt, const double & eta, const T & parval){
    return parval[6] + parval[7]*(eta-parval[0])*(eta-parval[0]);
  }
    
  inline double rightParabola(const double & pt, const double & eta, const T & parval){
    return parval[8] + parval[9]*(eta-parval[3])*(eta-parval[3]);
  }
    
  inline double leftLine(const double & pt, const double & eta, const T & parval){
    double x_1 = parval[13];
    double y_1 = middleParabola(pt, parval[13], parval);
    double x_2 = parval[0];
    double y_2 = leftParabola(pt, parval[0], parval);
    return( (eta - x_1)*(y_2 - y_1)/(x_2 - x_1) + y_1 );
  }
    
  inline double rightLine(const double & pt, const double & eta, const T & parval){
    double x_1 = parval[14];
    double y_1 = middleParabola(pt, parval[14], parval);
    double x_2 = parval[3];
    double y_2 = rightParabola(pt, parval[3], parval);
    return( (eta - x_1)*(y_2 - y_1)/(x_2 - x_1) + y_1 );
  }
    
    
  inline double getMSC(const double & pt, const double & eta, const T & parval){
    // MSC term
    double qMSC(0);   
    if ( eta < parval[0] ) {
      qMSC = leftParabola(pt,eta,parval);
    } else if ( parval[0] <= eta && eta < parval[13] ) {
      qMSC = leftLine(pt,eta,parval);
    } else if ( parval[13] <= eta && eta < parval[1] ) {
      qMSC = middleParabola(pt,eta,parval);
    } else if ( parval[1] <= eta && eta < parval[2] ) {
      qMSC = centralParabola(pt,eta,parval);
    } else if ( parval[2] <= eta && eta < parval[14] ) {
      qMSC = middleParabola(pt,eta,parval);
    } else if ( parval[14] <= eta && eta < parval[3] ) {
      qMSC = rightLine(pt,eta,parval);
    } else {
      qMSC = rightParabola(pt,eta,parval);
    }
    return qMSC;
  }
    
  virtual double sigmaPt(const double & pt, const double & eta, const T & parval)
  {
    double qGEO = getGEO(pt,  eta,  parval);
    double qMSC = getMSC(pt,  eta,  parval);
    return sqrt(pow(qGEO*pt,2) + pow(qMSC,2));
  }
};



// Service to build the scale functor corresponding to the passed identifier                                                                               
scaleFunctionBase<double * > * scaleFunctionService( const int identifier ){
  switch ( identifier ) {
  case ( 50 ): return ( new scaleFunction50<double * > ); break;
  case ( 62 ): return ( new scaleFunction62<double * > ); break;
  default: std::cout << "scaleFunctionService error: wrong identifier = " << identifier << std::endl; exit(1);
  }
}


// Service to build the resolution functor corresponding to the passed identifier                                                                               
resolutionFunctionBase<double * > * resolutionFunctionService( const int identifier ){
  switch ( identifier ) {
  case ( 45 ): return ( new resolutionFunction45<double * > ); break;
  case ( 46 ): return ( new resolutionFunction46<double * > ); break;
  case ( 57 ): return ( new resolutionFunction57<double * > ); break;
  default: std::cout << "resolutionFunctService error: wrong identifier = " << identifier << std::endl; exit(1);
  }
}

