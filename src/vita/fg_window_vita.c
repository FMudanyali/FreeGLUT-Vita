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

void fgPlatformOpenWindow( SFG_Window* window, const char* title,
                           GLboolean positionUse, int x, int y,
                           GLboolean sizeUse, int w, int h,
                           GLboolean gameMode, GLboolean isSubWindow )
{
  /* TODO: only one full-screen window possible? */
  if (fgDisplay.pDisplay.single_native_window != NULL) {
    fgWarning("You can't have more than one window on Vita");
    return;
  }
  fgDisplay.pDisplay.single_native_window = window;
  window->Window.Handle = fgDisplay.pDisplay.single_native_window;
  window->State.WorkMask |= GLUT_INIT_WORK;

  /* Create context */
  fghChooseConfig(&window->Window.pContext.egl.Config);
  window->Window.Context = fghCreateNewContextEGL(window);

  EGLDisplay display = fgDisplay.pDisplay.egl.Display;
  EGLint vid;
  eglGetConfigAttrib(display, window->Window.pContext.egl.Config, EGL_NATIVE_VISUAL_ID, &vid);
  fghPlatformOpenWindowEGL(window);

  /* Bind context to the current thread if it's lost */
  if (eglGetCurrentContext() == EGL_NO_CONTEXT &&
      eglMakeCurrent(fgDisplay.pDisplay.egl.Display,
             window->Window.pContext.egl.Surface,
             window->Window.pContext.egl.Surface,
             window->Window.Context) == EGL_FALSE)
    fgError("eglMakeCurrent: err=%x\n", eglGetError());
  window->State.Visible = GL_TRUE;
}

void fgPlatformReshapeWindow ( SFG_Window *window, int width, int height )
{
  fprintf(stderr, "fgPlatformReshapeWindow: STUB\n");
}

/*
 * Closes a window, destroying the frame and OpenGL context
 */
void fgPlatformCloseWindow( SFG_Window* window )
{
  fghPlatformCloseWindowEGL(window);
}

/*
 * This function makes the specified window visible
 */
void fgPlatformShowWindow( void )
{
  fprintf(stderr, "fgPlatformShowWindow: STUB\n");
}

/*
 * This function hides the specified window
 */
void fgPlatformHideWindow( SFG_Window *window )
{
  fprintf(stderr, "fgPlatformHideWindow: STUB\n");
}

/*
 * Iconify the specified window (top-level windows only)
 */
void fgPlatformIconifyWindow( SFG_Window *window )
{
  fprintf(stderr, "fgPlatformGlutIconifyWindow: STUB\n");
}

/*
 * Set the current window's title
 */
void fgPlatformGlutSetWindowTitle( const char* title )
{
  fprintf(stderr, "fgPlatformGlutSetWindowTitle: STUB\n");
}

/*
 * Set the current window's iconified title
 */
void fgPlatformGlutSetIconTitle( const char* title )
{
  fprintf(stderr, "fgPlatformGlutSetIconTitle: STUB\n");}

/*
 * Change the specified window's position
 */
void fgPlatformPositionWindow( SFG_Window *window, int x, int y )
{
  fprintf(stderr, "fgPlatformPositionWindow: STUB\n");
}

/*
 * Lowers the specified window (by Z order change)
 */
void fgPlatformPushWindow( SFG_Window *window )
{
  fprintf(stderr, "fgPlatformPushWindow: STUB\n");
}

/*
 * Raises the specified window (by Z order change)
 */
void fgPlatformPopWindow( SFG_Window *window )
{
  fprintf(stderr, "fgPlatformPopWindow: STUB\n");
}

/*
 * Toggle the window's full screen state.
 */
void fgPlatformFullScreenToggle( SFG_Window *win )
{
  fprintf(stderr, "fgPlatformFullScreenToggle: STUB\n");
}