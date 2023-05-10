#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "TLatex.h"
#include <TH1.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TCanvas.h>

void draw_histograms(){
  gStyle->SetOptStat(0); //Remove the Entries and Means boxes from histogram
  
  TFile *hh = new TFile("/home/xwl/His_signal_ana/cut-3-800/Root/sig2pt.root");
  TFile *ww = new TFile("/home/xwl/His_Bkg_ana/3-tev/BkG_ww/Root/bw2pt.root");
  TFile *zz = new TFile("/home/xwl/His_Bkg_ana/3-tev/BkG_zz/Root/bz2pt.root");
  TFile *tt = new TFile("/home/xwl/His_Bkg_ana/3-tev/BkG_tt/Root/bt2pt.root");

  // create a canvas with multiple subplots
  TCanvas* c1[10];
  //TCanvas* c1 = new TCanvas("c1","c1",0,0,800,600);
  //c1->Divide(5,2);

  // loop over the variables and draw histograms in each subplot
  std::vector<std::string> variableNames = {"h1H_alpha", "h1H_llPT", "h1H_llM", "h1H_JetPT", "h1H_lleta", "h1H_llP", "h1H_llE","plot","plot1"};
  std::vector<std::string> titleNames = {"alpha", "llPT", "M", "JetPT", "eta", "P", "E","MT2","MET"};
  std::vector<double> Ranges = {0.7, 0.1, 0.15, 0.7, 0.1, 0.2, 0.2, 0.6, 0.6};
  
  for (int i=0; i<variableNames.size(); i++) {
    c1[i] = new TCanvas("c1","c1",0,0,800,600);
    //c1->cd(i+1);
    // signal
    TH1F *C0 = (TH1F*)hh->Get(variableNames[i].c_str());
    C0->Scale(1/C0->Integral());
    C0->SetLineColor(4);
    C0->SetLineStyle(1);
    C0->SetLineWidth(2);
    C0->GetXaxis()->SetTitle(variableNames[i].c_str());
    C0->GetYaxis()->SetTitle("Number of events(Scaled to one)");
    C0->GetXaxis()->SetTitle(titleNames[i].c_str());
    C0->GetYaxis()->SetRangeUser(0,Ranges[i]);
    C0->Draw("hist");

    // background 1
    TH1F *C1 = (TH1F*)ww->Get(variableNames[i].c_str());
    C1->Scale(1/C1->Integral());
    C1->SetLineColor(3);
    C1->SetLineStyle(2);
    C1->SetLineWidth(2);
    C1->Draw("hist same");

    // background 2
    TH1F *C2 = (TH1F*)zz->Get(variableNames[i].c_str());
    C2->Scale(1/C2->Integral());
    C2->SetLineColor(2);
    C2->SetLineStyle(2);
    C2->SetLineWidth(2);
    C2->Draw("hist same");

    // background 3
    TH1F *C3 = (TH1F*)tt->Get(variableNames[i].c_str());
    C3->Scale(1/C3->Integral());
    C3->SetLineColor(1);
    C3->SetLineStyle(2);
    C3->SetLineWidth(2);
    C3->Draw("hist same");
    
    TLegend* legend = new TLegend(.73,.5,.97,.95);
    legend->AddEntry(C0,"h+ h-(sig)");
    legend->AddEntry(C1,"w+ w-(bkg)");
    legend->AddEntry(C2,"z z(bkg)");
    legend->AddEntry(C3,"t t(bkg)");
 
    legend->SetFillColor(0);
    legend->SetTextSize(0.05);
    legend->SetTextFont(22);
    legend->SetY1(TMath::Max(0.15,0.97-0.10*legend->GetListOfPrimitives()->GetSize()));
    legend->Draw();
    
    c1[i]->SaveAs(("/home/xwl/signal_Bkg/MHP3-800/cut/cut-PT/" + titleNames[i] + ".png").c_str());
  }
}
