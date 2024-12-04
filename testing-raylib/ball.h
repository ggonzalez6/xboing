#ifndef _BALL_H_
#define _BALL_H_

/*
 * XBoing - An X11 blockout style computer game
 *
 * (c) Copyright 1993, 1994, 1995, Justin C. Kibell, All Rights Reserved
 *
 * The X Consortium, and any party obtaining a copy of these files from
 * the X Consortium, directly or indirectly, is granted, free of charge, a
 * full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 * nonexclusive right and license to deal in this software and
 * documentation files (the "Software"), including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons who receive
 * copies from any such party to do so.  This license includes without
 * limitation a license to do the foregoing actions under any patents of
 * the party supplying this software to the X Consortium.
 *
 * In no event shall the author be liable to any party for direct, indirect,
 * special, incidental, or consequential damages arising out of the use of
 * this software and its documentation, even if the author has been advised
 * of the possibility of such damage.
 *
 * The author specifically disclaims any warranties, including, but not limited
 * to, the implied warranties of merchantability and fitness for a particular
 * purpose.  The software provided hereunder is on an "AS IS" basis, and the
 * author has no obligation to provide maintenance, support, updates,
 * enhancements, or modifications.
 */

/* 
 * =========================================================================
 *
 * $Id: ball.h,v 1.1.1.1 1994/12/16 01:36:50 jck Exp $
 * $Source: /usr5/legends/jck/xb/master/xboing/include/ball.h,v $
 * $Revision: 1.1.1.1 $
 * $Date: 1994/12/16 01:36:50 $
 *
 * $Log: ball.h,v $
 * Revision 1.1.1.1  1994/12/16  01:36:50  jck
 * The XBoing distribution requires configuration management. This is why the
 * cvs utility is being used. This is the initial import of all source etc..
 *
 *
 * =========================================================================
 */

/*
 *  Dependencies on other include files:
 */

// TODO: Remove x11 #include <X11/Xlib.h>
//#include <faketypes.h>

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <values.h>
/*
 *  Constants and macros:
 */

#define BALL_WIDTH  		20
#define BALL_HEIGHT 		19
#define MAX_BALL_MASS 		3.0
#define MIN_BALL_MASS 		1.0

#define BALL_WC     		(BALL_WIDTH / 2)
#define BALL_HC     		(BALL_HEIGHT / 2)

#define BIRTH_SLIDES        8
#define BALL_SLIDES         5

#define MAX_BALLS 			5

#define MAX_X_VEL           14
#define MAX_Y_VEL           14

#define MIN_DY_BALL			2
#define MIN_DX_BALL			2

#define BALL_ANIM_RATE      50
#define BIRTH_FRAME_RATE    5
#define BALL_FRAME_RATE     5
#define BORDER_ANIM_DELAY   15

#define PADDLE_HIT_SCORE    10

#define BALL_AUTO_ACTIVE_DELAY  3000

#define DIST_BALL_OF_PADDLE 45

#define PADDLE_BALL_FRAME_TILT  5000

//Temporary
#define PLAY_HEIGHT 580
#define PLAY_WIDTH 495
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 582
//const int False = 0;
//const int True = 1;
#define True 0
#define False 1
/*
 *  Type declarations:
 */

enum BallStates 
{ 
	BALL_POP, 
	BALL_ACTIVE, 
	BALL_STOP, 
	BALL_CREATE, 
	BALL_DIE, 
	BALL_WAIT, 
	BALL_READY, 
	BALL_NONE 
};

typedef struct Ball
{
	enum BallStates	waitMode;		/* Ball waiting mode */
	int				waitingFrame;	/* Frame to wait until */
	int				newMode;		/* Ball's new mode */
	int				nextFrame;		/* next frame for something */
	int				active;			/* True - in use, False - dead */

  Vector2 position;
  Vector2 velocity;
    int             slide;			/* Current pixmap visible */
	float          	radius;			/* The radius of the ball */
	float          	mass;			/* The mass of the ball */
	int 			lastPaddleHitFrame;	/* Last frame the ball hit paddle */
    enum BallStates	ballState;		/* The state of the ball */
  Color color;
  Texture2D texture;
} Ball;

/*
 *  Function prototypes:
 */
//added
void UpdateABall(Ball balls[], int i);

//NOTE:  all commented out functions are likely either animations or powerups
//       exceptions will be commented
void InitialiseBall(Ball balls[], int i, char *texturePath, Vector2 startPos, float radius);
//void FreeBall(Display *display);

//not even implimented
//void RedrawBall(Display *display, Window window);

void DrawTheBall(Ball balls[], int theBall);
//void DrawTheBallBirth(Display *display, Window window, int x, int y, int slide);

//will be needed for demo
//void KillBallNow(Display *display, Window window, int i);

//should be accessible anyways
//void GetBallPosition(int *ballX, int *ballY, int i);

//needed for demo
//void ResetBallStart(Display *display, Window window);

//not even implimented
//int GetBallMode(int i);

//likely needed for demo
//void ChangeBallMode(enum BallStates newMode, int i);

int AddANewBall(Ball balls[],  int x, int y, int dx, int dy);
void ClearAllBalls(void);

//demo
//void HandleBallMode(Display *display, Window window);

//not implimented
//int StartAnotherBall(Display *display, Window window);

//probably wont be used until demo. should compile
int IsBallWaiting(void);

void ClearBall(int i);

//powerups not in scope rn
//void SplitBallInTwo(Display *display, Window window);

//current functions shoudl suffice
//void ClearBallNow(Display *display, Window window, int i);

//easy to convert with no major overhauls. might not be used.
int GetAnActiveBall(void);

//deal with this in demo when ball states matter
//int ActivateWaitingBall(Display *display, Window window);

//easy to change. no powerups means no use however
int GetNumberOfActiveBalls(void);

//hopefully doesnt mess with collision too much
//void DoBoardTilt(Display *display, int i);

extern Ball balls[MAX_BALLS];
extern int speedLevel;
extern int paddleDx;

#endif
