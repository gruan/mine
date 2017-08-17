#include <cpprest/json.h>
#include <cpprest/ws_client.h>

#include "CurrencyPairEnum.hpp"
#include "ExchangeReaderBFX.hpp"

using namespace web;
using namespace web::websockets::client;

const std::string BFX_WS_URI = "wss://api.bitfinex.com/ws";

ExchangeReaderBFX::ExchangeReaderBFX()
{
  this->m_connectTask = this->m_client.connect(U(BFX_WS_URI));
}

ExchangeReaderBFX::~ExchangeReaderBFX() noexcept
{
  this->m_client.close();
}

boost::optional<std::string> ExchangeReaderBFX::getMaybeBFXPairFromCurrencyPair(
  const CurrencyPairEnum& pair
)
{
  switch (pair) {
    case BTCUSD:
      return std::string("BTCUSD");
    case ETHBTC:
      return std::string("ETHBTC");
    case ETHUSD:
      return std::string("ETHUSD");
    case LTCBTC:
      return std::string("LTCBTC");
    case LTCUSD:
      return std::string("LTCUSD");
    default:
      return boost::optional<std::string>();
  }
}
