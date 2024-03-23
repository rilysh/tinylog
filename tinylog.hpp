#pragma once

/* Basic compile-time checks. */
#ifndef __cplusplus
# error standard library does not define __cplusplus macro.
#endif
#if __cplusplus < 202002L
# error "log header file requires that your compiler \
support C++20 or above."
#endif

#include <cinttypes>
#include <string>
#include <array>
#include <ctime>
#include <fmt/core.h>
#include <source_location>
#include <type_traits>

enum TinyLogLevel {
  LVL_TRACE = 0,
  LVL_DEBUG = 1,
  LVL_INFO = 2,
  LVL_WARN = 3,
  LVL_ERROR = 4,
  LVL_FATAL = 5,
};

class TinyLog {
  const char *trace_color;
  const char *debug_color;
  const char *info_color;
  const char *warn_color;
  const char *error_color;
  const char *fatal_color;
  static constexpr std::array<const char *, 6> log_levels = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
  };
  static constexpr std::array<const char *, 7> log_colors = {
    "\x1b[0;37m", "\x1b[0;33m", "\x1b[0;92m", "\x1b[0;31m",
    "\x1b[0;91m", "\x1b[1;91m", "\x1b[0m" };
  bool show_time;

public:
  /* Explicitly initialize the class members. */
  TinyLog() = default;

  /* Override the default color of trace. */
  inline void
  log_set_trace_color(const char *color)
  {
    this->trace_color = color;
  }

  /* Override the default color of void. */
  inline void
  log_set_debug_color(const char *color)
  {
    this->debug_color = color;
  }

  /* Override the default color of info. */
  inline void
  log_set_info_color(const char *color)
  {
    this->info_color = color;
  }

  /* Override the default color of warn. */
  inline void
  log_set_warn_color(const char *color)
  {
    this->warn_color = color;
  }

  /* Override the default color of error. */
  inline void
  log_set_error_color(const char *color)
  {
    this->error_color = color;
  }

  /* Override the default color of fatal. */
  inline void
  log_set_fatal_color(const char *color)
  {
    this->fatal_color = color;
  }

  /* Override the default show_time boolean. */
  inline void
  log_enable_time(bool is_ok)
  {
    this->show_time = is_ok;
  }

  /* Print the log (arguments) with additional arguments. */
  template <typename Ty, typename... Args>
  requires requires (Ty t) { requires std::is_same_v<Ty, std::uint32_t>; }
  void
  log_print(std::int32_t type, const std::string& file_name, Ty line,
	    fmt::format_string<Args...> fmt, [[maybe_unused]] Args&&... args)
  {
    auto color = "";

#ifdef WITH_COLORS
    switch (type) {
    case TinyLogLevel::LVL_TRACE:
      /* Loglevel is: trace. */
      color = trace_color;
      if (!color)
	color = this->log_colors[type];
      break;

    case TinyLogLevel::LVL_DEBUG:
      /* Loglevel is: debug. */
      color = debug_color;
      if (!color)
	color = this->log_colors[type];
      break;

    case TinyLogLevel::LVL_INFO:
      /* Loglevel is: info. */
      color = info_color;
      if (!color)
	color = this->log_colors[type];
      break;

    case TinyLogLevel::LVL_WARN:
      /* Loglevel is: warn. */
      color = warn_color;
      if (!color)
	color = this->log_colors[type];
      break;

    case TinyLogLevel::LVL_ERROR:
      /* Loglevel is: error. */
      color = error_color;
      if (!color)
	color = this->log_colors[type];
      break;

    case TinyLogLevel::LVL_FATAL:
      /* Loglevel is: fatal. */
      color = fatal_color;
      if (!color)
	color = this->log_colors[type];
      break;

    default:
      break;
    }
#endif
    
    if (show_time) {
      const auto tm = std::time(nullptr);
      struct tm *ltm = std::localtime(&tm);

      fmt::print("* {}{}{}\t{}:{}:{:02d} -> {}:{:02d}: ", color,
		 log_levels[type], this->log_colors[6],
		 ltm->tm_hour, ltm->tm_min, ltm->tm_sec,
		 file_name, line);
    } else {
      fmt::print("* {}{}{}\t-> {}:{:02d}: ", color, log_levels[type],
		 this->log_colors[6], file_name, line);
    }
    fmt::print(
      fmt::runtime(fmt), std::forward<Args>(args)...);
  }

  /* Return the current line. */
  constexpr std::uint32_t
  current_line(const std::source_location& at =
	       std::source_location::current())
  {
    return at.line();
  }

  /* Return the current file. */
  constexpr const char *
  current_file(const std::source_location& at =
	       std::source_location::current())
  {
    return at.file_name();
  }

  /* log_trace() */
  template <typename Ty, typename... Args>
  requires requires (Ty t) { requires std::is_same_v<Ty, std::uint32_t>; }
  inline void
  log_trace(const std::string& file_name, Ty line,
	    fmt::format_string<Args...> fmt, Args... args)
  {
    log_print(TinyLogLevel::LVL_TRACE, file_name, line,
	      fmt::runtime(fmt), args...);
  }

  /* log_debug() */
  template <typename Ty, typename... Args>
  requires requires (Ty t) { requires std::is_same_v<Ty, std::uint32_t>; }
  inline void
  log_debug(const std::string& file_name, Ty line,
	    fmt::format_string<Args...> fmt, Args... args)
  {
    log_print(TinyLogLevel::LVL_DEBUG, file_name, line,
	      fmt::runtime(fmt), args...);
  }
// TODO: Complete comments and add constraints to log_print()
  /* log_info() */
  template <typename Ty, typename... Args>
  requires requires (Ty t) { requires std::same_as<Ty, std::uint32_t>; }
  inline void
  log_info(const std::string& file_name, Ty line,
	   fmt::format_string<Args...> fmt, Args... args)
  {
    log_print(TinyLogLevel::LVL_INFO, file_name, line,
	      fmt::runtime(fmt), args...);
  }

  /* log_xcape() */
  template <typename Ty, typename... Args>
  requires requires (Ty t) { requires std::is_same_v<Ty, std::uint32_t>; }
  inline void
  log_warn(const std::string& file_name, Ty line,
	   fmt::format_string<Args...> fmt, Args... args)
  {
    log_print(TinyLogLevel::LVL_WARN, file_name, line,
	      fmt::runtime(fmt), args...);
  }

  /* log_error() */
  template <typename Ty, typename... Args>
  requires requires (Ty t) { requires std::is_same_v<Ty, std::uint32_t>; }
  inline void
  log_error(const std::string& file_name, Ty line,
	    fmt::format_string<Args...> fmt, Args... args)
  {
    log_print(TinyLogLevel::LVL_ERROR, file_name, line,
	      fmt::runtime(fmt), args...);
  }

  /* log_fatal() */
  template <typename Ty, typename... Args>
  requires requires (Ty t) { requires std::is_same_v<Ty, std::uint32_t>; }
  inline void
  log_fatal(const std::string& file_name, Ty line,
	    fmt::format_string<Args...> fmt, Args... args)
  {
    log_print(TinyLogLevel::LVL_FATAL, file_name, line,
	      fmt::runtime(fmt), args...);
  }
};
