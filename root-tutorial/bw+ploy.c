#include "/home/xwl/root-file/bes3plotstyle.c"
using namespace RooFit;
void test40090()
{
  SetStyle(); #设置RooPlot对象的属性，用于绘制拟合曲线或数据分布的图形表示
  SetPrelimStyle(); #用于设置测量结果图形的样式，SetPrelimStyle()函数将图形的填充样式设置为灰色的斜线填充，表示这是一个初步的测量结果，该函数通常在绘制测量结果的图形之前调用。
  gSystem->Load("libRooFit");#动态加载libRoofit库，因为RooRealVar需要使用它
  gROOT->SetStyle("Pub");

  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 800, 600);
  TFile *file = new TFile("/home/xwl/root-file/KKeta_Data_all.root");
  TTree *t = (TTree*) file->Get("Data");
  RooRealVar pipE("pipE", "e(#pip)", 0.1,1.4);
          //定义数据集
  RooDataSet SUMD("SUMD", "SUMD", t, pipE);
          //定义布里渊拟合函数和拟合函数的参数
  RooRealVar mean1("mean1", "mean1",0.1,0.5,1);//中心值，区间
  RooRealVar sigma1("sigma1", "sigma1",0.005,0.5,1);//宽度
  RooBreitWigner BW("BW"," BW fit ",pipE, mean1,sigma1);
          //定义一阶切比雪夫合函数和拟合函数的参数(常用于背景拟合,定义的区间在[-1,1])
  RooRealVar p1("p1", "p1",0.172560,-1,1);
  RooRealVar p2("p2", "p2",0.1,-1,1);
  RooChebychev poly("poly", "poly PDF", pipE, RooArgList(p1,p2));
          //定义信号和背景的权重 
   RooRealVar n_sig("n_sig", "signal number",100,0,10000);
   RooRealVar n_bkg("n_bkg", "bkg  number",1000,0,100000);
          //创建信号和背景的加权和分布
   RooAddPdf sum2("sum2","sum2",RooArgList(BW,poly),RooArgList(n_sig, n_bkg));
          //对数据进行拟合
   sum2.fitTo(SUMD, Range(0.1,1.4),Extended(kTRUE));
           //绘制pipE的分布和拟合结果
   RooPlot* pipEframe = pipE.frame();
   SUMD.plotOn(pipEframe, Binning(80),DataError(RooAbsData::SumW2));
   sum2.plotOn(pipEframe, LineColor(1));

   //double chi2 = xframe->chiSquare(); //计算拟合的chi2
               //将拟合结果中贡献为“BW”的部分以虚线形式绘制在“xframe”上
   sum2.plotOn(pipEframe, Components("BW"), LineStyle(kDashed), LineColor(2));
               //将拟合结果中贡献为“poly”的部分以实线形式绘制在“xframe”上
   sum2.plotOn(pipEframe, Components("poly"),LineWidth(2), LineColor(4));

   c1->SetFillColor(10);
   c1->cd();
   pipEframe->SetXTitle("E(#pi^{+})(GeV/c^{2})");
   pipEframe->SetYTitle("Events");
        //对pipEframe对象的x轴和y轴进行格式化处理
   FormatAxis(pipEframe->GetXaxis());
   FormatAxis(pipEframe->GetYaxis());

   pipEframe->Draw();
//cout<<"chi2="<<chi2<<endl;

////////////////////////

   /*TPaveText *pt = new TPaveText(0.6,0.8, 0.94,0.94,"BRNDC");
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
   pt->Draw();*/


c1->Print("test.pdf");
c1->Print("test.eps");

 cout << "####job done!####" << endl;



}
