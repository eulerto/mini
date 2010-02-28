/*
 * parser.h
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

#ifndef __PARSER_H__
#define __PARSER_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mini_file.h"
#include "readline.h"
#include "strip.h"


MiniFile *mini_parse_file (const char *file_name);

#endif /* __PARSER_H__ */

