/*
 * mini.c
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

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "mini.h"
#include "mini-readline.h"
#include "mini-strip.h"


/**
 *  Parses a line readed from an INI file.
 *
 *  @param mini_file A MiniFile structure to save all the parsed data.
 *  @param line A line readed from an INI file.
 *  @return The function returns a negative number, if the line can't be parsed.
 */
static int
mini_parse_line (MiniFile *mini_file, char *line)
{
    char *start, *end, *equal;
    char *section, *key, *value;
    size_t section_len, key_len, value_len;
    MiniFile *mini_file_tmp;

    /* Line can't be NULL */
    assert (line != NULL);

    /* Strip all whitespaces */
    start = mini_strip (line);

    /* Empty line */
    if (strcmp (start, "") == 0) 
        return 0;

    /* Non empty line */
    switch (start[0]) {

        /* Section */
        case '[':
            /* At the end of the line must be an end of section (']') */
            end = strchr (start, ']');
            if ((end == NULL) || (end[1] != '\0'))
                return -1;

            /* Get length of the section */
            section_len = strlen (start) - 2;

            /* Empty section */
            if (section_len == 0)
                return -1;

            /* Get section string */
            section = (char *) malloc ((section_len + 1) * sizeof (char));
            if (section == NULL)
                return -1;

            strncpy (section, &start[1], section_len);
            section[section_len] = '\0';

            mini_file_tmp = mini_file_insert_section (mini_file, section);
            if (mini_file_tmp == NULL)
                return -1;

            break;

        /* Comment */
        case ';':
            /* Process comments here */
            break;

        default:
            /* Between key and value must be an equality symbol ('=') */
            equal = strchr (start, '=');
            if ((equal == NULL) || (start == equal) || (equal[1] == '\0'))
                return -1;

            /* Get length of the key string */
            for (key_len = 0; start[key_len] != '='; key_len++)
                ;

            /* Get key string */
            key = (char *) malloc ((key_len + 1) * sizeof (char));
            if (key == NULL)
                return -1;

            strncpy (key, start, key_len);
            key[key_len] = '\0';

            /* Get length of the value string */
            value_len = strlen (equal) - 1;

            /* Get value string */
            value = (char *) malloc ((value_len + 1) * sizeof (char));
            if (value == NULL)
                return -1;

            strncpy (value, &equal[1], value_len);
            value[value_len] = '\0';

            mini_file_tmp = mini_file_insert_key_and_value (mini_file, key, 
                                                            value);
            if (mini_file_tmp == NULL)
                return -1;
    }

    return 0;
}


/**
 *  Parses a given INI file generating a MiniFile structure.
 *  This is the main function of mini library.
 *
 *  @param file_name INI file path.
 *  @return The return value is a MiniFile structure generated from the given
 *          INI file.
 *          The function returns NULL, if the given INI file can't be parsed.
 */
MiniFile *
mini_parse_file (const char *file_name)
{
    char *line;
    FILE *file;
    MiniFile *mini_file;

    /* Filename can't be NULL */
    assert (file_name != NULL);

    /* Create an empty MiniFile structure */
    mini_file = mini_file_new (file_name);
    if (mini_file == NULL)
        return NULL;

    file = fopen (file_name, "r");
    if (file == NULL) {
        mini_file_free (mini_file);
        return NULL;
    }

    /* Read line and parse it */
    line = mini_readline (file);
    while (!feof (file) && (line != NULL)) {

        if (mini_parse_line (mini_file, line) < 0)
            break;

        line = mini_readline (file);
    }

    fclose (file);

    return mini_file;
}

/**
 *  Frees all the data allocated by mini library.
 *  This must be used when you don't want to use more the MiniFile structure
 *  created by 'mini_parse_file' function.
 *
 *  @param mini_file A MiniFile structure created by 'mini_parse_file' function.
 */
void
mini_free (MiniFile *mini_file)
{
    mini_file_free (mini_file);
}

/**
 *  Gets the number of sections in the parsed INI file.
 *
 *  @param mini_file A MiniFile structure created by 'mini_parse_file' function.
 *  @return The return value is the number of sections in the parsed INI file.
 */
unsigned int
mini_get_number_of_sections (MiniFile *mini_file)
{
    unsigned int num_sections = 0;

    num_sections = mini_file_get_number_of_sections (mini_file);

    return num_sections;
}

/**
 *  Gets the number of keys in a given section.
 *
 *  @param mini_file A MiniFile structure created by 'mini_parse_file' function.
 *  @param section A section name.
 *  @return The return value is the number of keys in the given section.
 */
unsigned int
mini_get_number_of_keys (MiniFile *mini_file, const char *section)
{
    unsigned int num_keys = 0;

    num_keys = mini_file_get_number_of_keys (mini_file, section);

    return num_keys;
}

/**
 *  Gets the name of the section which is in the given position.
 *
 *  @param mini_file A MiniFile structure created by 'mini_parse_file' function.
 *  @param section_pos Section's position.
 *  @return The return value is the name of the section which is in the given
 *          position.
 *          The function returns NULL, if there isn't a section in the given
 *          position.
 */
char *
mini_get_section (MiniFile *mini_file, unsigned int section_pos)
{
    char *section_name;

    section_name = mini_file_get_section (mini_file, section_pos);

    return section_name;
}

/**
 *  Gets the name of the key which is in the given section and in the given
 *  position.
 *
 *  @param mini_file A MiniFile structure created by 'mini_parse_file' function.
 *  @param section Section from where the key is gotten.
 *  @param key_pos Key's position.
 *  @return The return value is the name of the key which is in the given
 *          section and in the given position.
 *          The function returns NULL, if there isn't a key in the given section
 *          and in the given position.
 */
char *
mini_get_key (MiniFile *mini_file, const char *section, unsigned int key_pos)
{
    char *key_name;

    key_name = mini_file_get_key (mini_file, section, key_pos);

    return key_name;
}

/**
 *  Gets a value from a section's key.
 *
 *  @param mini_file A MiniFile structure created by 'mini_parse_file' function.
 *  @param section A section name.
 *  @param key A key name.
 *  @return The return value is the value from the given section's key.
 *          The function returns NULL, if the given section or the given 
 *          key doesn't exist.
 */
char *
mini_get_value (MiniFile *mini_file, const char *section, const char *key)
{
    char *value;

    value = mini_file_get_value (mini_file, section, key);

    return value;
}

