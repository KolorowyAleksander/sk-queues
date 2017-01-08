#include <SimpleLogger.h>
#include <date.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <string>

using namespace date;

namespace logger {

std::string _logFileName = "mailbox.log";

Log log(_logFileName);

Log::Log(std::string filename) {
  logFileName = filename;
  logFile.open(logFileName);
}

Log::~Log() { logFile.close(); }

void Log::debug(std::string message) {
  auto now = std::chrono::high_resolution_clock::now();
  lock.lock();
  std::cout << "[DEBUG] " << now << " " << message << std::endl;
  logFile << "[DEBUG] " << now << " " << message << std::endl;
  lock.unlock();
}

void Log::error(std::string message) {
  auto now = std::chrono::high_resolution_clock::now();
  lock.lock();
  std::cerr << "\033[1;31m"
            << "[ERROR] " << now << " " << message << "\033[0m" << std::endl;
  logFile << "[ERROR] " << now << " " << message << std::endl;
  lock.unlock();
}
}