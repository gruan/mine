#include <boost/optional.hpp>
#include <fstream>
#include <iostream>

#include "ConfigStore.hpp"

const std::string ALPHA_VANTAGE_API_KEY = "alpha_vantage_api_key";

int main() {
  std::ifstream input("config.txt");
  ConfigStore& config = ConfigStore::get();
  config.parseFile(input);
  auto maybeVal = config.getMaybeValue(std::string(ALPHA_VANTAGE_API_KEY));

  if (maybeVal->empty()) {
    std::cerr << "Config key: "
      << ALPHA_VANTAGE_API_KEY
      << "not found."
      << std::endl;
    return 1;
  }
  std::cout << maybeVal.value()<< std::endl;

  return 0;
}
