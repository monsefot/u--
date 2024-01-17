#ifndef LEX_H
#define LEX_H

#include <stdio.h>

typedef enum
{
    END_OF_FILE_TOKEN,
    NUMBER_TOKEN,
    WHITESPACE_TOKEN,
    PLUS_TOKEN,
    MINUS_TOKEN,
    STAR_TOKEN,
    SLASH_TOKEN,
    LPARENT_TOKEN,
    RPARENT_TOKEN,
    INVALID_TOKEN
} Syntax_Kind;

typedef struct
{
    Syntax_Kind kind;
    int position;
    char *text;
    size_t text_length;
    void *value;
} Syntax_Token;

typedef struct
{
    const char *text;
    size_t text_length;
    int position;
} Lexer;

Lexer lexer_new(const char *content, size_t content_length, int position);
Syntax_Token lexer_next_token(Lexer *lexer);

#endif // LEX_H