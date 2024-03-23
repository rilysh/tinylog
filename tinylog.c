#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "tinylog.h"

/* Log level strings, useful here, if you want to modify them. */
static const char *log_level[] = {
	"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

void log_print(struct log *log, int type, const char *file, int line,
	       const char *fmt, ...)
{
	va_list list;
	const char *color;
	time_t ti;
	struct tm *tm;

	color = "";
	va_start(list, fmt);

	/* If ENABLE_COLOR flag is defined, enable all
	   the possible colors. */
#ifdef WITH_COLORS
	switch (type) {
	case TRACE:
		/* Color style: trace */
		color = log->trace_color;
		if (color == NULL)
			color = TRACE_COLOR;
	        break;
		
	case DEBUG:
		/* Color style: debug */
		color = log->debug_color;
		if (color == NULL)
			color = DEBUG_COLOR;
		break;

	case INFO:
		/* Color style: info */
		color = log->info_color;
		if (color == NULL)
			color = INFO_COLOR;
		break;

	case WARN:
		/* Color style: warn */
		color = log->info_color;
		if (color == NULL)
			color = WARN_COLOR;
		break;

	case ERROR:
		/* Color style: error */
		color = log->error_color;
		if (color == NULL)
			color = ERROR_COLOR;
		break;

	case FATAL:
		/* Color style: fatal */
		color = log->fatal_color;
		if (color == NULL)
			color = FATAL_COLOR;
		break;

	default:
		/* Ignore. */
		break;
	}
#endif

	/* This is the default, without colors. */

	if (log->show_time) {
		/* Ignore possible errors, it's _unlikely_ that
		   an error will happen to query time. */
		ti = time(NULL);
		tm = localtime(&ti);
		fprintf(stderr, "* %s%s%s\t%02d:%02d:%02d -> %s:%02d: ",
			color, log_level[type], END_COLOR,
			tm->tm_hour, tm->tm_min, tm->tm_sec, file, line);
        } else {
		fprintf(stderr, "* %s%s%s\t-> %s:%02d: ",
			color, log_level[type], END_COLOR, file, line);
	}

	vfprintf(stderr, fmt, list);
	va_end(list);
}
