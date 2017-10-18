#ifndef ERRORS
	#define ERRORS
	
	#include <stdio.h>

	#define STR_ERROR_OPENING_DEVICE    "Error opening device: "
	#define STR_ERROR_CONFIG_DEVICE     "Error configuring device: "
	#define STR_ERROR_OPENING_FILE      "Error opening file: "
	#define STR_ERROR_READING_FILE      "Error reading file: "
	#define STR_NO_ERROR                "No error found."
	#define STR_ERROR_NULL_POINTER      "Error: Null pointer recieved."
	#define STR_ERROR_MEMORY            "Error: Not enough memory"
	#define STR_ERROR_INVALID_FILE      "Error: Can't process that file"
	#define STR_ERROR_CMD_LINE_ARGS     "Error: Invalid command line arguments"

	typedef enum {SUCCESS,
	              ERROR_NULL_POINTER,
	              ERROR_MEMORY,
	              ERROR_OPENING_FILE,
	              ERROR_READING_FILE,
	              ERROR_OPENING_DEVICE,
	              ERROR_CONFIG_DEVICE,
	              ERROR_INVALID_FILE,
	              ERROR_CMD_LINE_ARGS
	} status_t;

	char *errors[] = { STR_NO_ERROR,
	                   STR_ERROR_NULL_POINTER,
	                   STR_ERROR_MEMORY,
	                   STR_ERROR_OPENING_FILE,
	                   STR_ERROR_READING_FILE,
	                   STR_ERROR_OPENING_DEVICE,
	                   STR_ERROR_CONFIG_DEVICE,
	                   STR_ERROR_INVALID_FILE,
	                   STR_ERROR_CMD_LINE_ARGS
	};

	status_t show_error(status_t st);
	status_t show_error_info(status_t st, char *info);
#endif