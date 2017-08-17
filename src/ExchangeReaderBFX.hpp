/**
 * ExchangeReaderBFX is responsible for reading exchange data from
 * the Bitfinex API.
 */

#pragma once

#include <boost/optional.hpp>
#include <cpprest/ws_client.h>
#include <string>

#include "CurrencyPairEnum.hpp"

using namespace web;
using namespace web::websockets::client;

class ExchangeReaderBFX {
  public:
    ExchangeReaderBFX();
    ~ExchangeReaderBFX() noexcept;

    void subscribeToOrderbookChannel(
      CurrencyPairEnum pair,
      std::string precision,
      std::string frequency
    );

  private:
    static bool isValidOrderbookPrecision(const std::string& precision);
    static bool isValidOrderbookFrequency(const std::string& frequency);
    static boost::optional<std::string> getMaybeBFXPairFromCurrencyPair(
      const CurrencyPairEnum& pair
    );

    websocket_callback_client m_client;
    pplx::task<void> m_connectTask;
};
