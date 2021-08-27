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

#pragma once

#include <libcopland/utils.h>
#include <rxi/map.h>
#include <rxi/vec.h>

#define FOREACH_TYPE(FUNC)                                                     \
    FUNC(TOKEN_NAME)                                                           \
    FUNC(TOKEN_LPARENT)                                                        \
    FUNC(TOKEN_RPARENT)                                                        \
    FUNC(TOKEN_COMMA)                                                          \
    FUNC(TOKEN_RET)                                                            \
    FUNC(TOKEN_VALUE)                                                          \
    FUNC(TOKEN_LBRACE)                                                         \
    FUNC(TOKEN_RBRACE)                                                         \
    FUNC(TOKEN_ASSIGN)                                                         \
    FUNC(TOKEN_PLUS)                                                           \
    FUNC(TOKEN_SEMICOLON)                                                      \
    FUNC(TOKEN_EOF)                                                            \
    FUNC(TOKEN_ILLEGAL)                                                        \
    FUNC(TOKEN_STATIC)                                                         \
    FUNC(TOKEN_ENUM)                                                           \
    FUNC(TOKEN_STRUCT)                                                         \
    FUNC(TOKEN_TYPEDEF)                                                        \
    FUNC(TOKEN_CONST)                                                          \
    FUNC(TOKEN_UNSIGNED)                                                       \
    FUNC(TOKEN_BANG)                                                           \
    FUNC(TOKEN_ARROW)                                                          \
    FUNC(TOKEN_MINUS)                                                          \
    FUNC(TOKEN_NBR)                                                            \
    FUNC(TOKEN_LT)                                                             \
    FUNC(TOKEN_GT)                                                             \
    FUNC(TOKEN_LTEQ)                                                           \
    FUNC(TOKEN_GTEQ)                                                           \
    FUNC(TOKEN_EQEQ)                                                           \
    FUNC(TOKEN_NEQ)                                                            \
    FUNC(TOKEN_FOR)                                                            \
    FUNC(TOKEN_WHILE)                                                          \
    FUNC(TOKEN_IF)                                                             \
    FUNC(TOKEN_ELSE)                                                           \
    FUNC(TOKEN_STAR)

enum token_type
{
    FOREACH_TYPE(GENERATE_ENUM)
};

used static char const *token_type[] = {FOREACH_TYPE(GENERATE_STRING)};

typedef struct
{
    enum token_type type;
    char const *value;
} token_t;

typedef struct
{
    char *input;
    size_t position;
    size_t read_position;
    char ch;
} lexer_t;

typedef vec_t(token_t) vec_token_t;
typedef map_t(enum token_type) map_token_t;

lexer_t lexer_init(char const *source);
token_t lexer_next_token(lexer_t *self);