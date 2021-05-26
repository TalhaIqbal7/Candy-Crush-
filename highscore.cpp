#include<iostream>
#include"highscore.h"
#include<ctime>
using namespace std;;
highscore::highscore()
{
    for(int i=0;i<5;++i)
    {
        listint[i]=0;
        list[i]='/0';
    }
}
string highscore::gethsl(int i)
{
    return list[i];
}
void highscore::sethsl(int i,string sc)
{
    list[i]=sc;
}
int highscore::gethsi(int i)
{
    return listint[i];
}
void highscore::sethsi(int i,int sc)
{
    listint[i]=sc;
}
