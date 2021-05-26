#include<iostream>
#include"gems.h"
#include<ctime>
using namespace std;;
Gems::Gems()
{
        pause=0;
        srand(time(0));
        for(int i=0;i<8;++i)
        {
                for(int j=0;j<8;++j)
                {
                        array[i][j]=rand()%7;
                }
        }
        ms=0;
}
void Gems::GemsCheck()
{
        for(int i=0;i<8;++i)
        {
                for(int j=0;j<8;++j)
                {
                        cout<<array[i][j];
                }
        }
}
int Gems::getarray(int i, int j)
{
    return array[i][j];
}
int Gems::setarray(int i, int j,int temp)
{
    array[i][j]=temp;
}
int Gems::getms()
{
        return ms;
}
void Gems::setms(int i)
{
        ms=ms+i;
}
void Gems::setpn(string pn)
{
    name=pn;;
}
string Gems::getpn()
{
    return name;
}
void Gems::setp(int pn)
{
    pause=pn;
}
int Gems::getp()
{
    return pause;
}