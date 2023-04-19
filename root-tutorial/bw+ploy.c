#include "/workfs2/bes/xhy_20200622/workarea-665/bes3plotstyle/bes3plotstyle.c"
using namespace RooFit;
void test40090()
{
  SetStyle(); #设置RooPlot对象的属性，用于绘制拟合曲线或数据分布的图形表示
  SetPrelimStyle();
  gSystem->Load("libRooFit");
        gROOT->SetStyle("Pub");

  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 800, 600);
  TFile *file = new TFile("/besfs5/groups/tauqcd/xhy_20200622/AnaData/f1pipi_Databp_4.0090_Final.root ");
  TTree *t = (TTree*) file->Get("DataReducedmin");
   RooRealVar x("minf1_final", "m(#f1)", 1.1019,1.4619);
   RooDataSet after("after", "after", t, x);

   RooRealVar mean1("mean1", "mean1",1.2819,1.1019, 1.4619);//中心值，区间
   RooRealVar sigma1("sigma1", "sigma1",0.0231701,0.00,0.04);//宽度
   RooBreitWigner BW("BW"," BW fit ",x, mean1,sigma1);

//   RooRealVar mean2("mean2", "mean2",-0.00001,0.00001 );
//   RooRealVar sigma2("sigma2", "sigma2" ,0.0009,0., 0.001);
//RooRealVar sigma2("sigma2", "sigma2", 0., 0.01);   
//   RooGaussian gaus2("gaus2"," gaus fit ",x, mean2,sigma2);
//   x.setBins(10000, "cache");   
//   RooFFTConvPdf BG("BG", "breit-wigner (X) gauss ", x, BW, gaus2);


//  BG.setBufferFraction(0.2);
//  BG.setBufferStrategy(2);

  RooRealVar p1("p1", "p1",0.172560,-1,1);
  RooRealVar p2("p2", "p2",-0.100278,-0.5,0.5);
  RooChebychev poly("poly", "poly PDF", x, RooArgList(p1,p2));

   RooRealVar n_sig("n_sig", "signal number",100,0,10000);
   RooRealVar n_bkg("n_bkg", "bkg  number",1000,0,100000);
   RooAddPdf sum2("sum2","sum2",RooArgList(BW,poly),RooArgList(n_sig, n_bkg));
   sum2.fitTo( after , Range(1.1019,1.4619),Extended(kTRUE));
   RooPlot* xframe = x.frame();
   after.plotOn(xframe, Binning(80),DataError(RooAbsData::SumW2));
   sum2.plotOn(xframe, LineColor(1));

   double chi2 = xframe->chiSquare();
   sum2.plotOn(xframe, Components("BW"), LineStyle(kDashed), LineColor(2));
   sum2.plotOn(xframe, Components("poly"),LineWidth(2), LineColor(4));
//   BG.plotOn(xframe, Components("BW"),LineWidth(2), LineColor(5));
   //sum2.plotOn(xframe, Components("BW"),LineWidth(2), LineColor(3));  

   c1->SetFillColor(10);
   c1->cd();
   xframe->SetXTitle("M(#pi#pi#eta)(GeV/c^{2})");
   xframe->SetYTitle("Events");
   FormatAxis(xframe->GetXaxis());
   FormatAxis(xframe->GetYaxis());

   xframe->Draw();
cout<<"chi2="<<chi2<<endl;

////////////////////////

   TPaveText *pt = new TPaveText(0.6,0.8, 0.94,0.94,"BRNDC");
   pt->SetBorderSize(1);
   pt->SetFillColor(10);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);

   TString Par1V = Form("%5.1f", n_sig.getVal() );
   TString Par1E = Form("%3.1f", n_sig.getError() );
   TString Par1  = "Nsignal = " + Par1V + " #pm " + Par1E;

   TString Par2V = Form("%5.1f", n_bkg.getVal() );
   TString Par2E = Form("%3.1f", n_bkg.getError() );
   TString Par2  = "Nbkg = " + Par2V + " #pm " + Par2E;

   TString Par3V = Form("%5.5f", sigma1.getVal() );
   TString Par3E = Form("%3.5f", sigma1.getError() );
   TString Par3  = "bwsigma = " + Par3V + " #pm " + Par3E;
  TString Par4V = Form("%5.5f", mean1.getVal() );
   TString Par4E = Form("%3.5f", mean1.getError() );
   TString Par4  = "bwmean = " + Par4V + " #pm " + Par4E;

   TString Par5V = Form("%5.5f", chi2 );
//   TString Par4E = Form("%3.5f", mean1.getError() );
   TString Par5  = "chi2 = " + Par5V;

   TText *text=new TText();
   text = pt->AddText("#sqrt{s} = 4.0090 GeV");
   text = pt->AddText(Par1);
   text = pt->AddText(Par2);
   text = pt->AddText(Par3);
   text = pt->AddText(Par4);
   text = pt->AddText(Par5);
   pt->Draw();

/*
c1->Print("data_f1_21250.pdf");
c1->Print("data_f1_21250.eps");

 cout << "####job done!####" << endl;
*/
