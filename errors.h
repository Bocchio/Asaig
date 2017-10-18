#ifndef ERRORS_H
	#define ERRORS_H

	#include <stdio.h>

	#define STR_ERROR_OPENING_DEVICE    "Error opening device"
	#define STR_ERROR_CONFIG_DEVICE     "Error configuring device"
	#define STR_ERROR_OPENING_FILE      "Error opening file"
	#define STR_ERROR_READING_FILE      "Error reading file"
	#define STR_NO_ERROR                "No error found"
	#define STR_ERROR_NULL_POINTER      "Error recieved null pointer"
	#define STR_ERROR_MEMORY            "Error not enough memory"
	#define STR_ERROR_INVALID_FILE      "Error unable to process file"
	#define STR_ERROR_CMD_LINE_ARGS     "Error invalid command line arguments"

	#define SEPARATOR	':'

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

	status_t show_error(status_t st);
	status_t show_error_info(status_t st, char *info);
#endif