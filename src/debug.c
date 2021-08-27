/**
 * Copyright (C) 2021 Keyboard Slayer
 * 
 * This file is part of WM.
 * 
 * WM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * WM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with WM.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "debug.h"

#include <string.h>
#include <stdio.h>

void display_out(const char *msg)
{
    if (msg)
    {
        fwrite(msg, 1, strlen(msg), stdout);
    }
}

void cprint_impl(char const *filename, size_t line_nbr, char const *format, struct fmt_args args)
{
    print_format(display_out, "\033[33m{}:{}\033[0m ", filename, line_nbr);
    PRINT_FORMAT(display_out, format, args);
    display_out("\n");
}