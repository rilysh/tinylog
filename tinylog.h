#ifndef LOG_H
# define LOG_H

/* Color strings. */
#define TRACE_COLOR   "\x1b[0;37m"
#define DEBUG_COLOR   "\x1b[0;33m"
#define INFO_COLOR    "\x1b[0;92m"
#define WARN_COLOR    "\x1b[0;31m"
#define ERROR_COLOR   "\x1b[0;91m"
#define FATAL_COLOR   "\x1b[1;91m"		
#define END_COLOR     "\x1b[0m"

/* Log levels. */
enum {
	TRACE = 0,
	DEBUG = 1,
        INFO  = 2,
	WARN  = 3,
	ERROR = 4,
	FATAL = 5
};

/* Log structure. */
struct log {
	char *trace_color;
	char *debug_color;
	char *info_color;
	char *warn_color;
	char *error_color;
	char *fatal_color;
	int show_time;
};

/* Function prototype. */
void log_print(struct log *, int, const char *, int,
	       const char *, ...);

/* Trace logging. */
#define log_trace(log, ...)					\
	log_print(log, TRACE, __FILE__, __LINE__, __VA_ARGS__)

/* Debug logging. */
#define log_debug(log, ...)					\
	log_print(log, DEBUG, __FILE__, __LINE__, __VA_ARGS__)

/* Information logging. */
#define log_info(log, ...)					\
	log_print(log, INFO, __FILE__, __LINE__, __VA_ARGS__)

/* Warning logging. */
#define log_warn(log, ...)					\
	log_print(log, WARN, __FILE__, __LINE__, __VA_ARGS__)

/* Error logging. */
#define log_error(log, ...)					\
	log_print(log, ERROR, __FILE__, __LINE__, __VA_ARGS__)

/* Fatal logging. */
#define log_fatal(log, ...)					\
	log_print(log, FATAL, __FILE__, __LINE__, __VA_ARGS__)

#endif /* LOG_H */
