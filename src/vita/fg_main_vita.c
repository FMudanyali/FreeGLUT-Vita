/*****************************************************************************
 *
 *  Copyright (c) 2020 by Furkan Mudanyali <fmudanyali@icloud.com>
 *
 *  This file is part of Freeglut-Vita
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

#include <GL/freeglut.h>
#include "fg_internal.h"
#include "egl/fg_window_egl.h"
#include <psp2/kernel/threadmgr.h>
#include <psp2/ctrl.h>

extern void fghOnReshapeNotify(SFG_Window *window, int width, int height, GLboolean forceNotify);
extern void fghOnPositionNotify(SFG_Window *window, int x, int y, GLboolean forceNotify);
extern void fgPlatformFullScreenToggle( SFG_Window *win );
extern void fgPlatformPositionWindow( SFG_Window *window, int x, int y );
extern void fgPlatformReshapeWindow ( SFG_Window *window, int width, int height );
extern void fgPlatformPushWindow( SFG_Window *window );
extern void fgPlatformPopWindow( SFG_Window *window );
extern void fgPlatformHideWindow( SFG_Window *window );
extern void fgPlatformIconifyWindow( SFG_Window *window );
extern void fgPlatformShowWindow( SFG_Window *window );
/* Function to read key press, needs work so it can
detect multiple presses. */
static unsigned char read_key() {
  SceCtrlData ctrl;
  sceCtrlPeekBufferPositive(0, &ctrl, 1);
  switch(ctrl.buttons){
    case SCE_CTRL_CROSS: return GLUT_KEY_F1;
    case SCE_CTRL_SQUARE: return GLUT_KEY_F2;
    case SCE_CTRL_CIRCLE: return GLUT_KEY_F3;
    case SCE_CTRL_TRIANGLE: return GLUT_KEY_F4;
    case SCE_CTRL_L1: return GLUT_KEY_F5;
    case SCE_CTRL_R1: return GLUT_KEY_F6;
    case SCE_CTRL_L2: return GLUT_KEY_F7;
    case SCE_CTRL_R2: return GLUT_KEY_F8;
    case SCE_CTRL_L3: return GLUT_KEY_F9;
    case SCE_CTRL_R3: return GLUT_KEY_F10;
    case SCE_CTRL_SELECT: return GLUT_KEY_F11;
    case SCE_CTRL_START: return GLUT_KEY_F12;
    case SCE_CTRL_UP: return GLUT_KEY_UP;
    case SCE_CTRL_DOWN: return GLUT_KEY_DOWN;
    case SCE_CTRL_LEFT: return GLUT_KEY_LEFT;
    case SCE_CTRL_RIGHT: return GLUT_KEY_RIGHT;
    default: return 0;
  }
}
/* This function is called every frame or something. */
void fgPlatformProcessSingleEvent ( void )
{
  SFG_Window* window = fgStructure.CurrentWindow;
  if (window != NULL && window->Window.Handle != NULL) {
    int32_t width = 960;
    int32_t height = 544;
    fghOnReshapeNotify(window,width,height,GL_FALSE);
  }
  unsigned char keypress = read_key();
  if (keypress!=0)
    INVOKE_WCB(*window, Special, (keypress, window->State.MouseX, window->State.MouseY));
}

void fgPlatformMainLoopPreliminaryWork ( void )
{
//
}

unsigned long fgPlatformSystemTime ( void )
{
  struct timeval now;
  gettimeofday( &now, NULL );
  return now.tv_usec/1000 + now.tv_sec*1000;
}

void fgPlatformSleepForEvents( long msec )
{
  sceKernelDelayThread(msec);
}

void fgPlatformOpenWindow( SFG_Window* window, const char* title,
                           GLboolean positionUse, int x, int y,
                           GLboolean sizeUse, int w, int h,
                           GLboolean gameMode, GLboolean isSubWindow );

/* deal with work list items */
void fgPlatformInitWork(SFG_Window* window)
{
    /* notify windowStatus/visibility */
    INVOKE_WCB( *window, WindowStatus, ( GLUT_FULLY_RETAINED ) );

    /* Position callback, always at 0,0 */
    fghOnPositionNotify(window, 0, 0, GL_TRUE);
}

void fgPlatformPosResZordWork(SFG_Window* window, unsigned int workMask)
{
    if (workMask & GLUT_FULL_SCREEN_WORK)
        fgPlatformFullScreenToggle( window );
    if (workMask & GLUT_POSITION_WORK)
        fgPlatformPositionWindow( window, window->State.DesiredXpos, window->State.DesiredYpos );
    if (workMask & GLUT_SIZE_WORK)
        fgPlatformReshapeWindow ( window, window->State.DesiredWidth, window->State.DesiredHeight );
    if (workMask & GLUT_ZORDER_WORK)
    {
        if (window->State.DesiredZOrder < 0)
            fgPlatformPushWindow( window );
        else
            fgPlatformPopWindow( window );
    }
}

void fgPlatformVisibilityWork(SFG_Window* window)
{
    /* Visibility status of window should get updated in the window message handlers
     * For now, none of these functions called below do anything, so don't worry
     * about it
     */
    SFG_Window *win = window;
    switch (window->State.DesiredVisibility)
    {
    case DesireHiddenState:
        fgPlatformHideWindow( window );
        break;
    case DesireIconicState:
        /* Call on top-level window */
        while (win->Parent)
            win = win->Parent;
        fgPlatformIconifyWindow( win );
        break;
    case DesireNormalState:
        fgPlatformShowWindow( window );
        break;
    }
}