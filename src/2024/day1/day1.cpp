#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

#include "common/string/string.h"
#include "common/logging/logging.h"

namespace {

AOC::String AppendRunFilePath(const AOC::String& inputFilePath) {
  const AOC::String runfilesPath = "src/2024/day1/";

  return runfilesPath + inputFilePath;
}

std::ifstream readFileToStream(const AOC::String& inputFilePath) {
  std::ifstream inputFile(AppendRunFilePath(inputFilePath));

  if (!inputFile) {
    AOC::Log(AOC::LogLevel::ERROR, "Error opening file: ", inputFilePath);
    std::exit(1);
  }

  return inputFile;
}

}

// https://adventofcode.com/2024/day/1
int main() {
  const char* inputFilePath = "input.txt";

  // Find the total distance between each pair of sorted elements
  int totalDistances = 0;

  AOC::Log("Opening file ", inputFilePath);
  std::ifstream inputFile = readFileToStream(inputFilePath);
  
  AOC::Log("Parsing File Contents");
  AOC::String line;
  std::vector<int> listA, listB;
  while (std::getline(inputFile, line)) {
    const auto getLineNum = line.split(" ");
    if (getLineNum.size() != 2) {
      AOC::Log(AOC::LogLevel::ERROR, "Invalid input format: ", line);
      std::exit(1);
    }
    listA.push_back(std::stoi(getLineNum[0]));
    listB.push_back(std::stoi(getLineNum[1]));
  }

  AOC::Log("Sorting Lists");
  std::sort(listA.begin(), listA.end());
  std::sort(listB.begin(), listB.end());

  AOC::Log("Calulating Distances");
  if (listA.size() != listB.size()) {
    AOC::Log(AOC::LogLevel::ERROR, "Parsed lists have different sizes!");
    std::exit(1);
  }

  for (int i = 0; i < listA.size(); i++) {
    totalDistances += std::abs(listA[i] - listB[i]);
  }

  AOC::Log("Part 1 - The total distances value is: ", totalDistances);

  // Sum of each number in the left list after multiplying it by the number of
  // times that number appears in the right list.
  int totalSimilarity = 0;

  AOC::Log("Generating frequency map for list B");
  std::unordered_map<int, int> listBFreq;
  for (int i = 0; i < listB.size(); i++) {
    if (listBFreq.count(listB[i])) {
      listBFreq[listB[i]] += 1;
    } else {
      listBFreq[listB[i]] = 1;
    }
  }

  AOC::Log("Calculating Similarities");
  for (int i = 0; i < listA.size(); i++) {
    totalSimilarity += (listA[i] * listBFreq[listA[i]]);
  }

  AOC::Log("Part 2 - The total similarities value is: ", totalSimilarity);

  return 0;
}
