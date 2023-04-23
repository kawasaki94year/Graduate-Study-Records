////////
//from now on(2016-10-26), the using illustrations will be written only in main function file
///////

////////// illustraction written on 2016-10-26
// for the analysis frame work, the work road is: event selection (eventSelection.C, eventSelection.h)
// -> write the workspace using roofit (rooFitWSwrite.C, rooFitWSwrite.h) from the reduced root, which is produdeced by event slection
// -> after that, the rooFitWSread.C and rooFitWSread.h are used to read the fit results and save figures, numbers in results directory
//////////
//Root classes
#include <TString.h>
//my classes
#include "menus.h"
//#include "eventSelection.h"
#include "eventSelection6.h"
#include "rooFittest.h"
//Others
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main( int argc, char* argv[] )//int argc, char* argv[] 是命令行参数，
				  //表示运行程序时可以通过命令行传入的参数。
				  //其中，argc 表示命令行参数的个数，argv 是一个字符串指针数组，
				  //每个元素都指向一个命令行参数的字符串。
{
  std::string word = argv[1];//其中argv[0]是程序的名称，argv[1]是第一个传入的参数，以此类推
			     //这段代码的作用是将命令行传入的第一个参数转换为
			     //字符串类型并保存在变量word中。
  int samplestart=0, sampleend=1;
  TString sampleTypearray[2]={"KKeta","Data"};
  TString DataOrMC="";
  TString resNameArray[4] = {"PE", "PPM", "PP", "PME"};
  if( word == "rooFittest" ){
      for(int isample=samplestart; isample<sampleend; isample++){
       if(sampleTypearray[isample] == "KKeta") DataOrMC="Data" ;
       else DataOrMC = "MC";      
        for (int i = 0; i < 4; i++){
         TString resName = resNameArray[i];
         cout<<"i = "<<i<<endl;
         cout<<"resName1 = "<<resNameArray[0]<<endl;
         cout<<"resName2 = "<<resNameArray[1]<<endl;
         cout<<"resName3 = "<<resNameArray[2]<<endl;
         cout<<"resName4 = "<<resNameArray[3]<<endl;
       
        rooFittest *ws = new rooFittest(0, sampleTypearray[isample], DataOrMC);
        ws->writeWS(resName);
        delete ws;
        }
      }

  }

return 0;
}





