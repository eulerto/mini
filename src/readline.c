
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

