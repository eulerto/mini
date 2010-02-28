
#ifndef __INI_FILE_H__
#define __INI_FILE_H__

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct _SectionData SectionData;
struct _SectionData {
    char *key;
    char *value;
    SectionData *next;
};

typedef struct _Section Section;
struct _Section {
    char *name;
    SectionData *data;
    Section *next;
};

typedef struct _IniFile IniFile;
struct _IniFile {
    char *file_name;
    Section *section;
};


IniFile *ini_file_new (const char *file_name);

void ini_file_free (IniFile *ini);

IniFile *ini_file_insert_section (IniFile *ini, const char *section);

IniFile *ini_file_insert_key_and_value (IniFile *ini, const char *key, 
                                        const char *value);

unsigned int ini_file_get_number_of_sections (IniFile *ini);

unsigned int ini_file_get_number_of_keys (IniFile *ini, const char *section);

char *ini_file_get_value (IniFile *ini, const char *section, const char *key);

#endif /* __INI_FILE_H__ */

