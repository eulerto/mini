/*
 * main.c
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
 * along with mini,; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

#include <stdio.h>

#include "parser.h"


/**
 *  Prints the program's usage.
 */
static void
print_usage (const char *program_name)
{
    printf ("usage: %s INI-FILE\n", program_name);
    exit (0);
}


/**
 *  Only for testing purpose.
 */
int
main (int argc, char *argv[])
{
    MiniFile *mini_file;

    /* An INI file must be passed */
    if (argc != 2)
        print_usage (argv[0]);

    /* Parse INI file */
    mini_file = mini_parse_file (argv[1]);
    if (mini_file == NULL) {
        fprintf (stderr, "%s: Can't parse '%s' INI file!\n", argv[0], argv[1]);
        return -1;
    }

    /* Use some functions of the mini library */
    printf ("Number of sections: %ld\n", 
            mini_file_get_number_of_sections (mini_file));

    printf ("Number of keys (section2): %ld\n", 
            mini_file_get_number_of_keys (mini_file, "section2"));

    printf ("section1.key11 = %s\n", 
            mini_file_get_value (mini_file, "section1", "key11"));

    /* Always remember to free MiniFile structure */
    mini_file_free (mini_file);

    return 0;
}
