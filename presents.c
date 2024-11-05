
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
 * $Id: presents.c,v 1.1.1.1 1994/12/16 01:36:48 jck Exp $
 * $Source: /usr5/legends/jck/xb/master/xboing/presents.c,v $
 * $Revision: 1.1.1.1 $
 * $Date: 1994/12/16 01:36:48 $
 *
 * $Log: presents.c,v $
 * Revision 1.1.1.1  1994/12/16  01:36:48  jck
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
#include "main.h"
#include "init.h"
#include "intro.h"
#include "highscore.h"
#include "audio.h"
#include "stage.h"
#include "mess.h"
#include "sfx.h"
#include "version.h"
#include "../patchlevel.h"

#include "bitmaps/presents/flag.xpm"
#include "bitmaps/presents/earth.xpm"
#include "bitmaps/presents/titleX.xpm"
#include "bitmaps/presents/titleB.xpm"
#include "bitmaps/presents/titleO.xpm"
#include "bitmaps/presents/titleI.xpm"
#include "bitmaps/presents/titleN.xpm"
#include "bitmaps/presents/titleG.xpm"
#include "bitmaps/presents/justin.xpm"
#include "bitmaps/presents/kibell.xpm"
#include "bitmaps/presents/presents.xpm"

#include "presents.h"

/*
 *  Internal macro definitions:
 */

#define GAP 10

/*
 *  Internal type declarations:
 */

void SetPresentWait(int newMode, int waitFrame);
void DoPresentWait(void);
static void DoSparkle(Display *display, Window window);

/*
 *  Internal variable declarations:
 */

static int nextFrame = 0;
static int endFrame = 0;
static int startFrame = 0;
enum PresentStates PresentState;
static Pixmap flagPixmap, flagPixmapM;
Pixmap earthPixmap, earthPixmapM;
static Pixmap titlePixmap[6], titlePixmapM[6];
static Pixmap justin, justinM, kibell, kibellM, presents, presentsM;
static int waitingFrame, waitMode;


/**
 * @brief Initializes all bitmaps for the presentation.
 * 
 * This function loads various pixmap data for elements used in the presentation,
 * like flags, earth, and title bitmaps. It also handles errors if pixmaps
 * cannot be created.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where bitmaps are displayed.
 * @param colormap The colormap used for creating pixmaps.
 */
void SetUpPresents(Display *display, Window window, Colormap colormap)
{
	XpmAttributes   attributes;
	int             XpmErrorStatus;

    attributes.valuemask = XpmColormap;
	attributes.colormap = colormap;

	XpmErrorStatus = XpmCreatePixmapFromData(display, window, flag_xpm,
		&flagPixmap, &flagPixmapM, &attributes);
	HandleXPMError(display, XpmErrorStatus, "InitialisePresent(flag)");

	XpmErrorStatus = XpmCreatePixmapFromData(display, window, titleX_xpm,
		&titlePixmap[0], &titlePixmapM[0], &attributes);
	HandleXPMError(display, XpmErrorStatus, "InitialisePresent(titleX)");

	XpmErrorStatus = XpmCreatePixmapFromData(display, window, titleB_xpm,
		&titlePixmap[1], &titlePixmapM[1], &attributes);
	HandleXPMError(display, XpmErrorStatus, "InitialisePresent(titleB)");

	XpmErrorStatus = XpmCreatePixmapFromData(display, window, titleO_xpm,
		&titlePixmap[2], &titlePixmapM[2], &attributes);
	HandleXPMError(display, XpmErrorStatus, "InitialisePresent(titleO)");

	XpmErrorStatus = XpmCreatePixmapFromData(display, window, titleI_xpm,
		&titlePixmap[3], &titlePixmapM[3], &attributes);
	HandleXPMError(display, XpmErrorStatus, "InitialisePresent(titleI)");

	XpmErrorStatus = XpmCreatePixmapFromData(display, window, titleN_xpm,
		&titlePixmap[4], &titlePixmapM[4], &attributes);
	HandleXPMError(display, XpmErrorStatus, "InitialisePresent(titleN)");

	XpmErrorStatus = XpmCreatePixmapFromData(display, window, titleG_xpm,
		&titlePixmap[5], &titlePixmapM[5], &attributes);
	HandleXPMError(display, XpmErrorStatus, "InitialisePresent(titleG)");

	/* Justin kibell presents */

	XpmErrorStatus = XpmCreatePixmapFromData(display, window, justin_xpm,
		&justin, &justinM, &attributes);
	HandleXPMError(display, XpmErrorStatus, "InitialisePresent(justin)");

	XpmErrorStatus = XpmCreatePixmapFromData(display, window, kibell_xpm,
		&kibell, &kibellM, &attributes);
	HandleXPMError(display, XpmErrorStatus, "InitialisePresent(kibell)");

	XpmErrorStatus = XpmCreatePixmapFromData(display, window, presents_xpm,
		&presents, &presentsM, &attributes);
	HandleXPMError(display, XpmErrorStatus, "InitialisePresent(presents)");

	/* Create the earth pixmap */

	XpmErrorStatus = XpmCreatePixmapFromData(display, window, earth_xpm,
		&earthPixmap, &earthPixmapM, &attributes);
	HandleXPMError(display, XpmErrorStatus, "InitialisePresent(earth)");

    /* Free the xpm pixmap attributes */
	XpmFreeAttributes(&attributes);

	/* Setup intro to initial state */
	ResetPresents();
}


/**
 * @brief Renders a specific letter as part of the title display.
 * 
 * Draws one of six letters that spell out a title on the screen.
 * Each letter has unique position, dimensions, and pixmap data.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where letters are drawn.
 * @param letter The index of the letter to draw (0 to 5).
 * @param x The x-coordinate of the letter position.
 * @param y The y-coordinate of the letter position.
 */
static void DrawLetter(Display *display, Window window, int letter, 
	int x, int y)
{
	switch(letter)
	{
		case 0:		/* X */
			RenderShape(display, window, titlePixmap[0], titlePixmapM[0],
				x, y, 71, 74, False);
			break;

		case 1:		/* B */
			RenderShape(display, window, titlePixmap[1], titlePixmapM[1],
				x, y, 73, 74, False);
			break;

		case 2:		/* O */
			RenderShape(display, window, titlePixmap[2], titlePixmapM[2],
				x, y, 83, 74, False);
			break;

		case 3:		/* I */
			RenderShape(display, window, titlePixmap[3], titlePixmapM[3],
				x, y, 41, 74, False);
			break;

		case 4:		/* N */
			RenderShape(display, window, titlePixmap[4], titlePixmapM[4],
				x, y, 85, 74, False);
			break;

		case 5:		/* G */
			RenderShape(display, window, titlePixmap[5], titlePixmapM[5],
				x, y, 88, 74, False);
			break;

		default:
			ErrorMessage("Error: In default for DrawLetter()");
	}
}


/**
 * @brief Draws the flag and introductory text in the presentation.
 * 
 * Displays a flag bitmap and introductory text in the central window area.
 * Also displays the Earth image with a copyright message.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the presentation is shown.
 */
void DoPresentFlag(Display *display, Window window)
{
	char string[80];
	int y, x;
	XPoint pt[4];
	int z;

	DEBUG("Drawing earth in presents mode.")

	x = ((MAIN_WIDTH + PLAY_WIDTH) / 2) - 35;

	/* Draw the flag bitmap */
	RenderShape(display, window, flagPixmap, flagPixmapM,
		x, 15, 71, 40, True);
	DrawShadowCentredText(display, window, textFont, 
		"Made in Australia", 
		65, white, PLAY_WIDTH + MAIN_WIDTH);

	x = ((MAIN_WIDTH + PLAY_WIDTH) / 2) - 200;
	RenderShape(display, window, earthPixmap, earthPixmapM,
		x, 93, 400, 400, False);

	y = MAIN_HEIGHT + PLAY_HEIGHT - 20;

	/* Construct a copyright message leaving space for the copyright circle */
	sprintf(string, "  %s", c_string); 
	string[0] = 0xa9;  /* Copyright circle */
	DrawShadowCentredText(display, window, copyFont, string, y, white, 
		PLAY_WIDTH + MAIN_WIDTH);

	if (noSound == False) playSoundFile("intro", 40);

#ifdef testing
	for (z = 0; z < 700; z+=10)
	{
		pt[0].x = 0;
		pt[0].y = 50;
		pt[1].x = 100;
		pt[1].y = z;
		pt[2].x = 200;
		pt[2].y = z;
		pt[3].x = 300;
		pt[3].y = 50;
		Draw4PointCurve(display, window, pt, 100);
	}
#endif

	SetPresentWait(PRESENT_TEXT1, frame + 800);
}


/**
 * @brief Draws a specified introductory text image in the presentation.
 * 
 * Displays one of several introductory text images, each at a specific position
 * on the screen. Uses a bitmap to represent each text image.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the text is displayed.
 */
static void DoText1(Display *display, Window window)
{
	int x, y;

	DEBUG("Drawing Justin in presents mode.")

	x = ((MAIN_WIDTH + PLAY_WIDTH) / 2) - 142;
	y = 530;

	/* Render the Justin bitmap */
	RenderShape(display, window, justin, justinM,
		x, y, 285, 44, True);

	SetPresentWait(PRESENT_TEXT2, frame + 300);
}


/**
 * @brief Draws a specified introductory text image in the presentation.
 * 
 * Displays one of several introductory text images, each at a specific position
 * on the screen. Uses a bitmap to represent each text image.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the text is displayed.
 */
static void DoText2(Display *display, Window window)
{
	int x, y;

	DEBUG("Drawing kibell in presents mode.")

	x = ((MAIN_WIDTH + PLAY_WIDTH) / 2) - 130;
	y = 530 + 44 + 10;

	/* Render the Justin bitmap */
	RenderShape(display, window, kibell, kibellM,
		x, y, 260, 40, True);

	SetPresentWait(PRESENT_TEXT3, frame + 500);
}


/**
 * @brief Draws a specified introductory text image in the presentation.
 * 
 * Displays one of several introductory text images, each at a specific position
 * on the screen. Uses a bitmap to represent each text image.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the text is displayed.
 */
static void DoText3(Display *display, Window window)
{
	int x, y;

	DEBUG("Drawing presents in presents mode.")

	FadeAwayArea(display, window, 0, 530, PLAY_WIDTH + MAIN_WIDTH, 99);

	x = ((MAIN_WIDTH + PLAY_WIDTH) / 2) - 205;
	y = 530 + 44 + 10 - 22;

	/* Render the Justin bitmap */
	RenderShape(display, window, presents, presentsM,
		x, y, 410, 44, True);

	SetPresentWait(PRESENT_TEXT_CLEAR, frame + 750);
}


/**
 * @brief Clears the introductory text from the presentation window.
 * 
 * Removes any introductory text displayed in the presentation by fading it away.
 * Prepares the screen for the next display phase.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where text clearing is done.
 */
static void DoTextClear(Display *display, Window window)
{
	int x, y;

	DEBUG("Clearing word presents in presents mode.")

	x = ((MAIN_WIDTH + PLAY_WIDTH) / 2) - 205;
	y = 530 + 44 + 10 - 22;

	FadeAwayArea(display, window, x, y, 410, 44);

	SetPresentWait(PRESENT_LETTERS, frame + 10);
}

/* The distances for the gap inbetwen blocks */
static int dists[] =
{
	71, 73, 83, 41, 85, 88
};


/**
 * @brief Sequentially draws the letters of the title on the screen.
 * 
 * Displays each letter of the title one at a time across the screen.
 * Each letter plays a sound when displayed.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the letters are drawn.
 */
static void DoLetters(Display *display, Window window)
{
	static int i = 0;
	static int x = 40;
	static int y = 220;

	if (i < 6)
	{
		if (noSound == False) playSoundFile("stamp", 90);

		/* Draw the letters of xboing one at a time across screen */
		DrawLetter(display, window, i, x, y);
		x += 10 + dists[i];

		SetPresentWait(PRESENT_LETTERS, frame + 300);
	}
	else
	{
		if (noSound == False) playSoundFile("stamp", 90);

		y += 110;
		x = ((PLAY_WIDTH + MAIN_WIDTH) / 2) - (dists[3]); 
		DrawLetter(display, window, 3, x, y);
		x += dists[3];
		DrawLetter(display, window, 3, x, y);

		SetPresentWait(PRESENT_SHINE, frame + 200);
	}

	i++;
}


/**
 * @brief Creates a sparkle effect in the presentation.
 * 
 * Draws a series of images at a specific location on the screen to simulate
 * a sparkling effect.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the sparkle effect is drawn.
 */
static void DoSparkle(Display *display, Window window)
{
    static Pixmap store;
    static int in = 0;
	static int startFrame;
	static int x, y;


    if (!store)
    {
        store = XCreatePixmap(display, window, 20, 20,
            DefaultDepth(display, XDefaultScreen(display)));

        startFrame = frame;
		x = MAIN_WIDTH + PLAY_WIDTH - 50;
		y = 212;
		if (noSound == False) playSoundFile("ping", 70);

		DEBUG("start the sparkle on xboing.")
    }

    if (in == 0)
        XCopyArea(display, window, store, gc, x, y, 20, 20, 0, 0);

    if (frame == startFrame)
    {
        RenderShape(display, window, stars[in], starsM[in],
            x, y, 20, 20, False);

        in++;
        startFrame = frame + 35;

        if (in == 11)
        {
            XCopyArea(display, store, window, gc, 0, 0, 20, 20, x, y);
			SetPresentWait(PRESENT_SPECIAL_TEXT1, frame + 500);
        }
    }
}


/**
 * @brief Displays a special message in the presentation sequence.
 * 
 * Shows one of several special message text strings with typing effect.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the message is displayed.
 */
static void DoSpecialText1(Display *display, Window window)
{
	static int first = True;
	static int i;
	static int len;
	static int x, y;
	static char wisdom[100];

	if (first)
	{
		/* Do this section on the first entry */

		if (GetNickName() != NULL)
			sprintf(wisdom, "Welcome %s, prepare for battle.", 
				GetNickName());
		else
			sprintf(wisdom, "Welcome %s, prepare for battle.", 
				getUsersFullName());

		i = 1;
		y = 550;
		len = strlen(wisdom);
		x = ((PLAY_WIDTH + MAIN_WIDTH) / 2) - 
			(XTextWidth(dataFont, wisdom, len) / 2);
		nextFrame = frame + 10;
		first = False;
	}

	if (frame >= nextFrame)
	{
		if (noSound == False) playSoundFile("key", 60);
		DrawText(display, window, x, y, dataFont, red, wisdom, i);

		nextFrame = frame + 30;

		i++;
		if (i > len)
			SetPresentWait(PRESENT_SPECIAL_TEXT2, frame + 700);
	}
}


/**
 * @brief Displays a special message in the presentation sequence.
 * 
 * Shows one of several special message text strings with typing effect.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the message is displayed.
 */
static void DoSpecialText2(Display *display, Window window)
{
	static int first = True;
	static int i;
	static int len;
	static int x, y;
	static char wisdom2[100];

	if (first)
	{
		/* Do this section on the first entry */

		strcpy(wisdom2, 
		  "The future of the planet Earth is in your hands!");
		i = 1;
		y = 550 + dataFont->ascent + dataFont->descent + 5;
		len = strlen(wisdom2);
		x = ((PLAY_WIDTH + MAIN_WIDTH) / 2) - 
			(XTextWidth(dataFont, wisdom2, len) / 2);
		nextFrame = frame + 10;
		first = False;
	}

	if (frame >= nextFrame)
	{
		if (noSound == False) playSoundFile("key", 60);
		DrawText(display, window, x, y, dataFont, red, wisdom2, i);

		nextFrame = frame + 30;

		i++;
		if (i > len)
			SetPresentWait(PRESENT_SPECIAL_TEXT3, frame + 700);
	}
}


/**
 * @brief Displays a special message in the presentation sequence.
 * 
 * Shows one of several special message text strings with typing effect.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the message is displayed.
 */
static void DoSpecialText3(Display *display, Window window)
{
	static int first = True;
	static int i;
	static int len;
	static int x, y;
	static char wisdom3[100];

	if (first)
	{
		/* Do this section on the first entry */

		strcpy(wisdom3, 
		  "More instructions will follow within game zone - out.");
		i = 1;
		y = 550 + (dataFont->ascent + dataFont->descent + 5) * 2;
		len = strlen(wisdom3);
		x = ((PLAY_WIDTH + MAIN_WIDTH) / 2) - 
			(XTextWidth(dataFont, wisdom3, len) / 2);
		nextFrame = frame + 10;
		first = False;
	}

	if (frame >= nextFrame)
	{
		if (noSound == False) playSoundFile("key", 60);
		DrawText(display, window, x, y, dataFont, red, wisdom3, i);

		nextFrame = frame + 30;

		i++;
		if (i > len)
			SetPresentWait(PRESENT_CLEAR, frame + 800);
	}
}


/**
 * @brief Gradually clears the presentation screen.
 * 
 * Clears the entire screen gradually by wiping down the screen in rows.
 * Called at the end of the presentation to reset the display.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window to be cleared.
 */
static void DoClear(Display *display, Window window)
{
	static int yt, yb, t;
	static int first = True;

	if (first == True)
	{
		/* Do this section on the first entry */
		yt = 0;
		yb = PLAY_HEIGHT + MAIN_HEIGHT - 10;
		t = (PLAY_HEIGHT + MAIN_HEIGHT) / 2;
		first = False;
		nextFrame = frame;

    	if (noSound == False) playSoundFile("whoosh", 70);

		DEBUG("Clearing presents screen.")
	}

	if (frame >= nextFrame)
	{
		/* Clear and draw lines */
		XClearArea(display, window, 0, yt, PLAY_WIDTH + MAIN_WIDTH, 10, False);
		yt += 10;
		DrawLine(display, window, 2, yt, PLAY_WIDTH + MAIN_WIDTH-2, yt, 
			red, 1);

		XClearArea(display, window, 0, yb, PLAY_WIDTH + MAIN_WIDTH, 10, False);
		DrawLine(display, window, 2, yb-1, PLAY_WIDTH + MAIN_WIDTH-2, yb-1, 
			red, 1);
		yb -= 10;

		if (yt > ((PLAY_HEIGHT + MAIN_HEIGHT) / 2))
			SetPresentWait(PRESENT_FINISH, frame + 20);

		nextFrame = frame + 20;
	}
}


/**
 * @brief Finishes the presentation early.
 * 
 * Sets the state to finish mode to skip the remaining presentation steps.
 * Triggered when the user presses a specific key.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the presentation is shown.
 */
void QuickFinish(Display *display, Window window)
{
	DEBUG("finishing in presents mode.")

	/* User has pressed space so finish early */
	SetPresentWait(PRESENT_FINISH, frame);
}


/**
 * @brief Completes and cleans up the presentation.
 * 
 * Frees up resources used in the presentation, clears the screen,
 * and transitions to the game intro mode.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the presentation was shown.
 */
static void DoFinish(Display *display, Window window)
{
	/* Free all the pixmaps used in this intro */
	FreeAllPresents(display);

	/* Erase all stuff in window */
	XClearWindow(display, mainWindow);

	DEBUG("mapping all game windows.")

	/* Map all the windows */
	MapAllWindows(display);

	/* Now jump into the intro mode */
	ResetIntroduction();
	mode = MODE_INTRO;
}


/**
 * @brief Manages the presentation sequence based on the current state.
 * 
 * Controls the flow of the presentation by selecting the appropriate
 * function for the current state in the `PresentState` enumeration.
 * 
 * @param display Pointer to the X11 display connection.
 * @param window The X11 window where the presentation is shown.
 */
void Presents(Display *display, Window window)
{
	switch (PresentState)
	{
		case PRESENT_FLAG:
			DoPresentFlag(display, window);
			break;

		case PRESENT_TEXT1:
			DoText1(display, window);
			break;

		case PRESENT_TEXT2:
			DoText2(display, window);
			break;

		case PRESENT_TEXT3:
			DoText3(display, window);
			break;

		case PRESENT_TEXT_CLEAR:
			DoTextClear(display, window);
			break;

		case PRESENT_LETTERS:
			DoLetters(display, window);
			break;

		case PRESENT_SPECIAL_TEXT1:
			DoSpecialText1(display, window);
			break;

		case PRESENT_SPECIAL_TEXT2:
			DoSpecialText2(display, window);
			break;

		case PRESENT_SPECIAL_TEXT3:
			DoSpecialText3(display, window);
			break;

		case PRESENT_CLEAR:
			DoClear(display, window);
			break;

		case PRESENT_SHINE:
			DoSparkle(display, window);
			break;

		case PRESENT_FINISH:
			DoFinish(display, window);
			break;

		case PRESENT_WAIT:
			DoPresentWait();
			break;

		default:
			break;
	}
}

void RedrawPresents(Display *display, Window window)
{
}


/**
 * @brief Frees specific pixmap resources from the presentation.
 * 
 * Releases the large earth pixmap and its mask to free up memory.
 * 
 * @param display Pointer to the X11 display connection.
 */
void FreeSomePresents(Display *display)
{
	/* Free the large earth pixmap and it's mask */
    if (earthPixmap)	XFreePixmap(display, earthPixmap);         
	if (earthPixmapM)	XFreePixmap(display, earthPixmapM);
}


/**
 * @brief Frees all pixmap resources from the presentation.
 * 
 * Releases all pixmaps and their masks used in the presentation.
 * 
 * @param display Pointer to the X11 display connection.
 */
void FreeAllPresents(Display *display)
{
	int i;

	/* Free the flag pixmaps */
    if (flagPixmap)		XFreePixmap(display, flagPixmap);         
	if (flagPixmapM)	XFreePixmap(display, flagPixmapM);

	/* Free the text pixmaps for justin, kibell and presents */
    if (justin)		XFreePixmap(display, justin);         
	if (justinM)	XFreePixmap(display, justinM);

    if (kibell)		XFreePixmap(display, kibell);         
	if (kibellM)	XFreePixmap(display, kibellM);

    if (presents)	XFreePixmap(display, presents);         
	if (presentsM)	XFreePixmap(display, presentsM);

	/* Free the pixmaps for the letters of the work xboing */
	for (i = 0; i < 6; i++)
	{
		/* Free each of the letters in XBOING */
    	if (titlePixmap[i])		XFreePixmap(display, titlePixmap[i]);         
		if (titlePixmapM[i])	XFreePixmap(display, titlePixmapM[i]);
	}
}


/**
 * @brief Resets the presentation to its initial state.
 * 
 * Resets the `PresentState` and frame counters to start the presentation
 * from the beginning.
 */
void ResetPresents(void)
{
	DEBUG("Reset presents mode.")

	PresentState = PRESENT_FLAG;
	nextFrame = frame + 100;
	startFrame = frame + 10;
	endFrame = frame + 3000;
	SetGameSpeed(FAST_SPEED);
}


/**
 * @brief Sets the waiting mode and frame for the presentation.
 * 
 * This function configures the waiting period between frames during the
 * introduction sequence based on the specified mode and frame.
 *
 * @param newMode Integer representing the new wait mode to set.
 * @param waitFrame Integer specifying the frame at which to stop waiting.
 */

void SetPresentWait(int newMode, int waitFrame)
{
	waitingFrame = waitFrame;
	waitMode = newMode;
	PresentState = PRESENT_WAIT;
}


/**
 * @brief Manages the waiting state in the introduction presentation.
 * 
 * This function is called while the presentation is in a waiting mode.
 * It handles tasks during waiting, like transitioning modes after
 * the specified frame count is reached.
 */
void DoPresentWait(void)
{
	if (frame == waitingFrame)
		PresentState = waitMode;
}
