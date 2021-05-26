//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include "gems.h"
#include "mouseclicked.h"
#include "playerprofile.h"
#include "score.h"
#include <iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<ctime>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void mainmenu();
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
 Gems obj;
void sethighscore(int latestscore)
{
	int array[5]={0,0,0,0,0};
	string arrstr[5];
	string score;
	int j=0;
	ifstream fin ("highscore.txt"); 
	if (fin.is_open())
	{
		while(getline(fin,score)) 
		{
		  arrstr[j]=score;
		  j=j+1;
		}
		fin.close();
	}
	for(int i=0;i<4;++i)
	{
		stringstream convert(arrstr[i]);
		convert>>array[i];
	}
	array[4]=latestscore;
	int n = sizeof(array)/sizeof(array[0]);
	sort(array,array+n,greater<int>());
	for(int i=0;i<4;++i)
	{
		stringstream a;
		a<<array[i];
		a>>arrstr[i];
	}
	ofstream fout;
	fout.open ("highscore.txt");
	for (int i=0; i<4; i++){
		fout<<arrstr[i]<<endl;
	}	
	fout.close();
	int pos=5;
	for(int i=0;i<4;++i)
	{
		if(array[i]==latestscore)
		pos=i;
	}
	string names[4];
	string var;
	int k=0;
	ifstream h ("highscorename.txt"); 
	if (h.is_open())
	{
		while(getline(h,var)) 
		{
		  names[k]=var;
		  k=k+1;
		}
		h.close();
	}
	for(int k=0;k<4;++k)
	cout<<names[k];
	string nn;
	nn=obj.getpn();
	if(pos==0){
	names[3]=names[2];
	names[2]=names[1];
	names[1]=names[0];
	names[0]=nn;}
	if(pos==1){
	names[3]=names[2];
	names[2]=names[1];
	names[1]=nn;
	}
	if(pos==2){
	names[3]=names[2];
	names[2]=nn;
	}
	if(pos==3){
	names[3]=nn;
	}
	ofstream fou;
	fou.open ("highscorename.txt");
	for (int i=0; i<4; i++){
		fou << names[i] << endl;
	}
	fou.close();
}
void Highscores();
void GameDisplay()/**/{
		Score obj2;
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//Fire Gun
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	/*//Mushroom
	DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Spider
	DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)


	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
	DrawCircle(50,670,10,colors[RED]);
	DrawCircle(70,670,10,colors[RED]);
	DrawCircle(90,670,10,colors[RED]);
	DrawRoundRect(500,200,50,100,colors[DARK_SEA_GREEN],70);
	DrawRoundRect(100,200,100,50,colors[DARK_OLIVE_GREEN],20);	
	DrawRoundRect(100,100,50,100,colors[DARK_OLIVE_GREEN],30);
	DrawRoundRect(200,100,100,50,colors[LIME_GREEN],40);
	DrawRoundRect(350,100,100,50,colors[LIME_GREEN],20);*/
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int w, h, nrChannels;
	unsigned char *data = stbi_load("newgame.jpg", &w, &h, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		
	glLoadIdentity();
	glDisable(GL_LIGHTING);


	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);


	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 920, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(820, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(820,920 , 0);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	DrawString( 330, 120,obj.getpn(), colors[BLACK]);
	static int sw=1;
	static int lscore=650;
	if(obj.getms()>650)
	{
		sw=0;
	}
	if(obj.getms()<0)
	{
		sethighscore(lscore);
		glutDisplayFunc(mainmenu);
	}
	if(sw==0)
	{
		if(obj.getp()==0)
		obj.setms(-2);
	}
	if(obj.getms()>50)
	{
		DrawRoundRect(160,845,45,30,colors[DARK_OLIVE_GREEN],10);
	}
	if(obj.getms()>100)
	{
		DrawRoundRect(200,845,45,30,colors[DARK_OLIVE_GREEN],10);
	}
	if(obj.getms()>150)
	{
		DrawRoundRect(240,845,45,30,colors[DARK_OLIVE_GREEN],10);
	}
	if(obj.getms()>200)
	{
		DrawRoundRect(280,845,45,30,colors[DARK_OLIVE_GREEN],10);
	}
	if(obj.getms()>250)
	{
		DrawRoundRect(320,845,45,30,colors[DARK_OLIVE_GREEN],10);
	}
	if(obj.getms()>300)
	{
		DrawRoundRect(360,845,45,30,colors[DARK_OLIVE_GREEN],10);
	}
	if(obj.getms()>350)
	{
		DrawRoundRect(400,845,45,30,colors[DARK_OLIVE_GREEN],10);
	}
	if(obj.getms()>400)
	{
		DrawRoundRect(440,845,45,30,colors[DARK_OLIVE_GREEN],10);
	}
	if(obj.getms()>450)
	{
		DrawRoundRect(480,845,45,30,colors[DARK_OLIVE_GREEN],10);
	}
	if(obj.getms()>550)
	{
		DrawRoundRect(520,845,90,30,colors[DARK_OLIVE_GREEN],10);
	}
	if(obj.getms()>600)
	{
		DrawRoundRect(560,845,45,30,colors[DARK_OLIVE_GREEN],10);
	}
	if(obj.getms()>650)
	{
		DrawRoundRect(600,845,45,30,colors[DARK_OLIVE_GREEN],10);
	}
	//cout<<"score"<<obj.getms()<<endl;
	string dispvar;
	stringstream ss;
	ss<<obj.getms();
	ss>>dispvar;
	string ls;
	stringstream s;
	s<<lscore;
	s>>ls;
	if(sw==1)
	DrawString(410,885,dispvar,colors[BLACK]);
	if(sw==0)
	DrawString(410,885,ls,colors[BLACK]);
	int myarray[8][8];
	for(int i=0;i<8;++i)
	{
	    for(int j=0;j<8;++j)
        {
			myarray[i][j]=obj.getarray(i,j);
			//cout<<" "<<myarray[i][j];
		}
	}
	for(int i=0;i<8;++i)
	{
	    for(int j=0;j<6;++j)
    	{
			if(myarray[i][j]==myarray[i][j+1] && myarray[i][j+1]==myarray[i][j+2])
			{
				obj.setarray(i,j,10);
				obj.setarray(i,j+1,10);
				obj.setarray(i,j+2,10);
				obj.setms(10);
				if(sw==0)
				lscore=lscore+30;
			}
		}
	}
	for(int i=0;i<6;++i)
	{
	    for(int j=0;j<8;++j)
    	{
			if(myarray[i][j]==myarray[i+1][j] && myarray[i+1][j]==myarray[i+2][j])
			{
				obj.setarray(i,j,10);
				obj.setarray(i+1,j,10);
				obj.setarray(i+2,j,10);
				obj.setms(10);
				if(sw==0)
				lscore=lscore+30;
			}
		}
	}	
	for(int j=800;j>200;j=j-85)
	for(int i=60;i<900;i=i+100)	
	{
		//if(obj1.getx1()==i/100 && obj1.gety1()==-1*((j-800)/85))

		//cout<<i/100<<"  "<<-1*((j->>800)/85)<<endl;
		if(myarray[i/100][-1*((j-800)/85)]==0){
		DrawCircle(i,j,30,colors[RED]);
		DrawCircle(i,j,15,colors[YELLOW]);}
		if(myarray[i/100][-1*((j-800)/85)]==1){
		DrawRoundRect(i-35,j-25,70,40,colors[ORANGE],20);
		DrawCircle(i,j-5,15,colors[BLUE]);}
		if(myarray[i/100][-1*((j-800)/85)]==2){
		DrawSquare(i-25,j-25 ,50,colors[GREEN]);
		DrawSquare(i-20,j-20 ,20,colors[YELLOW]);
		DrawSquare(i,j ,20,colors[YELLOW]);}
		if(myarray[i/100][-1*((j-800)/85)]==3)
		DrawTriangle(i+25, j+25 ,i,j-25,i-25,j+25,colors[BLUE]);
		if(myarray[i/100][-1*((j-800)/85)]==4){
		DrawTriangle(i+25, j ,i,j-35,i-25,j,colors[WHITE]);
		DrawTriangle(i+25, j ,i,j+35,i-25,j,colors[WHITE]);
		DrawCircle(i,j,10,colors[BLACK]);}
		if(myarray[i/100][-1*((j-800)/85)]==5){
		DrawRoundRect(i-35,j-25,70,30,colors[LIGHT_YELLOW],20);
		DrawTriangle(i+25, j ,i,j+35,i-25,j,colors[LIGHT_YELLOW]);
		DrawTriangle(i+25, j ,i,j-35,i-25,j,colors[LIGHT_YELLOW]);
		DrawSquare(i-10,j-10 ,20,colors[WHITE]);}
		if(myarray[i/100][-1*((j-800)/85)]==6){
		DrawTriangle(i+35, j ,i,j+35,i-35,j,colors[MAGENTA]);
		DrawTriangle(i+35, j ,i,j-35,i-35,j,colors[MAGENTA]);
		DrawSquare(i-25,j-25 ,50,colors[MAGENTA]);
		DrawCircle(i,j,10,colors[BLUE]);
		}
	}
		for(int i=0;i<8;++i)
		{
		    for(int j=0;j<8;++j)
    		{
				if(myarray[i][j]==10 && j!=0)
				{
					//obj.setms(5);
					obj.setarray(i,j,obj.getarray(i,j-1));
					obj.setarray(i,j-1,10);
				}
				if(myarray[i][j]==10 && j==0)
				{
					//obj.setms(5);
					obj.setarray(i,j,rand()%7);
				}
			}
		}
	if(obj.getp()==1)
	{
		DrawRoundRect(150,450,500,300,colors[BLACK],10);
		DrawString(340,650,"PAUSED",colors[WHITE]);
		DrawString(280,550,"PRESS C TO CONTINUE",colors[WHITE]);
	}
	glutSwapBuffers(); // do not modify this line..
	glutPostRedisplay();
}
void mainmenu()
{
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//Fire Gun
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	/*//Mushroom
	DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Spider
	DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)


	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
	DrawCircle(50,670,10,colors[RED]);
	DrawCircle(70,670,10,colors[RED]);
	DrawCircle(90,670,10,colors[RED]);
	DrawRoundRect(500,200,50,100,colors[DARK_SEA_GREEN],70);
	DrawRoundRect(100,200,100,50,colors[DARK_OLIVE_GREEN],20);	
	DrawRoundRect(100,100,50,100,colors[DARK_OLIVE_GREEN],30);
	DrawRoundRect(200,100,100,50,colors[LIME_GREEN],40);
	DrawRoundRect(350,100,100,50,colors[LIME_GREEN],20);*/
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int w, h, nrChannels;
	unsigned char *data = stbi_load("menu.jpg", &w, &h, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		
	glLoadIdentity();
	glDisable(GL_LIGHTING);


	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);


	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 920, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(820, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(820,920 , 0);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();

}

void Setting()
{
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//Fire Gun
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	/*//Mushroom
	DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Spider
	DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)


	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
	DrawCircle(50,670,10,colors[RED]);
	DrawCircle(70,670,10,colors[RED]);
	DrawCircle(90,670,10,colors[RED]);
	DrawRoundRect(500,200,50,100,colors[DARK_SEA_GREEN],70);
	DrawRoundRect(100,200,100,50,colors[DARK_OLIVE_GREEN],20);	
	DrawRoundRect(100,100,50,100,colors[DARK_OLIVE_GREEN],30);
	DrawRoundRect(200,100,100,50,colors[LIME_GREEN],40);
	DrawRoundRect(350,100,100,50,colors[LIME_GREEN],20);*/
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int w, h, nrChannels;
	unsigned char *data = stbi_load("settings.jpg", &w, &h, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		
	glLoadIdentity();
	glDisable(GL_LIGHTING);


	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);


	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 920, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(820, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(820,920 , 0);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
}
void levelmodes()
{
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//Fire Gun
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	/*//Mushroom
	DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Spider
	DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)


	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
	DrawCircle(50,670,10,colors[RED]);
	DrawCircle(70,670,10,colors[RED]);
	DrawCircle(90,670,10,colors[RED]);
	DrawRoundRect(500,200,50,100,colors[DARK_SEA_GREEN],70);
	DrawRoundRect(100,200,100,50,colors[DARK_OLIVE_GREEN],20);	
	DrawRoundRect(100,100,50,100,colors[DARK_OLIVE_GREEN],30);
	DrawRoundRect(200,100,100,50,colors[LIME_GREEN],40);
	DrawRoundRect(350,100,100,50,colors[LIME_GREEN],20);*/
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int w, h, nrChannels;
	unsigned char *data = stbi_load("levelmodes.jpg", &w, &h, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		
	glLoadIdentity();
	glDisable(GL_LIGHTING);


	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);


	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 920, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(820, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(820,920 , 0);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
}
void Highscores()
{
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//Fire Gun
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	/*//Mushroom
	DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Spider
	DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)


	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
	DrawCircle(50,670,10,colors[RED]);
	DrawCircle(70,670,10,colors[RED]);
	DrawCircle(90,670,10,colors[RED]);
	DrawRoundRect(500,200,50,100,colors[DARK_SEA_GREEN],70);
	DrawRoundRect(100,200,100,50,colors[DARK_OLIVE_GREEN],20);	
	DrawRoundRect(100,100,50,100,colors[DARK_OLIVE_GREEN],30);
	DrawRoundRect(200,100,100,50,colors[LIME_GREEN],40);
	DrawRoundRect(350,100,100,50,colors[LIME_GREEN],20);*/
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int w, h, nrChannels;
	unsigned char *data = stbi_load("highscore.jpg", &w, &h, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		
	glLoadIdentity();
	glDisable(GL_LIGHTING);


	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);


	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 920, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(820, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(820,920 , 0);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	float *scolor2 = colors[WHITE];
	string score;
	int i=0;
	ifstream fin ("highscore.txt"); 
	if (fin.is_open())
	{
		while(getline(fin,score)) 
		{
			DrawString(500,750+i,score, colors[WHITE]);
			i=i-50;
		}
		fin.close();
	}
	int k=0;
	string var;
	ifstream hin ("highscorename.txt"); 
	if (hin.is_open())
	{
		while(getline(hin,var)) 
		{
			DrawString(300,750+k,var, colors[WHITE]);
			k=k-50;
		}
		fin.close();
	}
	DrawString(250,750,"1.", colors[WHITE]);
	DrawString(250,700,"2.", colors[WHITE]);
	DrawString(250,650,"3.", colors[WHITE]);
	DrawString(250,600,"4.", colors[WHITE]);
	glutSwapBuffers();
	glutPostRedisplay();
}
/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
	}
	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
	}
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'p' || key == 'P') //Key for placing the bomb
			{
		//do something if b is pressed
		glutDisplayFunc(GameDisplay);

	}
		if (key == 'r' || key == 'R') //Key for placing the bomb
			{
		//do something if b is pressed
		glutDisplayFunc(mainmenu);

	}
	if (key == 'H' || key == 'h') //Key for placing the bomb
			{
		//do something if b is pressed
		glutDisplayFunc(Highscores);
	}
 	if (key == 's' || key == 'S') //Key for placing the bomb
			{
		//do something if b is pressed
		glutDisplayFunc(Setting);

	}
		if (key == 'l' || key == 'L') //Key for placing the bomb
			{
		//do something if b is pressed
		glutDisplayFunc(levelmodes);

	}

		if (key == 'e' || key == 'E') //Key for placing the bomb
			{
		//do something if b is pressed
		exit(0);}
		if (key == 'z' || key == 'Z') //Key for placing the bomb
		{
			obj.setp(1);
		}
		if (key == 'c' || key == 'C') //Key for placing the bomb
		{
			obj.setp(0);
		}
		

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
//	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
MouseClicked obj1;
void MouseClicked(int button, int state, int x, int y)
{
	int bol=0;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) // dealing only with left button
	{
		//cout<<obj1.getstate();
		if(obj1.getstate()==1)
		{
				if(x>10 && x<810 && y>80 && y<760)
				{
					obj1.setx1((x-11)/100);
					obj1.sety1((y-85)/85);
					obj1.settemp(obj.getarray((x-11)/100,(y-85)/85));
					//cout<<"1";
					obj1.setstate(0);
				}
		}
		else
		{		
				if(x>10 && x<810 && y>80 && y<760)
				{
					obj1.settemp2(obj.getarray((x-11)/100,(y-85)/85));
					obj.setarray(obj1.getx1(),obj1.gety1(),obj1.gettemp2());
					obj.setarray((x-11)/100,(y-85)/85,obj1.gettemp());
					if((obj1.gety1()==(y-85)/85 && (obj1.getx1()==((x-11)/100)+1 || obj1.getx1()==((x-11)/100)-1)) || (obj1.getx1()==(x-11)/100) && (obj1.gety1()==((y-85)/85)-1 || obj1.gety1()==((y-85)/85)+1))
					{
						for(int i=0;i<6;++i)
						{
						    for(int j=0;j<8;++j)
    						{
								if(obj.getarray (i,j)  ==  obj.getarray(i+1,j) && obj.getarray (i,j)  ==  obj.getarray(i+2,j))
								{
									bol=1;
								}
							}
						}
						for(int i=0;i<8;++i)
						{
						    for(int j=0;j<6;++j)
    						{
								if(obj.getarray (i,j)  ==  obj.getarray(i,j+1) && obj.getarray (i,j)  ==  obj.getarray(i,j+2))
								{
									bol=1;
								}
							}
						}
					}
					if(bol==0)
					{
								obj.setarray(obj1.getx1(),obj1.gety1(),obj1.gettemp());
								obj.setarray((x-11)/100,(y-85)/85,obj1.gettemp2());
					}
					obj1.setstate(1);
					//cout <<"2";
				}
		}
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && x>720 && x<790 && y>0 && y<70)
	{
		for(int j=600;j>200;j=j-85)
		{
			for(int i=60;i<700;i=i+100)
			{
				int one=i/100;
				int two=-1*((j-800)/85);
				if(obj.getarray(one,two)==obj.getarray(one+1,two) && obj.getarray(one+3,two)==obj.getarray(one,two))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one+1,two) && obj.getarray(one,two)==obj.getarray(one+2,two+1))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one+1,two) && obj.getarray(one,two)==obj.getarray(one+2,two-1))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one+2,two) && obj.getarray(one,two)==obj.getarray(one+1,two-1))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one+2,two) && obj.getarray(one,two)==obj.getarray(one+1,two+1))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one+2,two) && obj.getarray(one+1,two-1)==obj.getarray(one,two))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one+2,two) && obj.getarray(one+1,two+1)==obj.getarray(one,two))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one+1,two) && obj.getarray(one-2,two)==obj.getarray(one,two))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one,two+1) && obj.getarray(one,two)==obj.getarray(one,two+3))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one,two+1) && obj.getarray(one,two)==obj.getarray(one+1,two+2))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one,two+1) && obj.getarray(one,two)==obj.getarray(one-1,two+2))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one,two+2) && obj.getarray(one,two)==obj.getarray(one+1,two+1))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one,two+2) && obj.getarray(one,two)==obj.getarray(one+1,two-1))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one,two+1) && obj.getarray(one,two)==obj.getarray(one,two-2))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one,two+1) && obj.getarray(one,two)==obj.getarray(one-1,two-1))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;
				}
				if(obj.getarray(one,two)==obj.getarray(one,two+1) && obj.getarray(one,two)==obj.getarray(one-1,two+1))
				{
					DrawCircle(i,j+30,25,colors[WHITE]);
					glutSwapBuffers();
					glutPostRedisplay();
					//DrawCircle(i+1,j,25,colors[WHITE]);
					//DrawCircle(i+3,j,25,colors[WHITE]);
					return;;
				}
				glutSwapBuffers();
				glutPostRedisplay();
	
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
		DrawSquare(10,10 ,20,colors[WHITE]);
		glutSwapBuffers();
		glutPostRedisplay();
		
	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
 void name(){
 	cout<<"ENTER YOUR NAME"<<endl;
	 string p;
	cin>>p;
	obj.setpn(p);}
int main(int argc, char*argv[]) {
	name();
	int width = 820, height = 920; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Project"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(mainmenu); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
