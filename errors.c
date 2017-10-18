#include <errno.h>
#include <string.h>

#include "errors.h"

const char *errors[] = { STR_NO_ERROR,
                              STR_ERROR_NULL_POINTER,
                              STR_ERROR_MEMORY,
                              STR_ERROR_OPENING_FILE,
                              STR_ERROR_READING_FILE,
                              STR_ERROR_OPENING_DEVICE,
                              STR_ERROR_CONFIG_DEVICE,
                              STR_ERROR_INVALID_FILE,
                              STR_ERROR_CMD_LINE_ARGS
};

extern int errno;

status_t show_error(status_t st)
{
    if(errno)
        fprintf(stderr, "%s%c %s\n", errors[st], SEPARATOR, strerror(errno));
    else
        fprintf(stderr, "%s\n", errors[st]);

    return SUCCESS;
}

status_t show_error_info(status_t st, char *info)
{
    status_t aux_st;

    if(info == NULL){
        aux_st = ERROR_NULL_POINTER;
        show_error(aux_st);
        show_error(st);
        return aux_st;
    }
    if(errno)
        fprintf(stderr, "%s%c %s%c %s\n", errors[st], SEPARATOR,
                                          info, SEPARATOR,
                                          strerror(errno));
    else
        fprintf(stderr, "%s%c %s\n", errors[st], SEPARATOR, info);

    return SUCCESS;
}
