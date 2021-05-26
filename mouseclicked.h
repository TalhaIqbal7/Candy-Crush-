#ifndef MOUSECLICKED_H_
#define MOUSECLICKED_H_
#include<iostream>
#include "util.h"
using namespace std;
class MouseClicked
{
	private:
		int state;
		int temp;
		int temp2;
		int x1;
		int y1;
	public:
		MouseClicked();
		int getstate();
		int setstate(int);
		int gettemp();
		int settemp(int);
		int gettemp2();
		int settemp2(int);
		int getx1();
		int setx1(int);
		int gety1();
		int sety1(int);
};
#endif
