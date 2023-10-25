#include <TString.h>
//my classes
#include "BKGtt.h"
#include "BKGww.h"
#include "BKGzz.h"
#include "sig_mhp800_ATLAS.h"
//Others
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
int main(int argc, char *argv[]){
  if(argc < 2){
    cerr << "Usage:"<< argv[0] << "[sig-A/tt/ww/zz]" << endl;
    return 1;
  }
  Eventselection1 *h1Draw1 = nullptr;
  Eventselection2 *h1Draw2 = nullptr;
  Eventselection3 *h1Draw3 = nullptr;
  Eventselection5 *h1Draw5 = nullptr;
  std::string word = argv[1];
       //eell-bkg
  if(word == "tt"){
          h1Draw1 = new Eventselection1();
          h1Draw1->Draw_BKGtt();
       }
  else if(word == "ww"){
          h1Draw2 = new Eventselection2();
          h1Draw2->Draw_BKGww();
       }
  else if(word == "zz"){
          h1Draw3 = new Eventselection3();
          h1Draw3->Draw_BKGzz();
       }
  else if(word == "sig-A"){
          h1Draw5 = new Eventselection5();
          h1Draw5->Draw_mhp800_A();
       }
  else {
    cerr<<"Invalid argument.Usage:"<<argv[0]<<"[sig-A/tt/ww/zz]"<<endl;
    return 1;
  }
  delete h1Draw1;
  delete h1Draw2;
  delete h1Draw3;
  delete h1Draw5;
  return 0;
}






