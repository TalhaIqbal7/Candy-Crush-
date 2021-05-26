#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_
#include<iostream>
#include "util.h"
using namespace std;
class highscore
{
	private:
		string list[5];
        int listint[5];
	public:
		highscore();
		string gethsl(int);
		void sethsl(int,string);
		int gethsi(int);
		void sethsi(int,int);
};
#endif
