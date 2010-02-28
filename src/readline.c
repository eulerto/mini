/*
 * readline.c
 * This file is part of mini, a library to parse INI files.
 *
 * Copyright (C) 2010 - Francisco Javier Cuadrado <fcocuadrado@gmail.com>
 *
 * mini is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * mini is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mini; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

#include "readline.h"


/**
 *  Reads a line from an opened file.
 *
 *  @param file An opened file.
 *  @return The return value is the readed line.
 *          The function returns NULL, if the file can't be readed.
 */
char *
readline (FILE *file)
{
    char *line, *ret_line;
    size_t line_size = LINE_LEN;
    size_t line_len;

    assert (file != NULL);

    line = (char *) malloc (line_size * sizeof (char));
    if (line == NULL)
        return NULL;

    ret_line = fgets (line, line_size, file);
    if (ret_line == NULL) {
        free (line);
        return NULL;
    }

    line_len = strlen (line);

    while (line[line_len - 1] != EOL) {
        char *tmp_line;

        line_size *= 2;
        tmp_line = (char *) realloc (line, line_size * sizeof (char));
        if (tmp_line == NULL) {
            free (line);
            return NULL;
        }

        line = tmp_line;
        tmp_line = NULL;

        ret_line = fgets (&line[line_len], line_len + 2, file);
        if (ret_line == NULL) {
            free (line);
            return NULL;
        }

        line_len += strlen (ret_line);
    }

    return line;
}

