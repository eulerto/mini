/*
 * check-mini-readline.c
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

#include <check.h>
#include <stdio.h>
#include <string.h>

#include "check-mini-readline.h"
#include "../src/mini-readline.h"

#define EMPTY_FILE "resources/empty-file.txt"
#define ONE_LINE_FILE "resources/one-line-file.txt"
#define THREE_LINE_FILE "resources/three-line-file.txt"

#define LINE "abcdefghijklmnopqrstuvwxyz\n"


/**
 *  Tests 'mini_readline' function providing an empty file and files with some
 *  lines as the parameter. These file can have one line or three lines, these
 *  lines contain "abcdefghijklmnopqrstuvwxyz".
 */
START_TEST (test_mini_readline)
{
    char *line;
    FILE *empty_file;
    FILE *one_line_file, *three_line_file;

    /* Test an empty file */
    empty_file = fopen (EMPTY_FILE, "r");
    if (empty_file == NULL) {
        printf ("Can't open empty file!");
        return;
    }

    fail_unless (mini_readline (empty_file) == NULL,
                 "'mini_readline' should return NULL value from an empty file");

    fclose (empty_file);


    /* Test a file with one line */
    one_line_file = fopen (ONE_LINE_FILE, "r");
    if (one_line_file == NULL) {
        printf ("Can't open one line file!");
        return;
    }

    fail_unless (strcmp (mini_readline (one_line_file), LINE) == 0,
                 "The line hasn't been read correctly from "
                 "'one-line-file.txt'");

    fclose (one_line_file);

    /* Test a file with three lines */
    three_line_file = fopen (THREE_LINE_FILE, "r");
    if (three_line_file == NULL) {
        printf ("Can't open three line file!");
        return;
    }

    line = mini_readline (three_line_file);
    while (!feof (three_line_file) && (line != NULL)) {
        fail_unless (strcmp (line, LINE) == 0,
                     "A line hasn't been read correctly from "
                     "'three-line-file.txt'");

        line = mini_readline (three_line_file);
    }

    fclose (three_line_file);
}
END_TEST


/**
 *  Creates a tests suite for the 'mini-readline' module.
 *
 *  @return The return value is the tests suite for the 'mini-readline' module.
 */
Suite *
check_mini_readline_suite_new ()
{
    Suite *suite;
    TCase *tc_readline;

    /* Create the tests suite for the 'mini-readline' module */
    suite = suite_create ("mini-readline");

    /* 'mini_readline' function test cases */
    tc_readline = tcase_create ("'mini_readline' function");
    tcase_add_test (tc_readline, test_mini_readline);
    suite_add_tcase (suite, tc_readline);

    return suite;
}
