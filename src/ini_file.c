
#include "ini_file.h"


static SectionData *
ini_file_section_data_new (const char *key, const char *value)
{
    SectionData *data;

    /* Key and value can't be NULL */
    assert (key != NULL);
    assert (value != NULL);

    data = (SectionData *) malloc (sizeof (SectionData));
    if (data == NULL)
        return NULL;

    data->key = strdup (key);
    data->value = strdup (value);
    data->next = NULL;

    return data;
}

static void
ini_file_section_data_free (SectionData *data)
{
    SectionData *p;

    /* Do nothing with NULL pointers */
    if (data == NULL)
        return;

    p = data;
    while (data != NULL) {
        data = p->next;
        p->next = NULL;

        free (p->key);
        free (p->value);
        free (p);
    }
}

static Section *
ini_file_section_new (const char *section_name)
{
    Section *section;

    /* Section name can't be NULL */
    assert (section_name != NULL);

    section = (Section *) malloc (sizeof (Section));
    if (section == NULL)
        return NULL;

    section->name = strdup (section_name);
    section->data = NULL;
    section->next = NULL;

    return section;
}

static void
ini_file_section_free (Section *section)
{
    Section *p;

    /* Do nothing with NULL pointers */
    if (section == NULL)
        return;

    p = section;
    while (section != NULL) {
        section = p->next;
        p->next = NULL;

        ini_file_section_data_free (p->data);
        free (p->name);
        free (p);
    }
}


/**
 *  Creates a new IniFile structure.
 *
 *  @param file_name INI file name.
 *  @return The return value is the new IniFile structure.
 *          The function returns NULL, if the IniFile structure can't be 
 *          created.
 */
IniFile *
ini_file_new (const char *file_name)
{
    IniFile *ini;

    ini = (IniFile *) malloc (sizeof (IniFile));
    if (ini == NULL)
        return NULL;

    ini->file_name = strdup (file_name);
    ini->section = NULL;

    return ini;
}

/**
 *  Frees an allocated IniFile structure.
 *
 *  @param ini An IniFile structure generated from an INI file.
 */
void
ini_file_free (IniFile *ini)
{
    /* Do nothing with NULL pointers */
    if (ini == NULL)
        return;

    ini_file_section_free (ini->section);

    free (ini->file_name);
    ini->file_name = NULL;

    free (ini);
}

/**
 *  Inserts a section in an IniFile structure.
 *
 *  @param ini An IniFile structure generated from an INI file.
 *  @param section_name A section name.
 *  @return The return value is the IniFile structure.
 *          The function returns NULL, if the section can't be inserted.
 */
IniFile *
ini_file_insert_section (IniFile *ini, const char *section_name)
{
    Section *section;

    /* Ini can't be NULL */
    assert (ini != NULL);

    section = ini_file_section_new (section_name);
    if (section == NULL)
        return NULL;

    /* Insert at first position */
    section->next = ini->section;
    ini->section = section;

    return ini;
}

/**
 *  Inserts a key-value pair in the last readed section from an INI file.
 *
 *  @param ini An IniFile structure generated from an INI file.
 *  @param key A key name.
 *  @param value The value of the key.
 *  @return The return value is the IniFile structure.
 *          The function returns NULL, if the key-value pair can't be inserted.
 */
IniFile *
ini_file_insert_key_and_value (IniFile *ini, const char *key, const char *value)
{
    SectionData *data;

    /* Ini can't be NULL */
    assert (ini != NULL);

    /* There isn't a section */
    if (ini->section == NULL)
        return NULL;

    data = ini_file_section_data_new (key, value);
    if (data == NULL)
        return NULL;

    data->next = ini->section->data;
    ini->section->data = data;

    return ini;
}

/**
 *  Gets the number of sections in an INI file.
 *
 *  @param ini An IniFile structure generated from an INI file.
 *  @return The return value is the number of sections in the given INI file.
 */
unsigned int
ini_file_get_number_of_sections (IniFile *ini)
{
    unsigned int num_sections = 0;
    Section *sec;

    for (sec = ini->section; sec != NULL; sec = sec->next)
        num_sections++;

    return num_sections;
}

/**
 *  Gets the number of keys in a given section.
 *
 *  @param ini An IniFile structure generated from an INI file.
 *  @param section A section name.
 *  @return The return value is the number of keys in the given section.
 */
unsigned int
ini_file_get_number_of_keys (IniFile *ini, const char *section)
{
    unsigned int num_keys = 0;
    Section *sec;
    SectionData *data;

    /* Search section */
    for (sec = ini->section; sec != NULL; sec = sec->next)
        if (strcmp (sec->name, section) == 0)
            break;

    /* Section not found */
    if (sec == NULL)
        return 0;

    for (data = sec->data; data != NULL; data = data->next)
        num_keys++;

    return num_keys;
}

/**
 *  Gets a value from a section's key.
 *
 *  @param ini An IniFile structure generated from an INI file.
 *  @param section A section name.
 *  @param key A key name.
 *  @return The return value is the value from the given section's key.
 *          The function returns NULL, if the given section or the given 
 *          key doesn't exist.
 */
char *
ini_file_get_value (IniFile *ini, const char *section, const char *key)
{
    Section *sec;
    SectionData *data;

    /* Search section */
    for (sec = ini->section; sec != NULL; sec = sec->next)
        if (strcmp (sec->name, section) == 0)
            break;

    /* Section not found */
    if (sec == NULL)
        return NULL;

    /* Search key */
    for (data = sec->data; data != NULL; data = data->next)
        if (strcmp (data->key, key) == 0)
            break;

    /* Key not found */
    if (data == NULL)
        return NULL;

    return data->value;
}

