//============================================================================
// Name        : .cpp
// Author      : FAST CS Department
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include <ctime>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

int moving=0, speed =3, direction = 0, last_direction=0;
bool touching=false;

int walls[][4]= {{2,5,17,1}, {10,20,17,1}, {13,17,7,2}, {5,7,13,1}, {2,4,13,1},{11,13,3,2}, 
			{3,7,3,2}, {3,7,4,2}, {3,7,5,2},
			{2,5,8,2},
			{15,20,5,1} , {3,6,14,2},
			{8,12,9,1}, {10,15,14,2}, {15,18,12,1}};

void NonPrintableKeys(int key, int x, int y);

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


int xI = 0, yI = 608;

void drawCar() {
	DrawSquare(xI, yI, 20, colors[RED]);
	glutPostRedisplay();
}

void checkTouching(int xy1, int xy2, int xy, int d)
{
	bool colX;
	bool colY;

	if(d == 1)
	{
		colX = xy2*32 >= xI && xI+20 >= xy1*32;
		colY = (xy+1)*32 >= yI && yI+20 >= xy*32;
	}
	else if (d == 2)
	{
		colX = (xy+1)*32 >= xI && xI+20 >= xy*32;
		colY = xy2*32 >= yI && yI+20 >= xy1*32;		
	}
	

	// cout << "x1: " << x1*32 <<endl;
	// cout << "x2: " << x2*32 <<endl;
	// cout << "y1: " << y1*32 <<endl;
	// cout << "y2: " << (y1+1)*32 <<endl;
	// cout << "car x1: " << xI <<endl;
	// cout << "car x2: " << xI+20 <<endl;
	// cout << "car y1: " << yI <<endl;
	// cout << "car y2: " << yI+20 <<endl;
	
	
	
	if (colX && colY)
	{
		last_direction = direction;
		// makes direction = 0;
		NonPrintableKeys(0,0,0);
		
		touching = true;
	}
	else
	{
		touching = false;
	}
}
void drawRoads()
{

	for(int i=0; i <= 20; i ++)
	{
		DrawLine( i*32 , 0 ,  i*32 , 640 , 1 , colors[MISTY_ROSE] );
		DrawLine( 0, i*32 ,  640 , i*32 , 1 , colors[MISTY_ROSE] );
	}

	for(int i=0; i <15; i++)
	{
		DabbaBanaoNEW(walls[i][0], walls[i][1], walls[i][2], walls[i][3], colors[DARK_GRAY]);
	}
	// DabbaBanaoNEW(2,5,17,1, colors[DARK_GRAY]);	
	// DabbaBanaoNEW(10,20,17,1, colors[DARK_GRAY]);
	// DabbaBanaoNEW(13,17,7,2, colors[DARK_GRAY]);
	// DabbaBanaoNEW(5,7,13,1, colors[DARK_GRAY]);
	// DabbaBanaoNEW(2,4,13,1, colors[DARK_GRAY]);
	// DabbaBanaoNEW(11,13,3,2, colors[DARK_GRAY]);

	// DabbaBanaoNEW(3,7,3,2, colors[DARK_GRAY]);
	// DabbaBanaoNEW(3,7,4,2, colors[DARK_GRAY]);
	// DabbaBanaoNEW(3,7,5,2, colors[DARK_GRAY]);

	// DabbaBanaoNEW(2,5,8,2, colors[DARK_GRAY]);

	// DabbaBanaoNEW(15,20,5,1, colors[DARK_GRAY]);
	// DabbaBanaoNEW(3,6,14,2, colors[DARK_GRAY]);


	// DabbaBanaoNEW(8,12,9,1, colors[DARK_GRAY]);
	// DabbaBanaoNEW(10,15,14,2, colors[DARK_GRAY]);
	// DabbaBanaoNEW(15,18,12,1, colors[DARK_GRAY]);


}

bool flag = true;
void moveCar() {
	
	if (xI > 10 && flag) {
		xI -= 10;
		cout << "going left";
		if(xI < 100)
			
			flag = false;

	}
	else if (xI < 1010 && !flag) {
		cout << "go right";
		xI += 10;
		if (xI > 900)
			flag = true;
	}
}

void movecar()
{
	// if(moving == 0)
	// {
	// 	car_timer = time(NULL);
	// }

	
	if(direction == 1)
	{
		if(!touching && last_direction !=1)
		{
			xI += speed;
			//cout << "right ";
		}
	}
	else if(direction == -1)
	{
		if(!touching && last_direction != -1)
		{
			xI -= speed;
			//cout << "left ";
		}	
	}
	else if(direction == 2)
	{
		if(!touching && last_direction != 2)
		{
			yI += speed;
			//cout << "up ";
		}	
		
	}
	else if(direction == -2)
	{
		if(!touching && last_direction != -2)
		{
			yI -= speed;
			//cout << "down ";
		}	
	}
	
	// if( (moving == 1) &&  (time(NULL) - car_timer >= 0.5))
	// {
	// 	direction = 0;
	// 	moving = 0;
	// }
	

}

/*
 * Main Canvas drawing function.
 * */

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	// //Red Square
	// DrawSquare(400, 20, 40, colors[RED]);
	
	 //Green Square
	 //DrawSquare( 128 , 128 ,30,colors[GREEN]); 
	
	// //Display Score
	// DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	
	// // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	// DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	


	// //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	// DrawLine( 550 , 50 ,  550 , 480 , 1 , colors[MISTY_ROSE] );	
	// DrawLine( 400 , 50 ,  550 , 50 , 32 , colors[MISTY_ROSE] );	
	
	// DrawCircle(50,670,10,colors[RED]);
	// DrawCircle(70,670,10,colors[RED]);
	// DrawCircle(90,670,10,colors[RED]);
	//DrawRoundRect(500,200,50,100,colors[DARK_SEA_GREEN],70);
	//DrawRoundRect(512,512,128,32,colors[DARK_OLIVE_GREEN],20);	

	drawRoads();

	for(int i=0; i <15; i++)
	{
		checkTouching(walls[i][0], walls[i][1], walls[i][2], walls[i][3]);
	}




	//DabbaBanao(256,544,288,416, colors[DARK_SEA_GREEN]);	

	// DrawRoundRect(100,100,50,100,colors[DARK_OLIVE_GREEN],30);
	// DrawRoundRect(200,100,100,50,colors[LIME_GREEN],40);
	// DrawRoundRect(350,100,100,50,colors[LIME_GREEN],20);
	
	drawCar();
	
	//moveCar();
	glutSwapBuffers(); // do not modify this line..

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

	

	if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) 
	{
		// what to do when left key is pressed...
		//xI -= 10;
		direction = -1;
	} 
	else if (key== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) 
	{
		//xI += 10;
		direction = 1;
	} 
	else if (key== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
	{
		//yI += 10;
		direction = 2;
	}
	else if (key== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		
		//yI -= 10;
		direction = -2;
	}
	else 
	{
		direction = 0;
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

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}

	if (key == 's'|| key == 'S')
	{
		direction = 0;
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
	//moveCar();

	movecar();

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(10, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
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
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 640, height = 640; // i have set my window size to be 640 x 640

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by BrokenGroup"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(100.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse





	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
