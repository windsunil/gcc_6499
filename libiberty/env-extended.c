/* Extended getenv implementation for handling very long environment variables.
   Copyright (C) 1992-2025 Free Software Foundation, Inc.
   Written by Fred Fish @ Cygnus Support

This file is part of the libiberty library.
Libiberty is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

Libiberty is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with libiberty; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
Boston, MA 02110-1301, USA.  */

/* env-extended.cc - Implementation for extended getenv */
#include "config.h"
#include "ansidecl.h"
#include "libiberty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getenv_extended (const char* var_name)
{
  int file_size;
  char* buf = NULL;
  const char* prefix = "@";
  size_t prefix_len = strlen (prefix);

  char* string = getenv (var_name);
  if (string == NULL)
    {
      return NULL;
    }

  if (strncmp (string, prefix, prefix_len) == 0)
    {
      FILE *fptr;
      char *new_string = xstrdup (string + prefix_len);

      fptr = fopen (new_string, "r");
      fseek (fptr, 0, SEEK_END);
      file_size = ftell (fptr);
      rewind (fptr);
      buf = (char *) xmalloc (file_size + 1);

      fread (buf, 1, file_size, fptr);
      buf[file_size] = '\0';

      free (new_string);
      fclose (fptr);
      return buf;
    }

  // Return the environment variable as-is if no file is referenced
  return string;
}
