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

#include "lexer.h"

#include "debug.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static map_token_t keywords;
static bool is_init = false;

static void keyword_init(void)
{
    map_set(&keywords, "static", TOKEN_STATIC);
    map_set(&keywords, "return", TOKEN_RET);
    map_set(&keywords, "enum", TOKEN_ENUM);
    map_set(&keywords, "struct", TOKEN_STRUCT);
    map_set(&keywords, "typedef", TOKEN_TYPEDEF);
    map_set(&keywords, "const", TOKEN_CONST);
    map_set(&keywords, "unsigned", TOKEN_UNSIGNED);
    map_set(&keywords, "if", TOKEN_IF);
    map_set(&keywords, "else", TOKEN_ELSE);
    map_set(&keywords, "while", TOKEN_WHILE);
    map_set(&keywords, "for", TOKEN_FOR);
}

static void lexer_readchar(lexer_t *self)
{

    if (self->read_position >= strlen(self->input))
    {
        self->ch = 0;
    }
    else
    {
        self->ch = self->input[self->read_position];
    }

    self->position = self->read_position++;
}

lexer_t lexer_init(char const *source)
{
    if (!is_init)
    {
        keyword_init();
        is_init = true;
    }

    lexer_t self;

    memset(&self, 0, sizeof(lexer_t));
    self.input = calloc(strlen(source) + 1, 1);
    memcpy(self.input, source, strlen(source));

    lexer_readchar(&self);
    return self;
}

static char *lexer_readident(lexer_t *self)
{
    size_t position = self->position;

    while (isalpha(self->ch) || self->ch == '_')
    {
        lexer_readchar(self);
    }

    char *literal = malloc(self->position - position + 1);
    assert(literal != NULL);

    memcpy(literal, self->input + position, self->position - position + 1);
    literal[self->position - position] = 0;

    return literal;
}

static void lexer_skip_whitespace(lexer_t *self)
{
    while (isspace(self->ch))
    {
        lexer_readchar(self);
    }
}

static char *lexer_read_nbr(lexer_t *self)
{
    size_t position = self->position;

    while (isdigit(self->ch))
    {
        lexer_readchar(self);
    }

    char *literal = malloc(self->position - position + 1);
    assert(literal != NULL);

    memcpy(literal, self->input + position, self->position - position + 1);
    literal[self->position - position] = 0;

    return literal;
}

token_t lexer_next_token(lexer_t *self)
{
    token_t token;

    lexer_skip_whitespace(self);

    switch (self->ch)
    {
        case '=':
            if (self->input[self->position + 1] == '=')
            {
                self->position++;
                token = (token_t){.type = TOKEN_EQEQ, .value = NULL};
            }
            else
            {
                token = (token_t){.type = TOKEN_ASSIGN, .value = NULL};
            }
            break;
        case ';':
            token = (token_t){.type = TOKEN_SEMICOLON, .value = NULL};
            break;
        case '(':
            token = (token_t){.type = TOKEN_LPARENT, .value = NULL};
            break;
        case ')':
            token = (token_t){.type = TOKEN_RPARENT, .value = NULL};
            break;
        case ',':
            token = (token_t){.type = TOKEN_COMMA, .value = NULL};
            break;
        case '+':
            token = (token_t){.type = TOKEN_PLUS, .value = NULL};
            break;
        case '-':
            if (self->input[self->position + 1] == '>')
            {
                self->position++;
                token = (token_t){.type = TOKEN_ARROW, .value = NULL};
            }
            else
            {
                token = (token_t){.type = TOKEN_MINUS, .value = NULL};
            }

            break;
        case '{':
            token = (token_t){.type = TOKEN_LBRACE, .value = NULL};
            break;
        case '}':
            token = (token_t){.type = TOKEN_RBRACE, .value = NULL};
            break;
        case '\0':
            token = (token_t){.type = TOKEN_EOF, .value = NULL};
            break;
        case '!':
            if (self->input[self->position + 1] == '=')
            {
                token = (token_t){.type = TOKEN_NEQ, .value = NULL};
            }
            else
            {
                token = (token_t){.type = TOKEN_BANG, .value = NULL};
            }
            break;
        case '<':
            if (self->input[self->position + 1] == '=')
            {
                self->position++;
                token = (token_t){.type = TOKEN_LTEQ, .value = NULL};
            }
            else
            {
                token = (token_t){.type = TOKEN_LT, .value = NULL};
            }
            break;
        case '>':
            if (self->input[self->position + 1] == '=')
            {
                self->position++;
                token = (token_t){.type = TOKEN_GTEQ, .value = NULL};
            }
            else
            {
                token = (token_t){.type = TOKEN_GT, .value = NULL};
            }
            break;

        case '*':
            token = (token_t){.type = TOKEN_STAR, .value = NULL};
            break;
        default:
            if (isalpha(self->ch) || self->ch == '_')
            {
                char *keyword = lexer_readident(self);
                enum token_type *type = map_get(&keywords, keyword);

                if (!type)
                {
                    token = (token_t){.type = TOKEN_NAME, .value = keyword};
                }
                else
                {
                    token = (token_t){.value = NULL, .type = *type};
                }

                return token;
            }
            else if (isdigit(self->ch))
            {
                token = (token_t) {.type = TOKEN_NBR, .value = lexer_read_nbr(self)};
            }
            else
            {
                token = (token_t){.type = TOKEN_ILLEGAL, .value = NULL};
            }
    }

    lexer_readchar(self);
    return token;
}