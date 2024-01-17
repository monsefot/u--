#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lex.h"

Lexer lexer_new(const char *text, size_t text_length, int position)
{
    Lexer lexer = {0};
    lexer.text = text;
    lexer.text_length = text_length;
    lexer.position = position;
    return lexer;
}

char current_char(Lexer *lexer)
{
    if (lexer->position >= lexer->text_length)
        return '\0';
    return lexer->text[lexer->position];
}

void next_char(Lexer *lexer)
{
    lexer->position++;
}

Syntax_Token lexer_next_token(Lexer *lexer)
{
    // <number>
    // + - * / ( )
    // <whitespace>

    Syntax_Token token = {0};

    if (current_char(lexer) == '\0') {
        token.kind = END_OF_FILE_TOKEN;
        token.position = '\0';
        return token;
    }

    if (isdigit(current_char(lexer)))
    {
        int start = lexer->position;

        while (isdigit(current_char(lexer)))
        {
            next_char(lexer);
        }

        int length = lexer->position - start;
        char *text = (char *) malloc(sizeof(char));
        strncpy(text, lexer->text + lexer->position, length);

        int *value = malloc(sizeof(int));
        *value = atoi(text);

        token.kind = NUMBER_TOKEN;
        token.position = start;
        token.text = text;
        token.text_length = length;
        token.value = value;

        free(value);

        return token;
    }

    if (isblank(current_char(lexer)))
    {
        int start = lexer->position;

        while (isblank(current_char(lexer)))
        {
            next_char(lexer);
        }

        int length = lexer->position - start;

        token.kind = WHITESPACE_TOKEN;
        token.position = start;
        token.text_length = length;
        return token;
    }

    if (current_char(lexer) == '+')
    {
        token.kind = PLUS_TOKEN;
        token.text = strncpy(token.text, lexer->text + lexer->position, 1);
        token.position = lexer->position++;
        return token;
    }

    else if (current_char(lexer) == '-')
    {
        token.kind = MINUS_TOKEN;
        token.text = strncpy(token.text, lexer->text + lexer->position, 1);
        token.position = lexer->position++;
        return token;
    }

    else if (current_char(lexer) == '*')
    {
        token.kind = STAR_TOKEN;
        token.text = strncpy(token.text, lexer->text + lexer->position, 1);
        token.position = lexer->position++;
        return token;
    }

    if (current_char(lexer) == '/')
    {
        token.kind = SLASH_TOKEN;
        token.text = strncpy(token.text, lexer->text + lexer->position, 1);
        token.position = lexer->position++;
        return token;
    }
    else if (current_char(lexer) == '(')
    {
        token.kind = LPARENT_TOKEN;
        token.text = strncpy(token.text, lexer->text + lexer->position, 1);
        token.position = lexer->position++;
        return token;
    }
    else if (current_char(lexer) == ')')
    {
        token.kind = RPARENT_TOKEN;
        token.text = strncpy(token.text, lexer->text + lexer->position, 1);
        token.position = lexer->position++;
        return token;
    }
    
    char *text = (char *) malloc(sizeof(char));
    strncpy(text, lexer->text + lexer->position, 1);

    token.kind = INVALID_TOKEN;
    token.text = text;
    token.position = lexer->position++;

    free(text);
    
    return token; 
}