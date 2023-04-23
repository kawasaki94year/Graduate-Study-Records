#include "menus.h"
//Root classes
#include "TString.h"
//Others
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

menus::menus(double eP, TString smapleType, TString MCorData ){
  _outputlevel=1;
  _lineWidth = 2;
  _MCorData = MCorData;
  _sampleType = smapleType;
  if(_MCorData == "Data") _sampleType == "KKeta";
  _flatMCround=0;
  _useISRUncert=0;
  _studydir="Final";//"XSection"; //"Final"; 
  _infiledir = "../Root/";
  _resultsdir = "/home/xwl/root-file/";
  _scaleFormat = "";//"toDataShape"; //"toSignalShape"; //"toLumi";
  _savedFileName = ".eps";
  _eP = eP;
  _PI=3.1415926;
  _etam=0.547862;
  _etamWindow = 0.025;
  _pi0m = 0.1349768;
  _pi0mWindow = 0.015;
  _allf1mWindow = 0.18;
  _sidef1mWindowlow = 4*_f1Width;
  _sidef1mWindowhigh = 6*_f1Width;
  _chi4Ccut=30.;
  _Energycut=0.8;
  _etapiem=0.95778;
  _etapiemWindow = 0.015;
  _f1285m = 1.2819;
  _f1285mWindow = 0.045;
  _Kstarm = 0.89176;
  _KstarmWindow = 0.07;
  _phi1020m = 1.019461;
  _phi1020mWindow = 0.012;
  _Kstar1m = 0.89555;
  _Kstar1mWindow = 0.07;
  _Jpsim = 3.0969;
//Mainly for the mass plots
 _addMassWindow=false;
 //mainly for the signal/bkg compare and MC/data compare
 _showNevents = false;
 _useshapeWeight = true; 
 _useData = false; 
 _useomegaKK = false; 
 _useomegaKK2M = false; 
 _usehadron = false; 
 _useStack = false;
 _signalInStack = false;
 if( _scaleFormat == "toDataShape" && !_useData ){
   cout<<"When not use data, the scaleformat is using toDataShape, please check"<<endl;
 }
 if( _scaleFormat != "toLumi" && _useStack ){
   _useStack=false;
 } 
//mainly for S/B study
 _useSoverSqrtSplusB = true;


  if ( _eP == 3.6860 ) { _ePAtfilename = "3.6860"; _ePAtfilenameFinal = "3.6860"; }


}


