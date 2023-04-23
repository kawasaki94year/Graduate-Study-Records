#include "rooFittest.h"
//Roofit classes
#include "RooFit.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooWorkspace.h"
#include "RooConstVar.h"
#include "RooArgusBG.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooWorkspace.h"
#include "RooFitResult.h"
#include "RooChebychev.h"
#include "RooVoigtian.h"
#include "RooCBShape.h"
#include "RooKeysPdf.h"
#include "RooBreitWigner.h"
//Root classes
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TPaveText.h"
#include "TText.h"
#include "TAttAxis.h"
#include "TString.h"
//my classes
//#include "tdrstyle.h"
#include "menus.h"
//#include "commonFuncs.h"
//c++ cloasses
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
using namespace RooFit;
rooFittest::rooFittest(double eP, TString sampleType, TString MCorData) : menus(eP, sampleType, MCorData){} //将 eP、sampleType 和 MCorData 传递给 menus 类的构造函数，以初始化 rooFittest 类的成员变量

void rooFittest::writeWS(TString resName){  //参数TString resName表示这个函数writeWS接受一个名为
					    //resName的字符串类型的参数。在函数内部可以使用
					    //这个参数进行计算、处理等操作。用于写出结果到一个指定的文件，resName是指定的文件名
  gSystem->Load("libRooFit");
  gROOT->SetStyle("Pub");
  double fitRange=0.2;
  TString rootfilename= "/home/xwl/root-file/" + _sampleType + "_" + _MCorData +"_"+"all" + ".root";
  TFile *file=new TFile(rootfilename);
  TTree *tree = (TTree*)file->Get("Data");
  double rangelow;
  double rangeup;
  double BWmeanini;
  double BWsigmaini;
  double BWsigmalow;
  double BWsigmaup;
  const char* xname;
  if( resName == "PE"){
    xname = "ppipE";
    rangelow=0;
    rangeup=14;
    BWmeanini=0.5;
    BWsigmaini=0.0231701;
    BWsigmalow=0.00;
    BWsigmaup=0.5;   
  }
  if( resName == "PPM"){
    xname = "ppipm";
    rangelow=0.13;
    rangeup=0.14;
    BWmeanini=0.5;
    BWsigmaini=0.5;
    BWsigmalow=0.00;
    BWsigmaup=0.8;
 }
  if( resName == "PP"){
    xname = "ppipp";
    rangelow=0;
    rangeup=1.4;
    BWmeanini=3.0969;
    BWsigmaini=0.0231701;
    BWsigmalow=0.00;
    BWsigmaup=0.5;
 } 
  if( resName == "PME"){
    xname = "ppimE";
    rangelow=0;
    rangeup=1.4;
    BWmeanini=1.019461;
    BWsigmaini=0.0231701;
    BWsigmalow=0.00;
    BWsigmaup=0.8;
 }
  RooRealVar x(xname,"m (GeV/c^{2})", rangelow, rangeup);
  RooDataSet mdist("mdist","mdist", tree, x);

  RooRealVar mean("mean", "mean",BWmeanini,rangelow, rangeup);//中心值，区间
  RooRealVar sigma("sigma", "sigma",BWsigmaini,BWsigmalow,BWsigmaup);//宽度
  RooBreitWigner BW("BW"," BW fit ",x, mean,sigma);
  
  RooRealVar p1("p1", "p1",0.172560,-1,1);
  RooChebychev poly("poly", "poly PDF", x, RooArgList(p1));

  RooRealVar n_sig("n_sig", "signal number",100,0,10000);
  RooRealVar n_bkg("n_bkg", "bkg  number",1000,0,100000);
  RooAddPdf sum("sum","sum",RooArgList(BW,poly),RooArgList(n_sig, n_bkg));
  sum.fitTo(mdist , Range(rangelow,rangeup),Extended(kTRUE));
  
  RooPlot* xframe = x.frame();
  mdist.plotOn(xframe, Binning(80),DataError(RooAbsData::SumW2));
  sum.plotOn(xframe, LineColor(1));
 
  double chi2=xframe->chiSquare();
  sum.plotOn(xframe, Components("BW"), LineStyle(kDashed), LineColor(2));
  sum.plotOn(xframe, Components("poly"),LineWidth(2), LineColor(4));
 
  TCanvas *c1=new TCanvas("c1", "c1", 800, 600);
  c1->SetFillColor(10);
  c1->cd();
  xframe->SetXTitle("M(#Kp#Km#pi0#eta)(GeV/c^{2})");
  xframe->SetYTitle("Events");
  xframe->GetXaxis();
  xframe->GetYaxis();
  xframe->GetYaxis()->SetRangeUser(0.00001,350);
  xframe->Draw();
    
  TPaveText *pt = new TPaveText(0.6,0.8, 0.94,0.94,"BRNDC");
  pt->SetBorderSize(1);
  pt->SetFillColor(10);
  pt->SetTextAlign(12);
  pt->SetTextSize(0.03);
  pt->Draw();
  c1->SetLogy(0);
  c1->SaveAs(_resultsdir + _sampleType + "_Databp_" + "3686" + "_" + resName.Data() + "fit" + ".png");
}

