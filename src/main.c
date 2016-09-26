/*
SDLPoP, a port/conversion of the DOS game Prince of Persia.
Copyright (C) 2013-2015  Dávid Nagy

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

The authors of this program may be contacted at http://forum.princed.org
*/

#ifdef PSP2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <psp2/io/stat.h>
#include <psp2shell.h>

int _newlib_heap_size_user = 192 * 1024 * 1024;

#define printf psp2shell_print

FILE *_fopen(const char *filename, const char *mode) {
	char path[512];
	memset(path, 0, 512);
	
	if(strcmp(filename, "SDLPoP.ini") == 0) {
		sprintf(path, "ux0:/data/vpop/%s", filename);
	} else {
		sprintf(path, "app0:/%s", filename);
	}
	return fopen(path, mode);
}

int _fprintf(FILE *stream, const char *format, ...) {
	char *s = malloc(1024);
	va_list args;
    va_start(args, format);
    int size = vsnprintf(s, 1024, format, args);
    printf(s);
    va_end(args);
    free(s);
    return size;
}

#endif

#include "common.h"

int main(int argc, char *argv[])
{
#ifdef PSP2
	sceIoMkdir("ux0:/data/vpop", 0777);
	psp2shell_init(3333);
#endif
	g_argc = argc;
	g_argv = argv;
	pop_main();
	
#ifdef PSP2
	psp2shell_exit();
#endif
	return 0;
}
