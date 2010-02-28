
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ini_file.h"
#include "readline.h"
#include "strip.h"


IniFile *ini = NULL;


/**
 *  Parses a line readed from an INI file.
 *
 *  @param line A line readed from an INI file.
 *  @return The function returns a negative number, if the line can't be parsed.
 */
static int
parse_line (char *line)
{
    char *start, *end, *equal;
    char *section, *key, *value;
    size_t section_len, key_len, value_len;
    IniFile *tmp;

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

            printf ("section: %s\n", section);

            tmp = ini_file_insert_section (ini, section);
            if (tmp == NULL)
                return -1;

            break;

        /* Comment */
        case ';':
            printf ("comment: %s\n", start);
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

            printf ("key: %s\n", key);
            printf ("value: %s\n", value);

            tmp = ini_file_insert_key_and_value (ini, key, value);
            if (tmp == NULL)
                return -1;
    }

    return 0;
}


int
main (int argc, char *argv[])
{
    char *line;
    FILE *file;

    assert (argv[1] != NULL);

    file = fopen (argv[1], "r");
    if (file == NULL) {
        fprintf (stderr, "%s: Can't open '%s'!\n", argv[0], argv[1]);
        return -1;
    }

    ini = ini_file_new (argv[1]);
    if (ini == NULL) {
        fprintf (stderr, "%s: Not enough memory!\n", argv[0]);
        fclose (file);
        return -1;
    }

    line = readline (file);
    while (!feof (file) && (line != NULL)) {

        if (parse_line (line) < 0) {
            fprintf (stderr, "%s: Can't parse line!\n", argv[0]);
            break;
        }

        line = readline (file);
    }

    fclose (file);

    printf ("Number of sections: %ld\n", ini_file_get_number_of_sections (ini));
    printf ("Number of keys (seccion_segunda): %ld\n", 
            ini_file_get_number_of_keys (ini, "seccion_segunda"));

    printf ("seccion_primera.clave11 = %s\n", 
            ini_file_get_value (ini, "seccion_primera", "clave11"));

    return 0;
}
