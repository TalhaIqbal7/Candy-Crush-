#ifndef GEMS_H_
#define GEMS_H_
#include<iostream>
#include "util.h"
using namespace std;
class Gems
{
	private:
		int array[8][8];
		int ms;
		string name;
		int pause;
	public:
		Gems();
		void GemsCheck();
		int getarray(int,int);
		int setarray(int,int,int);
		int getms();
		void setms(int i);
		string getpn();
		void setpn(string);
		int getp();
		void setp(int i);
};
#endif
