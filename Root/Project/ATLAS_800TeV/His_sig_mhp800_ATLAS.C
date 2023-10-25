#include "sig_mhp800_ATLAS.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TProfile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TClass.h"
#include "TStyle.h"
#include "TLorentzVector.h"
#include "TLegend.h"
#include <iostream>
#include <math.h>
#include "TObject.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TLatex.h"
#include "lester_mt2_bisect.h"

using namespace std;
typedef std::vector<int> Vint;

Eventselection5::Eventselection5(){
}

void Eventselection5::Draw_mhp800_A(){
  TChain *sig_tree = new TChain("Delphes");//tree name
  sig_tree->Add("/home/xwl/Analysis/Root/pp/signal/signal_100TeV_800_ATLAS.root");
	   //muon
  sig_tree->SetBranchAddress("Muon_size",&Muon_size, &b_Muon_size);
  sig_tree->SetBranchAddress("Muon.Eta", Muon_Eta, &b_Muon_Eta);
  sig_tree->SetBranchAddress("Muon.PT", Muon_PT, &b_Muon_PT);
  sig_tree->SetBranchAddress("Muon.Charge", Muon_Charge, &b_Muon_Charge);
  sig_tree->SetBranchAddress("Muon.Phi", Muon_Phi, &b_Muon_Phi);
            //MissingET
  sig_tree->SetBranchAddress("MissingET.MET", MissingET_MET, &b_MissingET_MET);
  sig_tree->SetBranchAddress("MissingET_size",&MissingET_size, &b_MissingET_size);
	   //Electron
  sig_tree->SetBranchAddress("Electron_size",&Electron_size, &b_Electron_size);
  sig_tree->SetBranchAddress("Electron.Charge", Electron_Charge, &b_Electron_Charge);
  sig_tree->SetBranchAddress("Electron.Eta", Electron_Eta, &b_Electron_Eta);
  sig_tree->SetBranchAddress("Electron.PT", Electron_PT, &b_Electron_PT);
  sig_tree->SetBranchAddress("Electron.Phi", Electron_Phi, &b_Electron_Phi);
	   //Jet
  sig_tree->SetBranchAddress("Jet_size",&Jet_size, &b_Jet_size);
  sig_tree->SetBranchAddress("Jet.PT", Jet_PT, &b_Jet_PT);
  sig_tree->SetBranchAddress("Jet.Eta", Jet_Eta, &b_Jet_Eta);
           //output root file
  //TFile *f = new TFile("/home/xwl/Analysis/pp-100TeV/ATLAS_800TeV/Root/sig_100TeV_800_ATLAS_1.root","recreate");
  TFile *f = new TFile("/home/xwl/Analysis/pp-100TeV/ATLAS_800TeV/Root/sig_100TeV_800_ATLAS_cut.root","recreate");
           //creat histogram
  TH1 *h1H_llPT = new TH1F("h1H_llPT","", 100, 0, 600); 
  TH1 *h1H_eePT = new TH1F("h1H_eePT","", 100, 0, 300); 
  TH1 *h1H_mumuPT = new TH1F("h1H_mumuPT","", 100, 0, 300); 
  TH1 *h1H_emuPT = new TH1F("h1H_emuPT","", 100, 0, 300); 

  TH1 *h1H_lleta = new TH1F("h1H_lleta","", 100, -3, 3); 
  TH1 *h1H_eeeta = new TH1F("h1H_eeeta","", 100, -3, 3); 
  TH1 *h1H_mumueta = new TH1F("h1H_mumueta","", 100, -3,3); 
  TH1 *h1H_emueta = new TH1F("h1H_emueta","", 100, -3,3); 

  TH1 *h1H_JetPT = new TH1F("h1H_JetPT","", 100, 0, 100); 
  TH1 *h1H_JetSize = new TH1F("h1H_JetSize","", 100, 0, 10);

  TH1 *h1H_llM = new TH1F("h1H_llM","", 100, 0, 1000); 
  TH1 *h1H_llE = new TH1F("h1H_llE","", 100, 0,2000);
  TH1 *h1H_llP = new TH1F("h1H_llP","", 100, 0,1500);
  TH1 *h1H_llp = new TH1F("h1H_llp","", 100, 0,1500);

  TH1 *h1H_alpha = new TH1F("h1H_alpha","", 100, 0,3.5);
  TH1 *h1H_cosalpha = new TH1F("h1H_cosalpha","", 100, -1,1);
  TH1 *h1H_delta = new TH1F("h1H_delta","", 100, 0,1);
  TH1 *h1H_Theta = new TH1F("h1H_Theta","", 100, 0,3.5);

  TH1F *h1H_MT2 = new TH1F("h1H_MT2","",50,0,340);
  TH1F *h1H_MissingET = new TH1F("h1H_MissingET","",50,0,700);

            //draw histogram
  double num_cut = 0;
  double eff_cut = 0;
  double num_cut1 = 0;
  double eff_cut1 = 0;
  double num_cut2 = 0;
  double eff_cut2 = 0;
  double num_cut3 = 0;
  double eff_cut3 = 0;
  Long64_t neventssig = sig_tree->GetEntries();
  cout<<"neventssig = "<<neventssig<<endl;
  for (Long64_t i = 0; i < neventssig; i++){
    sig_tree->GetEntry(i);
         //muon
    int num_mu = 0;
    for(int jm = 0; jm < Muon_size; jm++){
      num_mu = num_mu + 1;
    }
          //Eelc
    int num_e = 0;
    for(int je = 0; je < Electron_size; je++){
      num_e = num_e + 1;
    }
    int num_lep = num_e + num_mu;
    //cout<<"num_lep = "<<num_lep<<endl;

    Double_t l_PT[2];      
    Double_t l_Eta[2];      
    Double_t l_Phi[2];      
         //Jet
    double l_Jet = 0;
    for (int jt = 0; jt < Jet_size;jt++){
      l_Jet = Jet_PT[jt];
    }
          //MissingET
    double l_MET = 0;
    for (int js = 0; js < MissingET_size;js++){
      l_MET = MissingET_MET[js];
    }

    if(num_lep == 2){
      int num_ee = 0, num_mumu = 0, num_emu = 0;
      if(num_e == 2 && Electron_Charge[0] != Electron_Charge[1]){
        num_ee = num_ee + 1;
      }
      if(num_mu == 2 && Muon_Charge[0] != Muon_Charge[1]){
        num_mumu = num_mumu + 1;
      }
      if(num_mu == 1 && num_e == 1 && Muon_Charge[0] != Electron_Charge[0]){
        num_emu = num_emu + 1;
      }
      int num_llep = num_ee + num_mumu + num_emu;

      if( num_llep == 1 ){
	double MTee=0;
	if(num_e == 2 && Jet_size == 0){
          if(Electron_PT[0] > 100 && Electron_PT[1] > 100 && l_MET > 100){
		  //four momentum
	    l_PT[0] = Electron_PT[0];
	    l_PT[1] = Electron_PT[1];
	    l_Eta[0] = Electron_Eta[0];
	    l_Eta[1] = Electron_Eta[1];
	    l_Phi[0] = Electron_Phi[0];
	    l_Phi[1] = Electron_Phi[1];

	    TLorentzVector l1_p4,l2_p4;
	    l1_p4.SetPtEtaPhiM(l_PT[0],l_Eta[0],l_Phi[0],0);
	    l2_p4.SetPtEtaPhiM(l_PT[1],l_Eta[1],l_Phi[1],0);

	    Double_t ll_M = (l1_p4 + l2_p4).M();
	    Double_t ll_E = (l1_p4 + l2_p4).E();
            Double_t ll_P = (l1_p4 + l2_p4).P();
            Double_t alpha = l1_p4.Angle(l2_p4.Vect());
            Double_t cosa = cos(alpha);
            Double_t E1 = l1_p4.E();
            Double_t E2 = l2_p4.E();
            Double_t delta = fabs(E1 - E2)/fabs(E1 + E2);
            Double_t stheta = (l1_p4 + l2_p4).Theta();

	    Double_t l1px = l1_p4.Px();
            Double_t l1py = l1_p4.Py();
            Double_t l1pz = l1_p4.Pz();

            Double_t l2px = l2_p4.Px();
            Double_t l2py = l2_p4.Py();
            Double_t l2pz = l2_p4.Pz();

            Double_t lp1 = sqrt(l1px*l1px + l1py*l1py + l1pz*l1pz);
            Double_t lp2 = sqrt(l2px*l2px + l2py*l2py + l2pz*l2pz);

            Double_t llp = lp1 + lp2;

	              //MT2
	    double mVisA = 0; // mass of visible object on side A.  Must be >=0.
            double pxA = Electron_PT[0] * cos(Electron_Phi[0]); // x momentum of visible object on side A.
            double pyA = Electron_PT[0] * sin(Electron_Phi[0]); // y momentum of visible object on side A.

            double mVisB = 0; // mass of visible object on side B.  Must be >=0.
            double pxB = Electron_PT[1] * cos(Electron_Phi[1]); // x momentum of visible object on side B.
            double pyB = Electron_PT[1] * sin(Electron_Phi[1]); // y momentum of visible object on side B.

            double pxMiss = MissingET_MET[0] * cos(MissingET_Phi[0]); // x component of missing transverse momentum.
            double pyMiss = MissingET_MET[0] * sin(MissingET_Phi[0]); // y component of missing transverse momentum.

            double chiA = 0; // hypothesised mass of invisible on side A.  Must be >=0.
            double chiB = 0; // hypothesised mass of invisible on side B.  Must be >=0.

            double desiredPrecisionOnMt2 = 0; // Must be >=0.  If 0 alg aims for machine precision.  if >0, MT2 computed to supplied absolute precision.

            asymm_mt2_lester_bisect::disableCopyrightMessage();
            MTee =  asymm_mt2_lester_bisect::get_mT2(
                mVisA, pxA, pyA,
                mVisB, pxB, pyB,
                pxMiss, pyMiss,
                chiA, chiB,
                desiredPrecisionOnMt2);

            if( ll_M > 130 && MTee > 110){

              h1H_llPT->Fill(l_PT[0]);
              h1H_llPT->Fill(l_PT[1]);

              h1H_lleta->Fill(l_Eta[0]);
              h1H_lleta->Fill(l_Eta[1]);

              h1H_JetPT->Fill(l_Jet);
              h1H_JetSize->Fill(Jet_size);

              h1H_llM->Fill(ll_M);
	      h1H_llE->Fill(ll_E);
              h1H_llP->Fill(ll_P);
              h1H_alpha->Fill(alpha);
              h1H_cosalpha->Fill(cosa);
              h1H_delta->Fill(delta);
              h1H_Theta->Fill(stheta);
	      h1H_llp->Fill(llp);

	      h1H_MissingET->Fill(l_MET);
	      h1H_MT2->Fill(MTee);

	      num_cut1 = num_cut1 + 1;
              eff_cut1 = num_cut1 / neventssig;
              cout<<"neventssig1 = "<<neventssig<<endl;
	    }
	  }
	}

	double MTmumu=0;
	if(num_mu == 2 && Jet_size == 0){
	  if(Muon_PT[0] > 100 && Muon_PT[1] > 100 && l_MET > 100){
		   //four momentum
	    l_PT[0] = Muon_PT[0];
	    l_PT[1] = Muon_PT[1];
	    l_Eta[0] = Muon_Eta[0];
	    l_Eta[1] = Muon_Eta[1];
	    l_Phi[0] = Muon_Phi[0];
	    l_Phi[1] = Muon_Phi[1];

	    TLorentzVector l1_p4,l2_p4;
	    l1_p4.SetPtEtaPhiM(l_PT[0],l_Eta[0],l_Phi[0],0);
	    l2_p4.SetPtEtaPhiM(l_PT[1],l_Eta[1],l_Phi[1],0);

	    Double_t ll_M = (l1_p4 + l2_p4).M();
	    Double_t ll_E = (l1_p4 + l2_p4).E();
            Double_t ll_P = (l1_p4 + l2_p4).P();
            Double_t alpha = l1_p4.Angle(l2_p4.Vect());
            Double_t cosa = cos(alpha);
            Double_t E1 = l1_p4.E();
            Double_t E2 = l2_p4.E();
            Double_t delta = fabs(E1 - E2)/fabs(E1 + E2);
            Double_t stheta = (l1_p4 + l2_p4).Theta();

	    Double_t l1px = l1_p4.Px();
            Double_t l1py = l1_p4.Py();
            Double_t l1pz = l1_p4.Pz();

            Double_t l2px = l2_p4.Px();
            Double_t l2py = l2_p4.Py();
            Double_t l2pz = l2_p4.Pz();

            Double_t lp1 = sqrt(l1px*l1px + l1py*l1py + l1pz*l1pz);
            Double_t lp2 = sqrt(l2px*l2px + l2py*l2py + l2pz*l2pz);

            Double_t llp = lp1 + lp2;

	                //MT2
	    double mVisA = 0; // mass of visible object on side A.  Must be >=0.
            double pxA = Muon_PT[0] * cos(Muon_Phi[0]); // x momentum of visible object on side A.
            double pyA = Muon_PT[0] * sin(Muon_Phi[0]); // y momentum of visible object on side A.

            double mVisB = 0; // mass of visible object on side B.  Must be >=0.
            double pxB = Muon_PT[1] * cos(Muon_Phi[1]); // x momentum of visible object on side B.
            double pyB = Muon_PT[1] * sin(Muon_Phi[1]); // y momentum of visible object on side B.

            double pxMiss = MissingET_MET[0] * cos(MissingET_Phi[0]); // x component of missing transverse momentum.
            double pyMiss = MissingET_MET[0] * sin(MissingET_Phi[0]); // y component of missing transverse momentum.

            double chiA = 0; // hypothesised mass of invisible on side A.  Must be >=0.
            double chiB = 0; // hypothesised mass of invisible on side B.  Must be >=0.

            double desiredPrecisionOnMt2 = 0; // Must be >=0.  If 0 alg aims for machine precision.  if >0, MT2 computed to supplied absolute precision.

            asymm_mt2_lester_bisect::disableCopyrightMessage();
            MTmumu =  asymm_mt2_lester_bisect::get_mT2(
                mVisA, pxA, pyA,
                mVisB, pxB, pyB,
                pxMiss, pyMiss,
                chiA, chiB,
                desiredPrecisionOnMt2);

	    if( ll_M > 130 && MTmumu > 110){

              h1H_llPT->Fill(l_PT[0]);
	      h1H_llPT->Fill(l_PT[1]);

              h1H_lleta->Fill(l_Eta[0]);
              h1H_lleta->Fill(l_Eta[1]);

              h1H_JetPT->Fill(l_Jet);
              h1H_JetSize->Fill(Jet_size);

              h1H_llM->Fill(ll_M);
	      h1H_llE->Fill(ll_E);
              h1H_llP->Fill(ll_P);
              h1H_alpha->Fill(alpha);
              h1H_cosalpha->Fill(cosa);
              h1H_delta->Fill(delta);
              h1H_Theta->Fill(stheta);
              h1H_llp->Fill(llp);

	      h1H_MissingET->Fill(l_MET);
	      h1H_MT2->Fill(MTmumu);

	      num_cut2 = num_cut2 + 1;
              eff_cut2 = num_cut2 / neventssig;
              cout<<"neventssig2 = "<<neventssig<<endl;
	    }
	  }
	}

	double MTemu=0;
	if(num_e == 1 && num_mu == 1 && Jet_size == 0){
          if(Electron_PT[0] > 100 &&  Muon_PT[0] > 100 && l_MET > 100){
		  //four momentum
	    l_PT[0] = Electron_PT[0];
	    l_PT[1] = Muon_PT[0];
	    l_Eta[0] = Electron_Eta[0];
	    l_Eta[1] = Muon_Eta[0];
	    l_Phi[0] = Electron_Phi[0];
	    l_Phi[1] = Muon_Phi[0];

	    TLorentzVector l1_p4,l2_p4;
	    l1_p4.SetPtEtaPhiM(l_PT[0],l_Eta[0],l_Phi[0],0);
	    l2_p4.SetPtEtaPhiM(l_PT[1],l_Eta[1],l_Phi[1],0);

	    Double_t ll_M = (l1_p4 + l2_p4).M();
	    Double_t ll_E = (l1_p4 + l2_p4).E();
            Double_t ll_P = (l1_p4 + l2_p4).P();
            Double_t alpha = l1_p4.Angle(l2_p4.Vect());
            Double_t cosa = cos(alpha);
            Double_t E1 = l1_p4.E();
            Double_t E2 = l2_p4.E();
            Double_t delta = fabs(E1 - E2)/fabs(E1 + E2);
            Double_t stheta = (l1_p4 + l2_p4).Theta();

	    Double_t l1px = l1_p4.Px();
            Double_t l1py = l1_p4.Py();
            Double_t l1pz = l1_p4.Pz();

            Double_t l2px = l2_p4.Px();
            Double_t l2py = l2_p4.Py();
            Double_t l2pz = l2_p4.Pz();

            Double_t lp1 = sqrt(l1px*l1px + l1py*l1py + l1pz*l1pz);
            Double_t lp2 = sqrt(l2px*l2px + l2py*l2py + l2pz*l2pz);

            Double_t llp = lp1 + lp2;

	            //MT2
            double mVisA = 0; // mass of visible object on side A.  Must be >=0.
            double pxA = Electron_PT[0] * cos(Electron_Phi[0]); // x momentum of visible object on side A.
            double pyA = Electron_PT[0] * sin(Electron_Phi[0]); // y momentum of visible object on side A.

            double mVisB = 0; // mass of visible object on side B.  Must be >=0.
            double pxB = Muon_PT[0] * cos(Muon_Phi[0]); // x momentum of visible object on side B.
            double pyB = Muon_PT[0] * sin(Muon_Phi[0]); // y momentum of visible object on side B.

            double pxMiss = MissingET_MET[0] * cos(MissingET_Phi[0]); // x component of missing transverse momentum.
            double pyMiss = MissingET_MET[0] * sin(MissingET_Phi[0]); // y component of missing transverse momentum.

            double chiA = 0; // hypothesised mass of invisible on side A.  Must be >=0.
            double chiB = 0; // hypothesised mass of invisible on side B.  Must be >=0.

            double desiredPrecisionOnMt2 = 0; // Must be >=0.  If 0 alg aims for machine precision.  if >0, MT2 computed to supplied absolute precision.
            asymm_mt2_lester_bisect::disableCopyrightMessage();
            MTemu =  asymm_mt2_lester_bisect::get_mT2(
                mVisA, pxA, pyA,
                mVisB, pxB, pyB,
                pxMiss, pyMiss,
                chiA, chiB,
                desiredPrecisionOnMt2);

            if( ll_M > 130 && MTemu > 110){

              h1H_llPT->Fill(l_PT[0]);
              h1H_llPT->Fill(l_PT[1]);

              h1H_lleta->Fill(l_Eta[0]);
              h1H_lleta->Fill(l_Eta[1]);

              h1H_JetPT->Fill(l_Jet);
              h1H_JetSize->Fill(Jet_size);

              h1H_llM->Fill(ll_M);
	      h1H_llE->Fill(ll_E);
              h1H_llP->Fill(ll_P);
              h1H_alpha->Fill(alpha);
              h1H_cosalpha->Fill(cosa);
              h1H_delta->Fill(delta);
              h1H_Theta->Fill(stheta);
	      h1H_llp->Fill(llp);

	      h1H_MissingET->Fill(l_MET);
	      h1H_MT2->Fill(MTemu);

	      num_cut3 = num_cut3 + 1;
              eff_cut3 = num_cut3 / neventssig;
              cout<<"neventssig3 = "<<neventssig<<endl;
	    }
	  }
	}
	num_cut = num_cut1 + num_cut2 + num_cut3;
        eff_cut = eff_cut1 + eff_cut2 + eff_cut3;
        cout<<"sig800_ATLAS:num_cut = "<<num_cut<<";"<<"eff_cut = " << eff_cut << endl;
        
        cout<<"sig800_ATLAS:num_cut1 for ee="<<num_cut1<<endl;
	cout<<"sig800_ATLAS:eff_cut1 for ee="<<eff_cut1<<endl;
	
	cout<<"sig800_ATLAS:num_cut2 for mu mu="<<num_cut2<<endl;
	cout<<"sig800_ATLAS:eff_cut2 for mu mu="<<eff_cut2<<endl;
	
	cout<<"sig800_ATLAS:num_cut3 for emu="<<num_cut3<<endl;
	cout<<"sig800_ATLAS:eff_cut3 for emu="<<eff_cut3<<endl;
      }
    }
  }
  f->Write();
  f->Close();
}


