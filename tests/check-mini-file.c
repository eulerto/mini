/*
 * check-mini-file.c
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

#include "check-mini-file.h"
#include "../src/mini-file.h"

#define MAX_TESTS 10


/**
 *  Tests 'mini_file_new' function providing a correct filename, empty filename
 *  and a NULL value as a filename.
 */
START_TEST (test_mini_file_new)
{
    MiniFile *mini_file;

    /* Correct filename */
    mini_file = mini_file_new ("testing.ini");
    fail_unless (mini_file != NULL, "MiniFile structure with a correct "
                 "filename hasn't been created correctly.");
    fail_unless (strcmp (mini_file->file_name, "testing.ini") == 0,
                 "MiniFile structure with a correct filename hasn't been "
                 "created correctly.");
    mini_file_free (mini_file);

    /* Emtpy filename */
    mini_file = mini_file_new ("");
    fail_unless (mini_file != NULL, "MiniFile structure with an empty filename "
                 "hasn't been created correctly.");
    fail_unless (strcmp (mini_file->file_name, "") == 0, "MiniFile structure "
                 "with an empty filename hasn't been created correctly.");
    mini_file_free (mini_file);

    /* NULL value as a filename */
    mini_file = mini_file_new (NULL);
    fail_unless (mini_file == NULL, "MiniFile structure with a NULL value as "
                 "a filename hasn't been created correctly.");
    mini_file_free (mini_file);
}
END_TEST

/**
 *  Tests 'mini_file' module functions providing some data.
 */
START_TEST (test_mini_file_functions)
{
    char *section_gotten, *key_gotten, *value_gotten;
    char section_name[256];
    char key_name[256];
    char value[256];
    int i, j;
    MiniFile *mini_file;

    mini_file = mini_file_new ("testing.ini");
    fail_unless (mini_file != NULL, "MiniFile structure hasn't been created "
                 "correctly.");

    /* Some different sections with different key-value pairs */
    for (i = 0; i < MAX_TESTS; i++) {
        sprintf (section_name, "testing_section_name_%d", i);

        mini_file = mini_file_insert_section (mini_file, section_name);
        fail_unless (mini_file != NULL, "mini_file_insert_section fails.");

        for (j = 0; j < MAX_TESTS; j++) {
            sprintf (key_name, "testing_key_name_%d%d", i, j);
            sprintf (value, "testing_value_%d%d", i, j);

            mini_file = mini_file_insert_key_and_value (mini_file, key_name,
                                                        value);
            fail_unless (mini_file != NULL,
                         "mini_file_insert_key_and_value fails.");
        }
    }

    /* Test the number of sections inserted */
    fail_unless (mini_file_get_number_of_sections (mini_file) != MAX_TESTS,
                 "Incorrect number of sections inserted.");

    /* Test if these sections and key-value pairs are inserted */
    for (i = 0; i < MAX_TESTS; i++) {
        sprintf (section_name, "testing_section_name_%d", i);

        section_gotten = mini_file_get_section (mini_file, i);
        fail_unless (strcmp (section_gotten, section_name) == 0,
                     "Section name hasn't been inserted correctly.");

        for (j = 0; j < MAX_TESTS; j++) {
            sprintf (key_name, "testing_key_name_%d%d", i, j);
            sprintf (value, "testing_value_%d%d", i, j);

            key_gotten = mini_file_get_key (mini_file, section_gotten, j);
            fail_unless (strcmp (key_gotten, key_name) == 0,
                         "Key name hasn't been inserted correctly.");

            value_gotten = mini_file_get_value (mini_file, section_gotten,
                                                key_gotten);
            fail_unless (strcmp (value_gotten, value) == 0,
                         "Value hasn't been inserted correctly.");
        }
    }

    /* Test if a key-value pair repeated is inserted */
    sprintf (section_name, "testing_section_name_%d", 1);
    sprintf (key_name, "testing_key_name_%d%d", 1, 1);
    sprintf (value, "testing_value_%d%d", 1, 1);

    mini_file = mini_file_insert_section (mini_file, section_name);
    fail_unless (mini_file != NULL, "Insert a repeated section fails.");

    mini_file = mini_file_insert_key_and_value (mini_file, key_name, value);
    fail_unless (mini_file != NULL, "Insert a repeated key-value pair fails.");
}
END_TEST


/**
 *  Creates a tests suite for the 'mini-file' module.
 *
 *  @return The return value is the tests suite for the 'mini-file' module.
 */
Suite *
check_mini_file_suite_new ()
{
    Suite *suite;
    TCase *tc_file;

    /* Create the tests suite for the 'mini-file' module */
    suite = suite_create ("mini-file");

    /* 'mini_file_new' function test cases */
    tc_file = tcase_create ("'mini_file_new' function");
    tcase_add_test (tc_file, test_mini_file_new);
    suite_add_tcase (suite, tc_file);

    /* 'mini_file_new' function test cases */
    tc_file = tcase_create ("'mini_file' module functions");
    tcase_add_test (tc_file, test_mini_file_functions);
    suite_add_tcase (suite, tc_file);

    return suite;
}

