#pragma once

#include <chrono>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <utility>

namespace AOC {

enum LogLevel {
  ERROR,
  WARNING,
  INFO,
  DEBUG,
};

} // namespace AOC

namespace {

  const char* LogLevelToString(AOC::LogLevel level) {
    switch (level) {
      case AOC::ERROR:
        return "ERROR";
      case AOC::WARNING:
        return "WARNING";
      case AOC::INFO:
        return "INFO";
      case AOC::DEBUG:
        return "DEBUG";
      default:
        return "UNKNOWN";
    }
}

std::ostream& GetOStream(AOC::LogLevel level) {
  switch (level) {
    case AOC::ERROR:
    case AOC::WARNING:
      return std::cerr;
    case AOC::INFO:
    case AOC::DEBUG:
    default:
      return std::cout;
  }
}

std::string GetTimestamp() {
  auto now = std::chrono::system_clock::now();
  auto now_time_t = std::chrono::system_clock::to_time_t(now);

  std::stringstream ss;
  ss << std::ctime(&now_time_t);  // Get current time in a readable format
  std::string timestamp = ss.str();
  timestamp.pop_back();  // Remove trailing newline from ctime

  return timestamp;
}

template <typename T, typename... Args>
void FormatMessage(std::stringstream& logMessage, const T& message, Args &&...args) {
  logMessage << message;
  (void)(logMessage << ... << args);
}

} // namespace

namespace AOC {

template <typename... Args>
void Log(LogLevel level, const char* message, Args &&...args) {
  const char* logLevelString = LogLevelToString(level);

  std::ostream& ostream = GetOStream(level);

  std::string timestamp = GetTimestamp();
  std::stringstream logMessage;
  logMessage << "[" << timestamp << "][" << logLevelString << "]: ";

  FormatMessage(logMessage, message, std::forward<Args>(args)...);

  ostream << logMessage.str() << std::endl;
}

template <typename... Args>
void Log(const char* message, Args &&...args) {
  Log(LogLevel::INFO, message, args...);
}

} // namespace AOC
