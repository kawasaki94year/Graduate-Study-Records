#Divide和cd函数用来分割画布，Divide用于将当前画布分割成指定的行数和列数:
#Divide(2,1)表示将当前画布分割成两个区域，一行一列；
#cd函数用于将绘图操作切换到指定的区域，cd函数的参数可以是数字或者字符串，如果是数字表示在当前画布中的第几个区域中进行绘图，如果是字符串表示在当前画布的子区域列表中
#查找与该字符串匹配的区域。
#例：

#include <iostream>
#include "TCanvas.h"
#include "TH1F.h"

int main()
  //创建一个名为"mycanvas"的新画布，并将其设为当前画布
  TCanvas* canvas = new TCanvas("mycanvas","My Canvas",800,600);
  canvas->cd();
  //将画布分割成两行一列，第一个子区域为当前区域
  canvas->Divide(2,1);
  canvas->cd(1);
  // 在第一个子区域中创建一个名为 "hist1" 的 TH1F 对象，并设置x和y的范围以及名称
    TH1F* hist1 = new TH1F("hist1", "Histogram 1", 100, -5.0, 5.0);
    hist1->FillRandom("gaus", 1000);
    hist1->GetXaxis()->SetTitle("X Axis Title");
    hist1->GetYaxis()->SetTitle("Y Axis Title");
    hist1->SetMinimum(0.0);
    hist1->SetMaximum(200.0);
    hist1->Draw();

    // 将绘图操作切换到第二个子区域中
    canvas->cd(2);

    // 在第二个子区域中创建一个名为 "hist2" 的 TH1F 对象，并绘制它
    TH1F* hist2 = new TH1F("hist2", "Histogram 2", 100, -5.0, 5.0);
    hist2->FillRandom("gaus", 1000);
    hist2->GetXaxis()->SetTitle("X Axis Title");
    hist2->GetYaxis()->SetTitle("Y Axis Title");
    hist2->SetMinimum(0.0);
    hist2->SetMaximum(150.0);
    hist2->Draw();

    // 将绘图操作切换回第一个子区域中
    canvas->cd(1);

    // 画出第一个子区域的图形
    hist1->Draw();

    // 将绘图操作切换回整个画布
    canvas->cd();

    // 保存画布为 PNG 文件
    canvas->SaveAs("mycanvas.png");

    // 等待用户关闭画布窗口
    canvas->Update();
    canvas->WaitPrimitive();

    return 0;
}
