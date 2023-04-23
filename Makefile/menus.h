#ifndef MENUS_H
#define MENUS_H
//Root classes
#include "TString.h"
//Others
#include <stdio.h>
#include <stdlib.h>

class menus{
 public:
  menus(){};
  menus( double eP,TString smapleType, TString MCorData);//带有三个参数的构造函数
  inline virtual ~menus(){ };
  int _outputlevel;
  int _lineWidth;
  TString _MCorData;
  TString _sampleType;
  int _flatMCround;
  bool _useISRUncert;
  TString _studydir;
  TString _infiledir;
  TString _resultsdir;
  TString _scaleFormat;
  TString _savedFileName;
  Double_t _eP;
  TString _ePAtfilename;
  TString _ePAtfilenameFinal;

  Double_t _PI;
  Double_t _etam;
  Double_t _etamWindow;
  Double_t _f1m;
  Double_t _f1mWindow;
  Double_t _f1Width;
  Double_t _allf1mWindow;
  Double_t _sidef1mWindowlow;
  Double_t _sidef1mWindowhigh;
  Double_t _chi4Ccut;
  Double_t _pi0m;
  Double_t _pi0mWindow;
  Double_t _Energycut;
  Double_t _etapiem;
  Double_t _etapiemWindow;
  Double_t _f1285m;
  Double_t _f1285mWindow;
  Double_t _Kstarm;
  Double_t _KstarmWindow;
  Double_t _Kstar1m;
  Double_t _Kstar1mWindow;
  Double_t _phi1020m;
  Double_t _phi1020mWindow;
  Double_t _Jpsim;
  bool _addMassWindow;

  bool _showNevents;
  bool _useshapeWeight;
  bool _useData;
  bool _useomegaKK;
  bool _useomegaKK2M;
  bool _usehadron;
  bool _useStack;
  bool _signalInStack;

  bool _useSoverSqrtSplusB;

};

#endif


