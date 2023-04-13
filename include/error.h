/*
 * error.h
 * -------
 * Helpers for generating errors.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

#ifndef ERROR_H
#define ERROR_H

// Codes
#define ERR_CODE_GENERAL    1
#define ERR_CODE_ALLOC      2

// Colours
#define ANSI_FG_GREY    "\x1b[30m"
#define ANSI_FG_RED     "\x1b[31m"
#define ANSI_FG_GREEN   "\x1b[32m"
#define ANSI_FG_YELLOW  "\x1b[33m"
#define ANSI_FG_BLUE    "\x1b[34m"
#define ANSI_FG_MAGENTA "\x1b[35m"
#define ANSI_FG_CYAN    "\x1b[36m"
#define ANSI_FG_RESET   "\x1b[0m"

/*
 * err
 * ---
 * Exit the program after displaying a message in red.
 */
noreturn void err(char *msg, int code) {
    printf("%s%s%s\n", ANSI_FG_RED, msg, ANSI_FG_RESET);
    exit(code);
}

/*
 * err_loc
 * -------
 * Exit the program after displaying a message (location in grey, message in red).
 */
noreturn void err_loc(char *location, char *msg, int code) {
    printf("%s[%s]%s %s%s%s\n", ANSI_FG_GREY, location, ANSI_FG_RESET,
        ANSI_FG_RED, msg, ANSI_FG_RESET);
    exit(code);
}

#endif  // ERROR_H
