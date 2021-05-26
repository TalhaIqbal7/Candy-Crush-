#include<iostream>
#include"score.h"
#include<ctime>
using namespace std;
Score::Score()
{
    score=0;
}
int Score::getscore()
{
    return score;
}
void Score::setscore(int i)
{
    score=score+i;
}