/*
 * strip.c
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

#include "strip.h"


/**
 *  Strips left whitespaces.
 *
 *  @param string String to be stripped.
 *  @return The return value is the stripped string.
 */
char *
lstrip (char *string)
{
    char *p;

    /* String can't be NULL */
    assert (string != NULL);

    /* Search the first non whitespace character from left to right */
    for (p = string; (p != NULL) && isspace (*p); p++)
        ;

    return p;
}

/**
 *  Strips right whitespaces.
 *
 *  @param string String to be stripped.
 *  @return The return value is the stripped string.
 */
char *
rstrip (char *string)
{
    char *p;
    int pos;
    size_t len;

    /* String can't be NULL */
    assert (string != NULL);

    p = string;
    len = strlen (string);

    /* Search the first non whitespace character from right to left */
    for (pos = len - 1; (pos >= 0) && isspace (p[pos]); pos--)
        ;

    if ((pos >= 0) && !isspace (p[pos]))
        p[pos + 1] = '\0';

    return string;
}

/**
 *  Strips left and right whitespaces.
 *
 *  @param string String to be stripped.
 *  @return The return value is the stripped string.
 */
char *
strip (char *string)
{
    char *ret;

    /* String can't be NULL */
    assert (string != NULL);

    ret = lstrip (string);
    ret = rstrip (ret);

    return ret;
}

