#include <stdio.h>
#include <stdarg.h>
#include "err.h"

FILE * log_stream = NULL;

int init_log() {
    log_stream = fopen("log.txt", "w");
    return log_stream != NULL;
}

void end_log() {
    if (log_stream != NULL) {
        fclose(log_stream);
    }
}

void log_write(const char *fmt, ...) {
    if (log_stream != NULL) {
        va_list args;
        va_start(args, fmt);
        vfprintf(log_stream, fmt, args);
        va_end(args);
    }
}
