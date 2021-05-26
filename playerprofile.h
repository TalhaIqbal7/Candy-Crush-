#ifndef PLAYERPROFILE_H_
#define PLAYERPROFILE_H_
#include<iostream>
#include "util.h"
using namespace std;
class PlayerProfile
{
	private:
        string name;
		int hs;
	public:
        PlayerProfile();
		string getpn();
		void setpn(string);
		int geths();
		void seths(int);
};
#endif
