#include <string>

namespace AOC {

class String : public std::string {
  public:
    // Inherit std::string constructors
    using std::string::string;

    // Add a constructor to handle std::string
    String(const std::string& other) : std::string(other) {}

    // Add an assignment operator to handle std::string
    String& operator=(const std::string& other) {
      std::string::operator=(other); // Use base class assignment operator
      return *this;
    }

    // Add an assignment operator to handle const char* if needed
    String& operator=(const char* other) {
      std::string::operator=(other);
      return *this;
    }

    std::vector<String> split(const String& delimiter);
};

} // namespace AOC
