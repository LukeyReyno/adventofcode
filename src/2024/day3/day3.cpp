#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

#include "common/string/string.h"
#include "common/logging/logging.h"

namespace {

AOC::String AppendRunFilePath(const AOC::String &inputFilePath) {
  const AOC::String runfilesPath = "src/2024/day3/";

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

int parseComputeMul(const AOC::String &line) {
  const AOC::String delimiter = "mul";
  const AOC::String maxExample = "(XXX,YYY)";

  const int expectedNumMulInputs = 2;

  size_t posStart = 0, i, delimLen = delimiter.length();
  AOC::String token;
  
  int totalMul = 0;

  while ((i = line.find(delimiter, posStart)) != AOC::String::npos) {
    token = line.substr(i + delimLen, maxExample.length());
    posStart = i + delimLen;
    if (token.size() == 0) {
      continue;
    }

    // At this point we should have a token that comes right after "mul"
    // Ideally, it'll look something like (X,Y)
    if (token[0] != '(') {
      continue;
    }

    size_t j;
    if ((j = token.find(")")) == AOC::String::npos) {
      continue;
    }

    // Remove paranthesis, then try to comma split the string
    const AOC::String numsStr = token.substr(1, j - 1);
    const auto nums = numsStr.split(",");

    if (nums.size() != expectedNumMulInputs) {
      continue;
    }

    try {
      const int x = std::stoi(nums[0]);
      const int y = std::stoi(nums[1]);
      totalMul += x * y;
    } catch (const std::runtime_error& e) {
      // One of the values is not a decimal int
      continue;
    }
  }

  return totalMul;
}

std::pair<int, bool> parseComputeMul2(const AOC::String &line, bool isDoing) {
  const AOC::String mulFuncName = "mul";
  const AOC::String maxExample = "(XXX,YYY)";
  const int expectedNumMulInputs = 2;

  const AOC::String doFunc = "do()";
  const AOC::String dontFunc = "don't()";

  size_t posStart = 0;
  size_t mulIdx = 0, doIdx = 0, dontIdx = 0;
  AOC::String mulToken;

  int totalMul = 0;

  int i = 0;
  while (mulIdx != AOC::String::npos || doIdx != AOC::String::npos || dontIdx != AOC::String::npos) {
    mulIdx = line.find(mulFuncName, posStart);
    doIdx = line.find(doFunc, posStart);
    dontIdx = line.find(dontFunc, posStart);

    if (doIdx < mulIdx && doIdx < dontIdx) {
      posStart = doIdx + doFunc.length();
      isDoing = true;
      continue;
    } else if (dontIdx < mulIdx && dontIdx < doIdx) {
      posStart = dontIdx + dontFunc.length();
      isDoing = false;
      continue;
    }

    // Even if we're not doing the mul, still increment the posStart pointer
    posStart = mulIdx + mulFuncName.length();
    if (!isDoing) {
      continue;
    }

    mulToken = line.substr(mulIdx + mulFuncName.length(), maxExample.length());
    if (mulToken.size() == 0) {
      continue;
    }

    // At this point we should have a mulToken that comes right after "mul"
    // Ideally, it'll look something like (X,Y)
    if (mulToken[0] != '(') {
      continue;
    }

    size_t j;
    if ((j = mulToken.find(")")) == AOC::String::npos) {
      continue;
    }

    // Remove paranthesis, then try to comma split the string
    const AOC::String numsStr = mulToken.substr(1, j - 1);
    const auto nums = numsStr.split(",");

    if (nums.size() != expectedNumMulInputs) {
      continue;
    }

    try {
      const int x = std::stoi(nums[0]);
      const int y = std::stoi(nums[1]);
      totalMul += x * y;
    } catch (const std::runtime_error& e) {
      // One of the values is not a decimal int
      continue;
    }
  }

  return {totalMul, isDoing};
}

}

// https://adventofcode.com/2024/day/1
int main() {
  const char* inputFilePath = "input.txt";

  // Find the sum of products from valid "mul(X,Y)" calls
  int totalMul1 = 0;

  // Find the sum of products from valid "mul(X,Y)" calls with do and don't
  int totalMul2 = 0;

  AOC::Log("Opening file ", inputFilePath);
  std::ifstream inputFile = readFileToStream(inputFilePath);

  AOC::Log("Parsing File Contents and Calculating ");
  AOC::String line;
  bool isDoing = true;
  while (std::getline(inputFile, line)) {
    totalMul1 += parseComputeMul(line);

    const auto val = parseComputeMul2(line, isDoing);
    totalMul2 += val.first;
    isDoing = val.second;
  }

  AOC::Log("Part1: The total mul value is: ", totalMul1);
  AOC::Log("Part2: The total mul value is: ", totalMul2);

  return 0;
}
