/**
 * Copyright (C) 2021 Keyboard Slayer
 *
 * This file is part of cc.
 *
 * cc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cc.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "debug.h"
#include "lexer.h"

#include <libcopland/main.h>
#include <stdio.h>
#include <stdlib.h>

MaybeStr load_source(char const *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return Nothing(MaybeStr);
    }

    fseek(fp, 0, SEEK_END);

    long file_length = ftell(fp);
    if (file_length == -1)
    {
        return Nothing(MaybeStr);
    }

    fseek(fp, 0, SEEK_SET);

    char *buffer = (char *) malloc(file_length + 1);
    fread(buffer, (size_t) file_length, 1, fp);
    fclose(fp);

    buffer[file_length] = '\0';

    return Just(MaybeStr, buffer);
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        cprint("FATAL ERROR: No file given");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        MaybeStr src = load_source(argv[i]);
        if (Nothing$(src))
        {
            cprint("FATAL ERROR: couldn't load {}", argv[i]);
            return 1;
        }

        free(src.value);
    }

    return 0;
}