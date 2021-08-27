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


/* PLEASE DO NOT FORMAT THIS FILE */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "debug.h"
#include "lexer.h"

void basic_lexing(ignored void **state)
{
    char const *input = "=+(){},;";
    token_t const expected[] = {
        {.type = TOKEN_ASSIGN, .value = NULL},
        {.type = TOKEN_PLUS, .value = NULL},
        {.type = TOKEN_LPARENT, .value = NULL},
        {.type = TOKEN_RPARENT, .value = NULL},
        {.type = TOKEN_LBRACE, .value = NULL},
        {.type = TOKEN_RBRACE, .value = NULL},
        {.type = TOKEN_COMMA, .value = NULL},
        {.type = TOKEN_SEMICOLON, .value = NULL},
        {.type = TOKEN_EOF, .value = NULL}
    };

    lexer_t lexer = lexer_init(input);
    token_t token;
    size_t i = 0;

    do 
    {
        token = lexer_next_token(&lexer);
        assert_int_equal(token.type, expected[i++].type);
        assert_ptr_equal(token.value, NULL);
    } while(token.type != TOKEN_EOF);
}


void actual_lexing(ignored void **state)
{
    char const *input = 
        "int add(int x, int y)"
        "{\n"
        "   return x + y;\n"
        "}\n";

    token_t const expected[] = {
        {.type = TOKEN_NAME, .value = "int"},
        {.type = TOKEN_NAME, .value = "add"},
        {.type = TOKEN_LPARENT, .value = NULL},
        {.type = TOKEN_NAME, .value = "int"},
        {.type = TOKEN_NAME, .value = "x"},
        {.type = TOKEN_COMMA, .value = NULL},
        {.type = TOKEN_NAME, .value = "int"},
        {.type = TOKEN_NAME, .value = "y"},
        {.type = TOKEN_RPARENT, .value = NULL},
        {.type = TOKEN_LBRACE, .value = NULL},
        {.type = TOKEN_RET, .value = NULL},
        {.type = TOKEN_NAME, .value = "x"},
        {.type = TOKEN_PLUS, .value = NULL},
        {.type = TOKEN_NAME, .value = "y"},
        {.type = TOKEN_SEMICOLON, .value = NULL},
        {.type = TOKEN_RBRACE, .value = NULL},
        {.type = TOKEN_EOF, .value = NULL}
    };

    lexer_t lexer = lexer_init(input);
    token_t token;
    size_t i = 0;

    do 
    {
        token = lexer_next_token(&lexer);
        /* cprint("{} ?= {}", token_type[token.type], token_type[expected[i].type]); */ // Uncomment me for debug
        assert_int_equal(token.type, expected[i].type);

        if (token.value == NULL && expected[i].value == NULL)
        {
            assert_true(1);
            i++;
        }
        else 
        {
            /* cprint("{} ?= {}", token.value, expected[i].value); */ // Uncomment me for debug
            assert_string_equal(token.value, expected[i++].value);
        }
    } while(token.type != TOKEN_EOF);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(basic_lexing),
        cmocka_unit_test(actual_lexing)
    };

    cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}
