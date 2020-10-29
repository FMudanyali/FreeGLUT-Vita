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
#include "egl/fg_state_egl.h"
#include "egl/fg_structure_egl.h"

int fgPlatformGlutDeviceGet ( GLenum eWhat )
{
    switch( eWhat )
    {
    case GLUT_HAS_KEYBOARD:
        return 1;

    case GLUT_HAS_MOUSE:
        return 1 ;

    case GLUT_NUM_MOUSE_BUTTONS:
        return 1;

    default:
        fgWarning( "glutDeviceGet(): missing enum handle %d", eWhat );
        break;
    }

    /* And now -- the failure. */
    return -1;
}

int fgPlatformGlutGet ( GLenum eWhat )
{
  switch (eWhat) {
  /* One full-screen window only */
  case GLUT_WINDOW_X:
  case GLUT_WINDOW_Y:
  case GLUT_WINDOW_BORDER_WIDTH:
  case GLUT_WINDOW_HEADER_HEIGHT:
      return 0;

  case GLUT_WINDOW_WIDTH:
  case GLUT_WINDOW_HEIGHT:
    {
      if ( fgStructure.CurrentWindow == NULL )
	return 0;
      int32_t width = 960;
      int32_t height = 544;
      switch ( eWhat )
	{
	case GLUT_WINDOW_WIDTH:
	  return width;
	case GLUT_WINDOW_HEIGHT:
	  return height;
	}
    }

  case GLUT_WINDOW_COLORMAP_SIZE:
      return 0;
  
  default:
    return fghPlatformGlutGetEGL(eWhat);
  }
  return -1;
}

void fgPlatformCreateWindow ( SFG_Window *window )
{
  fghPlatformCreateWindowEGL(window);
}