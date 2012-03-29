/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "RooXZsZs_5D.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

//ClassImp(RooXZsZs_5D) 

RooXZsZs_5D::RooXZsZs_5D(const char *name, const char *title, 
                         RooAbsReal& _m1,
                         RooAbsReal& _m2,
                         RooAbsReal& _h1,
                         RooAbsReal& _h2,
                         RooAbsReal& _Phi,
                         RooAbsReal& _a1Val,
                         RooAbsReal& _phi1Val,
                         RooAbsReal& _a2Val,
                         RooAbsReal& _phi2Val,
                         RooAbsReal& _a3Val,
                         RooAbsReal& _phi3Val,
                         RooAbsReal& _mZ,
                         RooAbsReal& _gamZ,
                         RooAbsReal& _mX,
                         RooAbsReal& _R1Val,
                         RooAbsReal& _R2Val) :
RooAbsPdf(name,title), 
m1("m1","m1",this,_m1),
m2("m2","m2",this,_m2),
h1("h1","h1",this,_h1),
h2("h2","h2",this,_h2),
Phi("Phi","Phi",this,_Phi),
a1Val("a1Val","a1Val",this,_a1Val),
phi1Val("phi1Val","phi1Val",this,_phi1Val),
a2Val("a2Val","a2Val",this,_a2Val),
phi2Val("phi2Val","phi2Val",this,_phi2Val),
a3Val("a3Val","a3Val",this,_a3Val),
phi3Val("phi3Val","phi3Val",this,_phi3Val),
mZ("mZ","mZ",this,_mZ),
gamZ("gamZ","gamZ",this,_gamZ),
mX("mX","mX",this,_mX),
R1Val("R1Val","R1Val",this,_R1Val),
R2Val("R2Val","R2Val",this,_R2Val)
{ 
} 


RooXZsZs_5D::RooXZsZs_5D(const RooXZsZs_5D& other, const char* name) :  
RooAbsPdf(other,name), 
m1("m1",this,other.m1),
m2("m2",this,other.m2),
h1("h1",this,other.h1),
h2("h2",this,other.h2),
Phi("Phi",this,other.Phi),
a1Val("a1Val",this,other.a1Val),
phi1Val("phi1Val",this,other.phi1Val),
a2Val("a2Val",this,other.a2Val),
phi2Val("phi2Val",this,other.phi2Val),
a3Val("a3Val",this,other.a3Val),
phi3Val("phi3Val",this,other.phi3Val),
mZ("mZ",this,other.mZ),
gamZ("gamZ",this,other.gamZ),
mX("mX",this,other.mX),
R1Val("R1Val",this,other.R1Val),
R2Val("R2Val",this,other.R2Val)
{ 
} 



Double_t RooXZsZs_5D::evaluate() const 
{ 
    // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
    //   const Double_t VEV = 246.;
    Double_t sh1 = sqrt(1-h1*h1);
    Double_t sh2 = sqrt(1-h2*h2);        
    
    // definition of helicity amplitudes
    Double_t chi = (mX*mX-m1*m1-m2*m2)/(2.*m2*m1);
    Double_t eta = (m1*m2)/pow(mX,2);
    
    // condition to avoid NaN PDF
    // data should be variable changed to avoid this though
    if (chi<1) chi = 1;
    
    if (m1 < m2) return 1e-9;
    double nanval = sqrt((1 - TMath::Power(m1 - m2,2)/TMath::Power(mX,2))*(1 - TMath::Power(m1 + m2,2)/TMath::Power(mX,2)));
    if (nanval != nanval) return 1e-9;
    
    Double_t f00Val = (a1Val*a1Val*chi*chi+pow(a2Val,2)*pow(eta,2)*(chi*chi-1.)*(chi*chi-1.)+2.*a1Val*a2Val*chi*(chi*chi-1)*eta*cos(phi1Val-phi2Val));
    Double_t fppVal = (a1Val*a1Val+pow(a3Val,2)*pow(eta,2)*(chi*chi-1));
    Double_t fmmVal = (a1Val*a1Val+pow(a3Val,2)*pow(eta,2)*(chi*chi-1));
    Double_t phi00Val = atan2(a1Val*sin(phi1Val)+a2Val*eta*(chi*chi-1)*sin(phi2Val),a1Val*cos(phi1Val)+a2Val*eta*(chi*chi-1)*cos(phi2Val));
    Double_t phippVal = atan2(a1Val*sin(phi1Val)+a3Val*eta*sqrt(chi*chi-1)*sin(phi3Val),a1Val*cos(phi3Val)-a3Val*eta*sqrt(chi*chi-1)*cos(phi3Val));
    Double_t phimmVal = atan2(a1Val*sin(phi1Val)-a3Val*eta*sqrt(chi*chi-1)*sin(phi3Val),a1Val*cos(phi3Val)+a3Val*eta*sqrt(chi*chi-1)*cos(phi3Val));
    
    Double_t betaValSquared = (1.-(pow(m1-m2,2)/pow(mX,2)))*(1.-(pow(m1+m2,2)/pow(mX,2)));
    Double_t betaVal = sqrt(betaValSquared);

    Double_t term1Coeff = (pow(m1,3))/( (pow(m1,2)-pow(mZ,2))*(pow(m1,2)-pow(mZ,2))+pow(mZ,2)*pow(gamZ,2) );
    Double_t term2Coeff = (pow(m2,3))/( (pow(m2,2)-pow(mZ,2))*(pow(m2,2)-pow(mZ,2))+pow(mZ,2)*pow(gamZ,2) );
    
    Double_t term1A = 4.*f00Val*pow(sh1,2)*pow(sh2,2);
    Double_t term1B = (fppVal+fmmVal)*((1.+h1*h1)*(1.+h2*h2)+4.*R1Val*R2Val*h1*h2);
    Double_t term1C = -2.*(fppVal-fmmVal)*(R1Val*h1*(1.+h2*h2)+R2Val*h2*(1.+h1*h1));
    Double_t term1D = 4.*sqrt(fppVal*f00Val)*(R1Val-h1)*(R2Val-h2)*sh1*sh2*cos(Phi+phippVal-phi00Val);
    Double_t term1E = 4.*sqrt(fmmVal*f00Val)*(R1Val+h1)*(R2Val+h2)*sh1*sh2*cos(Phi-phimmVal+phi00Val);
    Double_t term1F = 2.*sqrt(fppVal*fmmVal)*pow(sh1,2)*pow(sh2,2)*cos(2.*Phi+phippVal-phimmVal);
    Double_t term1 = betaVal*term1Coeff*term2Coeff*(term1A+term1B+term1C+term1D+term1E+term1F);
    
    //Double_t para0 = 5.169254e-01;
    //Double_t para1 =-1.004152e-02;
    //Double_t para2 = 3.543577e-04;
    
    //Double_t accp = para0 + para1*m2 + para2*m2*m2;
    Double_t accp = 1.;
    
    //std::cout << "term1: " << term1 << "... coeff: " << (term1Coeff*term2Coeff) << std::endl;
    
    return term1*accp;
    
    
} 


Int_t RooXZsZs_5D::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const
{
    if (matchArgs(allVars,analVars,Phi,h1)) return 3 ;
    if (matchArgs(allVars,analVars,Phi,h2)) return 4 ;
    if (matchArgs(allVars,analVars,h1,h2)) return 5 ;
    if (matchArgs(allVars,analVars,h1,h2,Phi)) return 6 ;
    return 0 ;
}
Double_t RooXZsZs_5D::analyticalIntegral(Int_t code, const char* rangeName) const
{
    
    switch(code)
    {
            
        case 3:
        {
            // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
            //   const Double_t VEV = 246.;
            Double_t sh1 = sqrt(1-h1*h1);
            Double_t sh2 = sqrt(1-h2*h2);        
            
            // definition of helicity amplitudes
            Double_t chi = (mX*mX-m1*m1-m2*m2)/(2.*m2*m1);
            Double_t eta = (m1*m2)/pow(mX,2);
            
            // condition to avoid NaN PDF
            // data should be variable changed to avoid this though
            if (chi<1) chi = 1;
            
            if (m1 < m2) return 1e-9;
            double nanval = sqrt((1 - TMath::Power(m1 - m2,2)/TMath::Power(mX,2))*(1 - TMath::Power(m1 + m2,2)/TMath::Power(mX,2)));
            if (nanval != nanval) return 1e-9;
            
            Double_t f00Val = (a1Val*a1Val*chi*chi+pow(a2Val,2)*pow(eta,2)*(chi*chi-1.)*(chi*chi-1.)+2.*a1Val*a2Val*chi*(chi*chi-1)*eta*cos(phi1Val-phi2Val));
            Double_t fppVal = (a1Val*a1Val+pow(a3Val,2)*pow(eta,2)*(chi*chi-1)+2.*a1Val*a3Val*chi*sqrt(chi*chi-1)*eta*cos(phi1Val-phi3Val));
            Double_t fmmVal = (a1Val*a1Val+pow(a3Val,2)*pow(eta,2)*(chi*chi-1)+2.*a1Val*a3Val*chi*sqrt(chi*chi-1)*eta*cos(phi1Val-phi3Val));
            Double_t phi00Val = atan2(a1Val*sin(phi1Val)+a2Val*eta*(chi*chi-1)*sin(phi2Val),a1Val*cos(phi1Val)+a2Val*eta*(chi*chi-1)*cos(phi2Val));
            Double_t phippVal = atan2(a1Val*sin(phi1Val)+a3Val*eta*sqrt(chi*chi-1)*sin(phi3Val),a1Val*cos(phi3Val)-a3Val*eta*sqrt(chi*chi-1)*cos(phi3Val));
            Double_t phimmVal = atan2(a1Val*sin(phi1Val)-a3Val*eta*sqrt(chi*chi-1)*sin(phi3Val),a1Val*cos(phi3Val)+a3Val*eta*sqrt(chi*chi-1)*cos(phi3Val));
            
            Double_t betaValSquared = (1.-(pow(m1-m2,2)/pow(mX,2)))*(1.-(pow(m1+m2,2)/pow(mX,2)));
            Double_t betaVal = sqrt(betaValSquared);
            
            Double_t term1Coeff = (pow(m1,3))/( (pow(m1,2)-pow(mZ,2))*(pow(m1,2)-pow(mZ,2))+pow(mZ,2)*pow(gamZ,2) );
            Double_t term2Coeff = (pow(m2,3))/( (pow(m2,2)-pow(mZ,2))*(pow(m2,2)-pow(mZ,2))+pow(mZ,2)*pow(gamZ,2) );
            
            // FOR THE INTEGRATIONS, ONLY THESE LINES SHOULD CHANGE
            // cform --> still have to change "sqrt" and "cos" and "Pi" and "Power" and "R1" and "R2"
            Double_t term1A = (-32*f00Val*TMath::Pi()*(-1 + TMath::Power(h2,2)))/3.;
            Double_t term1B = (16*(fmmVal + fppVal)*TMath::Pi()*(1 + TMath::Power(h2,2)))/3.;
            Double_t term1C = (32*(fmmVal - fppVal)*TMath::Pi()*R2Val*h2)/3.;
            Double_t term1D = 0;
            Double_t term1E = 0;
            Double_t term1F = 0;
            Double_t term1 = betaVal*term1Coeff*term2Coeff*(term1A+term1B+term1C+term1D+term1E+term1F);
            
            //Double_t para0 = 5.169254e-01;
            //Double_t para1 =-1.004152e-02;
            //Double_t para2 = 3.543577e-04;
            
            //Double_t accp = para0 + para1*m2 + para2*m2*m2;
            Double_t accp = 1.;
            //std::cout << "term1: " << term1 << "... coeff: " << (term1Coeff*term2Coeff) << std::endl;
            return term1*accp;
        }
        case 4:
        {
            // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
            //   const Double_t VEV = 246.;
            Double_t sh1 = sqrt(1-h1*h1);
            Double_t sh2 = sqrt(1-h2*h2);        
            
            // definition of helicity amplitudes
            Double_t chi = (mX*mX-m1*m1-m2*m2)/(2.*m2*m1);
            Double_t eta = (m1*m2)/pow(mX,2);
            
            // condition to avoid NaN PDF
            // data should be variable changed to avoid this though
            if (chi<1) chi = 1;
            
            if (m1 < m2) return 1e-9;
            double nanval = sqrt((1 - TMath::Power(m1 - m2,2)/TMath::Power(mX,2))*(1 - TMath::Power(m1 + m2,2)/TMath::Power(mX,2)));
            if (nanval != nanval) return 1e-9;
            
            Double_t f00Val = (a1Val*a1Val*chi*chi+pow(a2Val,2)*pow(eta,2)*(chi*chi-1.)*(chi*chi-1.)+2.*a1Val*a2Val*chi*(chi*chi-1)*eta*cos(phi1Val-phi2Val));
            Double_t fppVal = (a1Val*a1Val+pow(a3Val,2)*pow(eta,2)*(chi*chi-1)+2.*a1Val*a3Val*chi*sqrt(chi*chi-1)*eta*cos(phi1Val-phi3Val));
            Double_t fmmVal = (a1Val*a1Val+pow(a3Val,2)*pow(eta,2)*(chi*chi-1)+2.*a1Val*a3Val*chi*sqrt(chi*chi-1)*eta*cos(phi1Val-phi3Val));
            Double_t phi00Val = atan2(a1Val*sin(phi1Val)+a2Val*eta*(chi*chi-1)*sin(phi2Val),a1Val*cos(phi1Val)+a2Val*eta*(chi*chi-1)*cos(phi2Val));
            Double_t phippVal = atan2(a1Val*sin(phi1Val)+a3Val*eta*sqrt(chi*chi-1)*sin(phi3Val),a1Val*cos(phi3Val)-a3Val*eta*sqrt(chi*chi-1)*cos(phi3Val));
            Double_t phimmVal = atan2(a1Val*sin(phi1Val)-a3Val*eta*sqrt(chi*chi-1)*sin(phi3Val),a1Val*cos(phi3Val)+a3Val*eta*sqrt(chi*chi-1)*cos(phi3Val));
            
            Double_t betaValSquared = (1.-(pow(m1-m2,2)/pow(mX,2)))*(1.-(pow(m1+m2,2)/pow(mX,2)));
            Double_t betaVal = sqrt(betaValSquared);
            
            Double_t term1Coeff = (pow(m1,3))/( (pow(m1,2)-pow(mZ,2))*(pow(m1,2)-pow(mZ,2))+pow(mZ,2)*pow(gamZ,2) );
            Double_t term2Coeff = (pow(m2,3))/( (pow(m2,2)-pow(mZ,2))*(pow(m2,2)-pow(mZ,2))+pow(mZ,2)*pow(gamZ,2) );
            
            // FOR THE INTEGRATIONS, ONLY THESE LINES SHOULD CHANGE
            // cform --> still have to change "sqrt" and "cos" and "Pi" and "Power" and "R1Val" and "R2"
            Double_t term1A = (-32*f00Val*TMath::Pi()*(-1 + TMath::Power(h1,2)))/3.;
            Double_t term1B = (16*(fmmVal + fppVal)*TMath::Pi()*(1 + TMath::Power(h1,2)))/3.;
            Double_t term1C = (32*(fmmVal - fppVal)*TMath::Pi()*R1Val*h1)/3.;
            Double_t term1D = 0;
            Double_t term1E = 0;
            Double_t term1F = 0;
            Double_t term1 = betaVal*term1Coeff*term2Coeff*(term1A+term1B+term1C+term1D+term1E+term1F);
            
            //Double_t para0 = 5.169254e-01;
            //Double_t para1 =-1.004152e-02;
            //Double_t para2 = 3.543577e-04;
            
            //Double_t accp = para0 + para1*m2 + para2*m2*m2;
            Double_t accp = 1.;
            //std::cout << "term1: " << term1 << "... coeff: " << (term1Coeff*term2Coeff) << std::endl;
            return term1*accp;
        }
        case 5:
        {
            // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
            //   const Double_t VEV = 246.;
            Double_t sh1 = sqrt(1-h1*h1);
            Double_t sh2 = sqrt(1-h2*h2);        
            
            // definition of helicity amplitudes
            Double_t chi = (mX*mX-m1*m1-m2*m2)/(2.*m2*m1);
            Double_t eta = (m1*m2)/pow(mX,2);
            
            // condition to avoid NaN PDF
            // data should be variable changed to avoid this though
            if (chi<1) chi = 1;
            
            if (m1 < m2) return 1e-9;
            double nanval = sqrt((1 - TMath::Power(m1 - m2,2)/TMath::Power(mX,2))*(1 - TMath::Power(m1 + m2,2)/TMath::Power(mX,2)));
            if (nanval != nanval) return 1e-9;
            
            Double_t f00Val = (a1Val*a1Val*chi*chi+pow(a2Val,2)*pow(eta,2)*(chi*chi-1.)*(chi*chi-1.)+2.*a1Val*a2Val*chi*(chi*chi-1)*eta*cos(phi1Val-phi2Val));
            Double_t fppVal = (a1Val*a1Val+pow(a3Val,2)*pow(eta,2)*(chi*chi-1)+2.*a1Val*a3Val*chi*sqrt(chi*chi-1)*eta*cos(phi1Val-phi3Val));
            Double_t fmmVal = (a1Val*a1Val+pow(a3Val,2)*pow(eta,2)*(chi*chi-1)+2.*a1Val*a3Val*chi*sqrt(chi*chi-1)*eta*cos(phi1Val-phi3Val));
            Double_t phi00Val = atan2(a1Val*sin(phi1Val)+a2Val*eta*(chi*chi-1)*sin(phi2Val),a1Val*cos(phi1Val)+a2Val*eta*(chi*chi-1)*cos(phi2Val));
            Double_t phippVal = atan2(a1Val*sin(phi1Val)+a3Val*eta*sqrt(chi*chi-1)*sin(phi3Val),a1Val*cos(phi3Val)-a3Val*eta*sqrt(chi*chi-1)*cos(phi3Val));
            Double_t phimmVal = atan2(a1Val*sin(phi1Val)-a3Val*eta*sqrt(chi*chi-1)*sin(phi3Val),a1Val*cos(phi3Val)+a3Val*eta*sqrt(chi*chi-1)*cos(phi3Val));
            
            Double_t betaValSquared = (1.-(pow(m1-m2,2)/pow(mX,2)))*(1.-(pow(m1+m2,2)/pow(mX,2)));
            Double_t betaVal = sqrt(betaValSquared);
            
            Double_t term1Coeff = (pow(m1,3))/( (pow(m1,2)-pow(mZ,2))*(pow(m1,2)-pow(mZ,2))+pow(mZ,2)*pow(gamZ,2) );
            Double_t term2Coeff = (pow(m2,3))/( (pow(m2,2)-pow(mZ,2))*(pow(m2,2)-pow(mZ,2))+pow(mZ,2)*pow(gamZ,2) );
            
            // FOR THE INTEGRATIONS, ONLY THESE LINES SHOULD CHANGE
            // cform --> still have to change "sqrt" and "cos" and "Pi" and "Power" and "R1" and "R2"
            Double_t term1A = (64*f00Val)/9.;
            Double_t term1B = (64*(fmmVal + fppVal))/9.;
            Double_t term1C = 0;
            Double_t term1D = sqrt(f00Val)*sqrt(fppVal)*TMath::Power(TMath::Pi(),2)*R1Val*R2Val*cos(Phi + phi00Val + phippVal);
            Double_t term1E = sqrt(f00Val)*sqrt(fmmVal)*TMath::Power(TMath::Pi(),2)*R1Val*R2Val*cos(Phi - phi00Val - phimmVal);
            Double_t term1F = (32*sqrt(fmmVal)*sqrt(fppVal)*cos(2*Phi - phimmVal + phippVal))/9.;
            Double_t term1 = betaVal*term1Coeff*term2Coeff*(term1A+term1B+term1C+term1D+term1E+term1F);
            
            //Double_t para0 = 5.169254e-01;
            //Double_t para1 =-1.004152e-02;
            //Double_t para2 = 3.543577e-04;
            
            //Double_t accp = para0 + para1*m2 + para2*m2*m2;
            Double_t accp = 1.;
            //std::cout << "term1: " << term1 << "... coeff: " << (term1Coeff*term2Coeff) << std::endl;
            return term1*accp;
        }
        case 6:
        {
            // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
            //   const Double_t VEV = 246.;
            Double_t sh1 = sqrt(1-h1*h1);
            Double_t sh2 = sqrt(1-h2*h2);        
            
            // definition of helicity amplitudes
            Double_t chi = (mX*mX-m1*m1-m2*m2)/(2.*m2*m1);
            Double_t eta = (m1*m2)/pow(mX,2);
            
            // condition to avoid NaN PDF
            // data should be variable changed to avoid this though
            if (chi<1) chi = 1;
            
            if (m1 < m2) return 1e-9;
            double nanval = sqrt((1 - TMath::Power(m1 - m2,2)/TMath::Power(mX,2))*(1 - TMath::Power(m1 + m2,2)/TMath::Power(mX,2)));
            if (nanval != nanval) return 1e-9;
            
            Double_t f00Val = (a1Val*a1Val*chi*chi+pow(a2Val,2)*pow(eta,2)*(chi*chi-1.)*(chi*chi-1.)+2.*a1Val*a2Val*chi*(chi*chi-1)*eta*cos(phi1Val-phi2Val));
            Double_t fppVal = (a1Val*a1Val+pow(a3Val,2)*pow(eta,2)*(chi*chi-1)+2.*a1Val*a3Val*chi*sqrt(chi*chi-1)*eta*cos(phi1Val-phi3Val));
            Double_t fmmVal = (a1Val*a1Val+pow(a3Val,2)*pow(eta,2)*(chi*chi-1)+2.*a1Val*a3Val*chi*sqrt(chi*chi-1)*eta*cos(phi1Val-phi3Val));
            Double_t phi00Val = atan2(a1Val*sin(phi1Val)+a2Val*eta*(chi*chi-1)*sin(phi2Val),a1Val*cos(phi1Val)+a2Val*eta*(chi*chi-1)*cos(phi2Val));
            Double_t phippVal = atan2(a1Val*sin(phi1Val)+a3Val*eta*sqrt(chi*chi-1)*sin(phi3Val),a1Val*cos(phi3Val)-a3Val*eta*sqrt(chi*chi-1)*cos(phi3Val));
            Double_t phimmVal = atan2(a1Val*sin(phi1Val)-a3Val*eta*sqrt(chi*chi-1)*sin(phi3Val),a1Val*cos(phi3Val)+a3Val*eta*sqrt(chi*chi-1)*cos(phi3Val));
            
            Double_t betaValSquared = (1.-(pow(m1-m2,2)/pow(mX,2)))*(1.-(pow(m1+m2,2)/pow(mX,2)));
            Double_t betaVal = sqrt(betaValSquared);
            
            Double_t term1Coeff = (pow(m1,3))/( (pow(m1,2)-pow(mZ,2))*(pow(m1,2)-pow(mZ,2))+pow(mZ,2)*pow(gamZ,2) );
            Double_t term2Coeff = (pow(m2,3))/( (pow(m2,2)-pow(mZ,2))*(pow(m2,2)-pow(mZ,2))+pow(mZ,2)*pow(gamZ,2) );
            
            // FOR THE INTEGRATIONS, ONLY THESE LINES SHOULD CHANGE
            // cform --> still have to change "sqrt" and "cos" and "Pi" and "Power" and "R1" and "R2"
            Double_t term1A = (128*f00Val*TMath::Pi())/9.;
            Double_t term1B = (128*(fmmVal + fppVal)*TMath::Pi())/9.;
            Double_t term1C = 0;
            Double_t term1D = 0;
            Double_t term1E = 0;
            Double_t term1F = 0;
            Double_t term1 = betaVal*term1Coeff*term2Coeff*(term1A+term1B+term1C+term1D+term1E+term1F);
            
            //Double_t para0 = 5.169254e-01;
            //Double_t para1 =-1.004152e-02;
            //Double_t para2 = 3.543577e-04;
            
            //Double_t accp = para0 + para1*m2 + para2*m2*m2;
            Double_t accp = 1.;
            //std::cout << "term1: " << term1 << "... coeff: " << (term1Coeff*term2Coeff) << std::endl;
            return term1*accp;
        }
    }
    assert(0) ;
    return 0 ;
}
