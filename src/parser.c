/*
 * parser.c
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

#include "parser.h"


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
    start = strip (line);

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
 *
 *  @param file_name INI file path.
 *  @return The return value is a MiniFile structure generated from the 
 *          given INI file.
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
    line = readline (file);
    while (!feof (file) && (line != NULL)) {

        if (mini_parse_line (mini_file, line) < 0)
            break;

        line = readline (file);
    }

    fclose (file);

    return mini_file;
}

