#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

#include "common/string/string.h"
#include "common/logging/logging.h"

namespace {

AOC::String AppendRunFilePath(const AOC::String &inputFilePath) {
  const AOC::String runfilesPath = "src/2024/day2/";

  return runfilesPath + inputFilePath;
}

std::ifstream readFileToStream(const AOC::String &inputFilePath) {
  std::ifstream inputFile(AppendRunFilePath(inputFilePath));

  if (!inputFile) {
    AOC::Log(AOC::LogLevel::ERROR, "Error opening file: ", inputFilePath);
    std::exit(1);
  }

  return inputFile;
}

int determineSafety1(const std::vector<AOC::String> &reports) {
  const int first = std::stoi(reports[0]);
  const int second = std::stoi(reports[1]);
  const bool expectIncreasing = (first < second) ? true : false;
  for (int i = 0; i < reports.size() - 1; i++) {
    int left = std::stoi(reports[i]);
    int right = std::stoi(reports[i + 1]);

    int diff = left - right;
    if (!((expectIncreasing && (-3 <= diff && diff <= -1)) ||
      (!expectIncreasing && (1 <= diff && diff <= 3)))) {
      return 0;
    }
  }

  return 1;
}

int determineSafety2(const std::vector<AOC::String> &reports) {
  // Make a mutable deep copy of the reports
  std::vector<AOC::String> reportsCopy = reports;

  const int first = std::stoi(reportsCopy[0]);
  const int second = std::stoi(reportsCopy[1]);

  bool expectIncreasing = (first < second) ? true : false;
  for (int i = 0; i < reportsCopy.size() - 1; i++) {
    int left = std::stoi(reportsCopy[i]);
    int right = std::stoi(reportsCopy[i + 1]);

    int diff = left - right;
    if (!((expectIncreasing && (-3 <= diff && diff <= -1)) ||
      (!expectIncreasing && (1 <= diff && diff <= 3)))) {

      // Check if deleting first element works; expectIncreasing may change
      if (i == 1) {
        reportsCopy.erase(reportsCopy.begin());
        if (determineSafety1(reportsCopy)) {
          return 1;
        }

        // Restore reportsCopy
        reportsCopy.insert(reportsCopy.begin(), reports[0]);
      }

      // Check if deleting left element works
      reportsCopy.erase(reportsCopy.begin() + i);

      if (determineSafety1(reportsCopy)) {
        return 1;
      }

      // Check if deleting right element works
      // Reinsert original left value (string), then delete right
      reportsCopy.insert(reportsCopy.begin() + i, reports[i]);
      reportsCopy.erase(reportsCopy.begin() + (i + 1));
      if (determineSafety1(reportsCopy)) {
        return 1;
      }

      return 0;
    }
  }

  return 1;
}

}

// https://adventofcode.com/2024/day/1
int main() {
  const char* inputFilePath = "input.txt";

  // Find the total safe reports (strict increase / decrease order by 1, 2, or 3)
  int totalSafe1 = 0;

  // Find the total safe reports (strict increase / decrease order by 1, 2, or 3), possibly off by one
  int totalSafe2 = 0;

  AOC::Log("Opening file ", inputFilePath);
  std::ifstream inputFile = readFileToStream(inputFilePath);
  
  AOC::Log("Parsing File Contents and Determining Safety");
  AOC::String line;
  while (std::getline(inputFile, line)) {
    const auto getLineNums = line.split(" ");
    totalSafe1 += determineSafety1(getLineNums);
    totalSafe2 += determineSafety2(getLineNums);
  }

  AOC::Log("Part1: The total safe reports is: ", totalSafe1);
  AOC::Log("Part2: The total safe reports is: ", totalSafe2);

  return 0;
}
