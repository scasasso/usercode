#define HZZ4lBaseclass_cxx
#include "HZZ4lBaseclass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void HZZ4lBaseclass::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L HZZ4lBaseclass.C
//      Root > HZZ4lBaseclass t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);

      const Int_t NHiggs = ZZMass->size();
      cout << "Number of Higgs candidates in the event = " << NHiggs << endl;

      //Loop over all the H-> ZZ candidates in the event
      for(int nH=0; nH<NHiggs;nH++){

	cout << ZZMass->at(nH) << endl;

      }


   }
}
