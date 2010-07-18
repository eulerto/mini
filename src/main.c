/*
 * main.c
 * This file is part of mini, a library to parse INI files.
 *
 * Copyright (c) 2010, Francisco Javier Cuadrado <fcocuadrado@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the Francisco Javier Cuadrado nor the names of its 
 *     contributors may be used to endorse or promote products derived from 
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
