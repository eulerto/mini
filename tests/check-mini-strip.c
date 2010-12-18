/*
 * check-mini-strip.c
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
#include <stdlib.h>
#include <string.h>

#include "check-mini-strip.h"
#include "../src/mini-strip.h"

/* String used in all tests */
#define CHARSET "abcdefghijklmnopqrstuvwxyz"


/**
 *  Tests 'mini_strip' function providing strings with spaces as the parameter.
 *  These strings can have right spaces, left spaces or both.
 */
START_TEST (test_mini_strip_string_with_spaces)
{
    char *string;

    /* String with right spaces */
    string = strdup ("   " CHARSET);
    fail_unless (strcmp (mini_strip (string), CHARSET) == 0,
                 "String with left spaces hasn't been stripped correctly");
    free (string);

    /* String with left spaces */
    string = strdup (CHARSET "   ");
    fail_unless (strcmp (mini_strip (string), CHARSET) == 0,
                 "String with right spaces hasn't been stripped correctly");
    free (string);

    /* String with right and left spaces */
    string = strdup ("   " CHARSET "   ");
    fail_unless (strcmp (mini_strip (string), CHARSET) == 0,
                 "String with right and left spaces hasn't been stripped "
                 "correctly");
    free (string);
}
END_TEST

/**
 *  Tests 'mini_strip' function providing strings without spaces as the
 *  parameter. These strings can be an empty string or a regular string.
 */
START_TEST (test_mini_strip_string_without_spaces)
{
    char *string;

    /* Empty string */
    string = strdup ("");
    fail_unless (strcmp (mini_strip (string), "") == 0,
                 "Emtpy string hasn't been stripped correctly");
    free (string);

    /* Regular string */
    string = strdup (CHARSET);
    fail_unless (strcmp (mini_strip (string), CHARSET) == 0,
                 "String without spaces hasn't been stripped correctly");
    free (string);
}
END_TEST


/**
 *  Creates a tests suite for the 'mini-strip' module.
 *
 *  @return The return value is the tests suite for the 'mini-strip' module.
 */
Suite *
check_mini_strip_suite_new ()
{
    Suite *suite;
    TCase *tc_strip;

    /* Create the tests suite for the 'mini-strip' module */
    suite = suite_create ("mini-strip");

    /* 'mini_strip' function test cases */
    tc_strip = tcase_create ("'mini_strip' function");
    tcase_add_test (tc_strip, test_mini_strip_string_with_spaces);
    tcase_add_test (tc_strip, test_mini_strip_string_without_spaces);
    suite_add_tcase (suite, tc_strip);

    return suite;
}

