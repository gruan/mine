/**
 * ExchangeReaderBFXOrderbook is responsible for subscribing to the
 * orderbook channel using the Bitfinex API
 */

#pragma once

#include <string>

#include "ExchangeReaderBFX.hpp"

enum CurrencyPairEnum;

class ExchangeReaderBFXOrderbook: public ExchangeReaderBFX {
  public:
    ExchangeReaderBFXOrderbook();
    void subscribe(
      const CurrencyPairEnum& pair,
      const std::string& precision,
      const std::string& frequency
    );

  private:
    static bool isValidPrecision(const std::string& precision);
    static bool isValidFrequency(const std::string& frequency);
};
