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

enum XPattern {
  DOWN,
  RIGHT,
  UP,
  LEFT,
};

std::vector<int> getPatternIndices(XPattern pattern, int rowIdx, int colIdx, int targetLen, int i) {
  switch (pattern) {
    case DOWN:
      return {
            rowIdx + i,
            colIdx + i,
            rowIdx + i,
            colIdx - i + (targetLen - 1)
          };
    case RIGHT:
      return {
            rowIdx + i,
            colIdx + i,
            rowIdx - i + (targetLen - 1),
            colIdx + i
          };
    case UP:
      return {
            rowIdx - i + (targetLen - 1),
            colIdx - i + (targetLen - 1),
            rowIdx - i + (targetLen - 1),
            colIdx + i
          };
    case LEFT:
      return {
            rowIdx + i,
            colIdx - i + (targetLen - 1),
            rowIdx - i + (targetLen - 1),
            colIdx - i + (targetLen - 1),
          };
  }
}

int search2(const std::vector<std::string> &wordsearchMat) {
  AOC::String targetStr = "MAS";
  int found = 0;

  const int height = wordsearchMat.size();
  const int width = wordsearchMat[0].length();

  const std::vector<XPattern> patterns = {DOWN, RIGHT, UP, LEFT};

  for (int rowIdx = 0; rowIdx < height; rowIdx++) {
    for (int colIdx = 0; colIdx < width; colIdx++) {
      for (int j = 0; j < patterns.size(); j++) {
        for (int i = 0; i < targetStr.length(); i++) {
          const std::vector<int> diagIndices = getPatternIndices(patterns[j], rowIdx, colIdx, targetStr.length(), i);
          const int diag1RowIdx = diagIndices[0];
          const int diag1ColIdx = diagIndices[1];
          const int diag2RowIdx = diagIndices[2];
          const int diag2ColIdx = diagIndices[3];
          if ((0 <= diag1RowIdx && diag1RowIdx < height) && (0 <= diag2RowIdx && diag2RowIdx < height) &&
            (0 <= diag1ColIdx && diag1ColIdx < width) && (0 <= diag2ColIdx && diag2ColIdx < width) &&
            wordsearchMat[diag1RowIdx][diag1ColIdx] == targetStr[i] &&
            wordsearchMat[diag2RowIdx][diag2ColIdx] == targetStr[i]) {
            if (i == targetStr.length() - 1) {
              found++;
            }
            continue;
          }

          break;
        }
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

  // Find how many times MAS is in an X (cross)
  int totalXmas2 = 0;

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
  totalXmas2 = search2(wordsearchMat);

  AOC::Log("Part 1 - The total number of XMAS in the wordsearch: ", totalXmas);
  AOC::Log("Part 2 - The total number of X-MAS in the wordsearch: ", totalXmas2);

  return 0;
}
