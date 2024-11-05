/**
 * @file demo.c
 * @author Gerardo Gonzalez
 * @date 2024-11-05
 * @brief controls a game demo
 * 
 * The demo.c file controls a game demo, showing various visuals like titles, blocks, paddles, and animations to guide the user through different stages.
 */


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
 * $Id: demo.c,v 1.1.1.1 1994/12/16 01:36:46 jck Exp $
 * $Source: /usr5/legends/jck/xb/master/xboing/demo.c,v $
 * $Revision: 1.1.1.1 $
 * $Date: 1994/12/16 01:36:46 $
 *
 * $Log: demo.c,v $
 * Revision 1.1.1.1  1994/12/16  01:36:46  jck
 * The XBoing distribution requires configuration management. This is why the
 * cvs utility is being used. This is the initial import of all source etc..
 *
 *
 * =========================================================================
 */

/*
 *  Include file dependencies:
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <xpm.h>

#include "error.h"
#include "misc.h"
#include "gun.h"
#include "file.h"
#include "main.h"
#include "init.h"
#include "inst.h"
#include "stage.h"
#include "blocks.h"
#include "sfx.h"
#include "special.h"
#include "ball.h"
#include "score.h"
#include "paddle.h"
#include "level.h"
#include "mess.h"
#include "audio.h"
#include "intro.h"
#include "keys.h"
#include "version.h"

#include "demo.h"

/*
 *  Internal macro definitions:
 */

#define GAP 10
#define COL2X(x, col) (x = col * colWidth)
#define ROW2Y(y, row) (y = row * rowHeight)


/*
 *  Internal type declarations:
 */

void SetDemoWait(enum DemoStates newMode, int waitFrame);
void DoDemoWait(void);

/*
 *  Internal variable declarations:
 */

static int endFrame = 0;
static int startFrame = 0;
enum DemoStates DemoState;
static int waitingFrame;
enum DemoStates waitMode;



/**
 * @brief Initializes the demonstration sequence.
 * 
 * Prepares the demonstration by resetting its initial settings, including 
 * resetting the demo state.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the demonstration will be shown.
 * @param colormap The colormap used for creating bitmaps in the demo.
 */
void SetUpDemonstration(Display *display, Window window, Colormap colormap)
{
	ResetDemonstration();
}



/**
 * @brief Displays the title screen in the demonstration.
 * 
 * Draws the title screen for the demonstration by rendering the background 
 * pattern and title bitmap.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the title is drawn.
 */
void DoDemoTitle(Display *display, Window window)
{
	/* Clear and draw background pattern */
    DrawStageBackground(display, window, BACKGROUND_0, True);

	/* Draw the title bitmap XBOING */
	DrawIntroTitle(display, window, 10, 10);
}



/**
 * @brief Draws demo level elements and animations in the demonstration.
 * 
 * Displays demo elements such as blocks, the ball, and text instructions
 * to simulate gameplay interactions.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where elements are drawn.
 */
static void DoBlocks(Display *display, Window window)
{
	int y = 120;
	int x = 40;
    char levelPath[1024];
    char *str;

	/* Be very friendly */
	SetCurrentMessage(display, messWindow, "Demonstration", False);

    /* Construct the demo level filename */
    if ((str = getenv("XBOING_LEVELS_DIR")) != NULL)
      snprintf(levelPath, sizeof(levelPath), "%s/demo.data", str); 
    else
      snprintf(levelPath, sizeof(levelPath), "%s/demo.data", LEVEL_INSTALL_DIR);

	/* Read in a demo level */
    if (ReadNextLevel(display, window, levelPath, True) == False)
        ShutDown(display, 1, "Sorry, invalid level specified.");

	/* Draw the ball anim animation slides */
	x = PLAY_WIDTH - (PLAY_WIDTH / 3) ; y = PLAY_HEIGHT - (PLAY_HEIGHT / 3);
	DrawTheBall(display, window, x, y, 0); 	x -= 18; y += 18;
	DrawTheBall(display, window, x, y, 1); 	x -= 18; y += 18;
	DrawTheBall(display, window, x, y, 2); 	x -= 18; y += 18;
	DrawTheBall(display, window, x, y, 3); 	x -= 18; y += 18;
	DrawTheBall(display, window, x, y, 0); 	x -= 18; y += 18;
	DrawTheBall(display, window, x, y, 1); 	

	x -= 25; y -= 18;
	DrawTheBall(display, window, x, y, 0); 	x -= 18; y -= 18;
	DrawTheBall(display, window, x, y, 1); 	x -= 18; y -= 18;
	DrawTheBall(display, window, x, y, 2);	x -= 18; y -= 18;
	DrawTheBall(display, window, x, y, 3); 	x -= 18; y -= 18;

	/* Draw a half distintegrated block */
	COL2X(x, 2); ROW2Y(y, 12);
    RenderShape(display, window, exyellowblock[1], exyellowblockM[1],
		x, y, 40, 20, False);

	/* Draw the paddle with some arrows */
	x = PLAY_WIDTH / 2;
	y = PLAY_HEIGHT - 90;
	RenderShape(display, window, leftarrow, leftarrowM,
        x - 75, y - 1, 35, 19, True);
	DrawPaddle(display, window, x, y, PADDLE_HUGE);

	/* Now draw some descriptive text */
    DrawShadowText(display, window, dataFont,
		"Ball hits the paddle", 300, PLAY_HEIGHT - 140, yellow);
    DrawShadowText(display, window, dataFont,
		"and bounces back.", 300, PLAY_HEIGHT - 120, yellow);

    DrawShadowText(display, window, dataFont,
		"Ball hits block", 30, PLAY_HEIGHT - 170, yellow);
    DrawShadowText(display, window, dataFont,
		"and rebounds.", 30, PLAY_HEIGHT - 150, yellow);

    DrawShadowText(display, window, dataFont,
		"Paddle moves left to intercept ball.", 160, PLAY_HEIGHT - 60, yellow);
}



/**
 * @brief Creates a sparkle effect during the demonstration.
 * 
 * Renders a sparkle effect in the window by animating a small sequence of 
 * star images at random positions. The sparkle effect is repeated at intervals.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the sparkle effect is rendered.
 */
static void DoSparkle(Display *display, Window window)
{
    static Pixmap store;
    static int x = 100;
    static int y = 20;
    static int in = 0;

    if (!store)
    {
        store = XCreatePixmap(display, window, 20, 20,
            DefaultDepth(display, XDefaultScreen(display)));
    }

    if (in == 0)
        XCopyArea(display, window, store, gc, x, y, 20, 20, 0, 0);

    if (frame == endFrame)
        DemoState = DEMO_FINISH;

    if (frame == startFrame)
    {
        XCopyArea(display, store, window, gc, 0, 0, 20, 20, x, y);
        RenderShape(display, window, stars[in], starsM[in],
            x, y, 20, 20, False);

        in++;
        startFrame = frame + 15;

        if (in == 11)
        {
            XCopyArea(display, store, window, gc, 0, 0, 20, 20, x, y);
            in = 0;
            startFrame = frame + 500;
            x = (rand() % 474) + 5;
            y = (rand() % 74) + 5;
        }
    }
}



/**
 * @brief Displays a prompt message in the demonstration.
 * 
 * Shows a prompt message, such as "Insert coin to start the game,"
 * at a specific position on the screen.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the prompt text is displayed.
 */
static void DoText(Display *display, Window window)
{
	char string[80];
	int y;

	y = PLAY_HEIGHT - 27;

	strcpy(string, "Insert coin to start the game");
	DrawShadowCentredText(display, window, textFont, 
		string, y, tann, PLAY_WIDTH);

	startFrame = frame + 10;
	endFrame = frame + 5000;
	DemoState = DEMO_SPARKLE;
}



/**
 * @brief Completes the demonstration sequence.
 * 
 * Finishes the demonstration by resetting keyboard controls and
 * transitioning to the main game or menu.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window used in the demonstration.
 */
static void DoFinish(Display *display, Window window)
{
    ResetKeys();
    mode = MODE_KEYS;

	if (noSound == False)
		playSoundFile("whizzo", 50);
}



/**
 * @brief Manages the flow of the demonstration sequence.
 * 
 * Based on the current `DemoState`, selects and executes the corresponding
 * function in the demonstration sequence, such as displaying the title,
 * demo blocks, text, or sparkle effects.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the demonstration is shown.
 */
void Demonstration(Display *display, Window window)
{
	switch (DemoState)
	{
		case DEMO_TITLE:
			if (getSpecialEffects(display) == True)
				DoDemoTitle(display, bufferWindow);
			else
				DoDemoTitle(display, window);
			DemoState = DEMO_BLOCKS;
			break;

		case DEMO_BLOCKS:
			if (getSpecialEffects(display) == True)
				DoBlocks(display, bufferWindow);
			else
				DoBlocks(display, window);
			DemoState = DEMO_TEXT;
			break;

		case DEMO_TEXT:
			if (getSpecialEffects(display) == True)
			{
				DoText(display, bufferWindow);
				while (WindowShatterEffect(display, window));
			}
			else
				DoText(display, window);
			break;

		case DEMO_SPARKLE:
			DoSparkle(display, window);
			BorderGlow(display, window);
			if ((frame % FLASH) == 0)
				RandomDrawSpecials(display);
			break;

		case DEMO_FINISH:
			DoFinish(display, window);
			break;

		case DEMO_WAIT:
			DoDemoWait();
			break;

		default:
			break;
	}
}



/**
 * @brief Redraws the demonstration display.
 * 
 * Refreshes the display by redrawing key elements of the demonstration,
 * including the title, blocks, and text, typically used during window exposure.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the demonstration is shown.
 */
void RedrawDemonstration(Display *display, Window window)
{
	DoDemoTitle(display, window);
	DoBlocks(display, window);
	DoText(display, window);
}



/**
 * @brief Frees resources allocated for the demonstration.
 * 
 * Releases resources associated with the demonstration, allowing the system
 * to reclaim memory used for demonstration assets.
 * 
 * @param display Pointer to the X11 display connection.
 */
void FreeDemonstration(Display *display)
{
}



/**
 * @brief Resets the demonstration to its starting state.
 * 
 * Sets the `DemoState` and frame counters back to the initial values,
 * restarting the demonstration from the title screen.
 */
void ResetDemonstration(void)
{
	DemoState = DEMO_TITLE;
	startFrame = frame + 10;
	endFrame = frame + 3000;

	DEBUG("Reset Demonstration mode.")
}



/**
 * @brief Sets a waiting mode and frame for the demonstration sequence.
 * 
 * This function configures the waiting period for the demonstration by specifying
 * the mode and frame to resume normal operation.
 *
 * @param newMode The mode to switch to after waiting.
 * @param waitFrame The frame number at which to end the wait period.
 */
void SetDemoWait(enum DemoStates newMode, int waitFrame)
{
	waitingFrame = waitFrame;
	waitMode = newMode;
	DemoState = DEMO_WAIT;
}



/**
 * @brief Handles the waiting state in the demonstration sequence.
 * 
 * Checks if the current frame matches the designated `waitFrame`, and if so,
 * transitions to the mode specified in `waitMode`.
 */
void DoDemoWait(void)
{
	if (frame == waitingFrame)
		DemoState = waitMode;
}
