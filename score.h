#ifndef SCORE_H_
#define SCORE_H_
#include<iostream>
#include "util.h"
using namespace std;
class Score
{
	private:
		int score;
	public:
        Score();
        int getscore();
        void setscore(int);
};
#endif
