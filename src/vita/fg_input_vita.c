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
typedef struct _serialport SERIALPORT;

void fgPlatformRegisterDialDevice ( const char *dial_device ) {
    fgWarning("GLUT_HAS_DIAL_AND_BUTTON_BOX: not implemented");
}
SERIALPORT *fg_serial_open ( const char *device ) { return NULL; }
void fg_serial_close(SERIALPORT *port) {}
int fg_serial_getchar(SERIALPORT *port) { return EOF; }
int fg_serial_putchar(SERIALPORT *port, unsigned char ch) { return 0; }
void fg_serial_flush ( SERIALPORT *port ) {}
