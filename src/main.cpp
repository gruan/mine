#include <boost/optional.hpp>
#include <fstream>
#include <iostream>

#include "ConfigStore.hpp"
#include "ExchangeReaderBFX.hpp"

const std::string ALPHA_VANTAGE_API_KEY = "alpha_vantage_api_key";

int main() {
  ExchangeReaderBFX reader;
  reader.subscribeToOrderbookChannel(CurrencyPairEnum::BTCUSD, "P2", "F1");

  std::ifstream input("config.txt");
  ConfigStore& config = ConfigStore::get();
  config.parseFile(input);
  auto maybeVal = config.getMaybeValue(ALPHA_VANTAGE_API_KEY);

  if (!maybeVal) {
    std::cerr << "Config key: "
      << ALPHA_VANTAGE_API_KEY
      << " not found."
      << std::endl;
    return 1;
  }
  std::cout << maybeVal.value()<< std::endl;


  while (true) {};
  return 0;
}
