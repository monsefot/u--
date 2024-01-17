#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "./src/lex/file.h"
#include "./src/lex/lex.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "[ERROR] No source code path argument could be found.\n");
		return EXIT_FAILURE;
	}

	char *source_code_path = argv[1];
	
	File_Content *content = new_source_code(source_code_path);
	
	Lexer lexer = lexer_new(content->buffer, content->size, 0);

	
	Syntax_Token token = lexer_next_token(&lexer);
	printf("token: %d\n", token.kind);
	
	free(content);

	return 0;
}
