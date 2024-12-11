#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

#include "common/string/string.h"
#include "common/logging/logging.h"

namespace {

AOC::String AppendRunFilePath(const AOC::String& inputFilePath) {
  const AOC::String runfilesPath = "src/2024/day4/";

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

// Brute Force Search
int search(const std::vector<std::string> &wordsearchMat) {
  AOC::String targetStr = "XMAS";
  int found = 0;

  const int height = wordsearchMat.size();
  const int width = wordsearchMat[0].length();

  for (int rowIdx = 0; rowIdx < height; rowIdx++) {
    for (int colIdx = 0; colIdx < width; colIdx++) {

      // Forwards
      for (int i = 0; i < targetStr.length(); i++) {
        if (colIdx + i < width && wordsearchMat[rowIdx][colIdx + i] == targetStr[i]) {
          if (i == targetStr.length() - 1) {
            found++;
          }
          continue;
        }

        break;
      }

      // Backwards
      for (int i = 0; i < targetStr.length(); i++) {
        if (colIdx + i < width && wordsearchMat[rowIdx][colIdx + i] == targetStr[targetStr.length() - 1 - i]) {
          if (i == targetStr.length() - 1) {
            found++;
          }
          continue;
        }

        break;
      }
      
      // Up
      for (int i = 0; i < targetStr.length(); i++) {
        if (rowIdx + i < height && wordsearchMat[rowIdx + i][colIdx] == targetStr[targetStr.length() - 1 - i]) {
          if (i == targetStr.length() - 1) {
            found++;
          }
          continue;
        }

        break;
      }

      // Down
      for (int i = 0; i < targetStr.length(); i++) {
        if (rowIdx + i < height && wordsearchMat[rowIdx + i][colIdx] == targetStr[i]) {
          if (i == targetStr.length() - 1) {
            found++;
          }
          continue;
        }

        break;
      }

      // Diagonal: Down / Right 
      for (int i = 0; i < targetStr.length(); i++) {
        if (rowIdx + i < height && colIdx + i < width && wordsearchMat[rowIdx + i][colIdx + i] == targetStr[i]) {
          if (i == targetStr.length() - 1) {
            found++;
          }
          continue;
        }

        break;
      }

      // Diagonal: Down / Left 
      for (int i = 0; i < targetStr.length(); i++) {
        if (rowIdx + i < height && colIdx - i >= 0 && wordsearchMat[rowIdx + i][colIdx - i] == targetStr[i]) {
          if (i == targetStr.length() - 1) {
            found++;
          }
          continue;
        }

        break;
      }

      // Diagonal: Up / Left 
      for (int i = 0; i < targetStr.length(); i++) {
        if (rowIdx - i >= 0 && colIdx - i >= 0 && wordsearchMat[rowIdx - i][colIdx - i] == targetStr[i]) {
          if (i == targetStr.length() - 1) {
            found++;
          }
          continue;
        }

        break;
      }

      // Diagonal: Up / Right 
      for (int i = 0; i < targetStr.length(); i++) {
        if (rowIdx - i >= 0 && colIdx + i < width && wordsearchMat[rowIdx - i][colIdx + i] == targetStr[i]) {
          if (i == targetStr.length() - 1) {
            found++;
          }
          continue;
        }

        break;
      }
    }
  }

  return found;
}

}

// https://adventofcode.com/2024/day/1
int main() {
  const char* inputFilePath = "input.txt";

  // Find how many times XMAS appears in the wordsearch.
  // Forwards, backwards, up, down, diagonals + backwards diagonals.
  int totalXmas = 0;

  AOC::Log("Opening file ", inputFilePath);
  std::ifstream inputFile = readFileToStream(inputFilePath);
  
  AOC::Log("Parsing File Contents and constructing matrix");
  AOC::String line;
  std::vector<std::string> wordsearchMat;
  while (std::getline(inputFile, line)) {
    wordsearchMat.push_back(line);
  }

  AOC::Log("Searching for 'XMAS'");
  totalXmas = search(wordsearchMat);

  AOC::Log("Part 1 - The total number of XMAS in the wordsearch: ", totalXmas);

  return 0;
}
