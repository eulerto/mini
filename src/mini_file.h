/*
 * mmini_file.h
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

#ifndef __MINI_FILE_H__
#define __MINI_FILE_H__

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

typedef struct _MiniFile MiniFile;
struct _MiniFile {
    char *file_name;
    Section *section;
};


MiniFile *mini_file_new (const char *file_name);

void mini_file_free (MiniFile *mini_file);

MiniFile *mini_file_insert_section (MiniFile *mini_file, const char *section);

MiniFile *mini_file_insert_key_and_value (MiniFile *mini_file, const char *key, 
                                          const char *value);

unsigned int mini_file_get_number_of_sections (MiniFile *mini_file);

unsigned int mini_file_get_number_of_keys (MiniFile *mini_file, 
                                           const char *section);

char *mini_file_get_value (MiniFile *mini_file, const char *section, 
                           const char *key);

#endif /* __MINI_FILE_H__ */

