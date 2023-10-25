#include <iostream>
#include <fstream>
#include <TGraph.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TLine.h>
#include <TStyle.h>
#include <TFrame.h>
#include <TAxis.h>

void FitDataNH() {
    // 打开文本文件
    std::ifstream dataFile("/home/xwl/xuwanlun/Cross_section/scan_mhp_NH.txt");
    if (!dataFile.is_open()) {
        std::cerr << "Failed to open data file." << std::endl;
        return;
    }

    // 创建变量来存储数据
    std::vector<double> MData, bestfitData, minData, maxData;
    double x, y1, y2, y3;
    
    while (dataFile >> x >> y1 >> y2 >> y3) {
        MData.push_back(x);
        bestfitData.push_back(y1);
        maxData.push_back(y2);
        minData.push_back(y3);
    }

    // 创建TGraph对象
    TGraph *graph1 = new TGraph(MData.size(), &MData[0], &minData[0]);
    TGraph *graph2 = new TGraph(MData.size(), &MData[0], &bestfitData[0]);
    TGraph *graph3 = new TGraph(MData.size(), &MData[0], &maxData[0]);
    
    // 创建画布和绘图
    TCanvas *c1 = new TCanvas("c1", "Inverted hierarchy", 800, 600);
    //c1->SetLogy();
    //graph1->Draw("AL");  // 绘制图形
    //graph2->Draw("L same");  // 绘制图形
    //graph3->Draw("L same");  // 绘制图形

    //graph1->SetMarkerStyle(20);
    //graph2->SetMarkerStyle(20);
    //graph3->SetMarkerStyle(20);

    //graph1->SetLineColor(kGreen);
    //graph2->SetLineColor(kRed);
    //graph3->SetLineColor(kBlue);

    // 使用TF1函数进行拟合，分别拟合每组数据
    TF1 *fitFunc1 = new TF1("fitFunc1", "pol3", MData.front(), MData.back());
    TF1 *fitFunc2 = new TF1("fitFunc2", "pol3", MData.front(), MData.back());
    TF1 *fitFunc3 = new TF1("fitFunc3", "pol3", MData.front(), MData.back());

    graph1->Fit(fitFunc1, "R");
    graph2->Fit(fitFunc2, "R");
    graph3->Fit(fitFunc3, "R");

    // 在同一画布上绘制拟合曲线
    fitFunc1->SetLineColor(kGreen);
    fitFunc1->SetLineWidth(3);
    fitFunc1->SetTitle("Normal hierarchy");
    fitFunc1->GetXaxis()->SetTitle("M_{H^{#pm}} [GeV]");
    fitFunc1->GetXaxis()->SetRangeUser(500,1100);
    TAxis *xaxis = fitFunc1->GetXaxis();
    xaxis->CenterTitle();
    fitFunc1->GetYaxis()->SetTitle("luminosity of 5#sigma [fb^{-1}]");
    fitFunc1->GetYaxis()->SetRangeUser(500,5000);
    TAxis *yaxis = fitFunc1->GetYaxis();
    yaxis->CenterTitle();
    
    fitFunc2->SetLineColor(kRed);
    fitFunc2->SetLineWidth(3);
    
    fitFunc3->SetLineColor(kBlue);
    fitFunc3->SetLineWidth(3);
    
    fitFunc1->Draw();
    fitFunc2->Draw("L same");
    fitFunc3->Draw("L same");
    
    // 3000 fb
    TLine *line = new TLine(MData.front(),3000,MData.back(),3000);
    line->SetLineColor(4);
    line->SetLineStyle(2);
    line->SetLineWidth(3);
    line->Draw();
    
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(fitFunc1, "min");
    legend->AddEntry(fitFunc2, "bestfit");
    legend->AddEntry(fitFunc3, "max");
    legend->AddEntry(line, "3000 fb^{-1} of collected data");
    legend->SetTextSize(0.03);
    legend->SetX1(0.1);
    legend->SetY1(0.78);
    legend->SetX2(0.45);
    legend->SetY2(0.9);
    legend->Draw();
   
    c1->SaveAs("/home/xwl/xuwanlun/Cross_section/scan_NH.eps");
}
