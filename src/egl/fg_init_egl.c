/*
 * fg_init_egl.c
 *
 * Various freeglut initialization functions.
 *
 * Copyright (C) 2012  Sylvain Beucler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"
#ifdef VITA
#include <pib.h>
#endif

/*
 * A call to this function should initialize all the display stuff...
 */
void fghPlatformInitializeEGL()
{
#ifdef VITA
  pibInit(PIB_SHACCCG);
#endif
  /* CreateDisplay */
  /* Using EGL_DEFAULT_DISPLAY, or a specific native display */
#ifdef FREEGLUT_WAYLAND
  fgDisplay.pDisplay.egl.Display = eglGetDisplay(
              (EGLNativeDisplayType)fgDisplay.pDisplay.display);
#else
  EGLNativeDisplayType nativeDisplay = EGL_DEFAULT_DISPLAY;
  fgDisplay.pDisplay.egl.Display = eglGetDisplay(nativeDisplay);
#endif

  FREEGLUT_INTERNAL_ERROR_EXIT(fgDisplay.pDisplay.egl.Display != EGL_NO_DISPLAY,
			       "No display available", "fgPlatformInitialize");
  if (eglInitialize(fgDisplay.pDisplay.egl.Display, &fgDisplay.pDisplay.egl.MajorVersion, &fgDisplay.pDisplay.egl.MinorVersion) != EGL_TRUE)
    fgError("eglInitialize: error %x\n", eglGetError());

# ifdef GL_VERSION_1_1  /* or later */
  eglBindAPI(EGL_OPENGL_API);
# else
  eglBindAPI(EGL_OPENGL_ES_API);
# endif

  /* fgDisplay.ScreenWidth = ...; */
  /* fgDisplay.ScreenHeight = ...; */
  /* fgDisplay.ScreenWidthMM = ...; */
  /* fgDisplay.ScreenHeightMM = ...; */
}

void fghPlatformCloseDisplayEGL()
{
  if (fgDisplay.pDisplay.egl.Display != EGL_NO_DISPLAY) {
    eglTerminate(fgDisplay.pDisplay.egl.Display);
    fgDisplay.pDisplay.egl.Display = EGL_NO_DISPLAY;
    fgDisplay.pDisplay.egl.MajorVersion = 0;
    fgDisplay.pDisplay.egl.MinorVersion = 0;
  }
}

/**
 * Destroy a menu context
 */
void fgPlatformDestroyContext ( SFG_PlatformDisplay pDisplay, SFG_WindowContextType MContext )
{
  if (MContext != EGL_NO_CONTEXT)
    eglDestroyContext(pDisplay.egl.Display, MContext);
}
