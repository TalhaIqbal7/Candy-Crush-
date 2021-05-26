#include<iostream>
#include"mouseclicked.h"
using namespace std;;
MouseClicked::MouseClicked()
{
    state=1;
    temp=0;
    temp2=0;
    int x1=11;
    int y1=11;
}
int MouseClicked::getstate()
{
    return state;
}
int MouseClicked::setstate(int i)
{
    state=i;
}
int MouseClicked::gettemp()
{
    return temp;
}
int MouseClicked::settemp(int i)
{
    temp=i;
}
int MouseClicked::gettemp2()
{
    return temp2;
}
int MouseClicked::settemp2(int i)
{
    temp2=i;
}
int MouseClicked::getx1()
{
    return x1;
}
int MouseClicked::setx1(int i)
{
    x1=i;
}
int MouseClicked::gety1()
{
    return y1;
}
int MouseClicked::sety1(int i)
{
    y1=i;
}