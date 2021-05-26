#include<iostream>
#include"playerprofile.h"
using namespace std;;
PlayerProfile::PlayerProfile()
{
    hs=0;
    name='/0';
}
void PlayerProfile::setpn(string pn)
{
    name=pn;;
}
string PlayerProfile::getpn()
{
    return name;
}
void PlayerProfile::seths(int pn)
{
    hs=pn;;
}
int PlayerProfile::geths()
{
    return hs;
}