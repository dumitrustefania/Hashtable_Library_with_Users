// Copyright 2022 Dumitru Bianca Stefania 312CA
#ifndef MACROS_H_
#define MACROS_H_
#include <errno.h>

//  macros for sizes
#define MAX_STRING_SIZE 40
#define COMMAND_MAX 64
#define TOKENS_MAX 5
#define HMAX 7

//  macro for handling error codes
#define DIE(assertion, call_description)  \
	do                                    \
	{                                     \
		if (assertion)                    \
		{                                 \
			fprintf(stderr, "(%s, %d): ", \
					__FILE__, __LINE__);  \
			perror(call_description);     \
			exit(errno);                  \
		}                                 \
	} while (0)

#endif  // MACROS_H_
