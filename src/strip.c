
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

