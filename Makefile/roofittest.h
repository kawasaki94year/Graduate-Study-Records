#ifndef ROOFITTEST_H
#define ROOFITTEST_H

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "menus.h"
//#include "commonFuncs.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace RooFit;

//****** use roofit to fit KS mass and write to WS ******//
           //rooFittest是一个类，这个类继承menus类
class rooFittest : virtual public menus{
 public:
	 //rooFittest 是一个构造函数，ep,samepleType,MCorData是一个参数 
  rooFittest(double eP, TString sampleType, TString MCorData);
  inline virtual ~rooFittest(){};//这是一个析构函数，
				 //virtual是一个虚函数，可以在派生类中被重写,
				 //~rooFittest()是一个析沟函数，它在对象被销毁时调用，用于释放对象占用的资源,
				 //inline 表示这个函数可以被编译器进行内联优化，避免函数调用的开销。
  void writeWS(TString resName);//writesWS是一个公有的函数成员，参数TSring resName 表示结果名称，用于写入结果 
};


#endif


