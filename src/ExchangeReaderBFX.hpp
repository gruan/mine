/**
 * ExchangeReaderBFX is responsible for reading exchange data from
 * the Bitfinex API.
 */

#pragma once

#include <boost/optional.hpp>
#include <cpprest/ws_client.h>
#include <string>

using namespace web;
using namespace web::websockets::client;

enum CurrencyPairEnum;

class ExchangeReaderBFX {
  public:
    ExchangeReaderBFX();
    ~ExchangeReaderBFX() noexcept;

  protected:
    static boost::optional<std::string> getMaybeBFXPairFromCurrencyPair(
      const CurrencyPairEnum& pair
    );

    websocket_callback_client m_client;
    pplx::task<void> m_connectTask;
};
