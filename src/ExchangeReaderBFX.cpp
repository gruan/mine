#include <cpprest/json.h>
#include <cpprest/ws_client.h>
#include <iostream>

#include "ExchangeReaderBFX.hpp"

using namespace web;
using namespace web::websockets::client;

const std::string BFX_WS_URI = "wss://api.bitfinex.com/ws";

ExchangeReaderBFX::ExchangeReaderBFX()
{
  this->m_connectTask = this->m_client.connect(U(BFX_WS_URI));

  this->m_client.set_message_handler([](websocket_incoming_message msg) {
    msg.extract_string()
      .then([](std::string body) {
        std::cout << body << std::endl;
      });
  });
}

ExchangeReaderBFX::~ExchangeReaderBFX() noexcept
{
  this->m_client.close();
}

void ExchangeReaderBFX::subscribeToOrderbookChannel(
  CurrencyPairEnum pair,
  std::string precision,
  std::string frequency
)
{
  auto maybePair = ExchangeReaderBFX::getMaybeBFXPairFromCurrencyPair(pair);
  if (!maybePair) {
    std::cerr << "`pair` is an unsupported BFX currency pair." << std::endl;
    return;
  }

  if (!ExchangeReaderBFX::isValidOrderbookPrecision(precision)) {
    std::cerr
      << "BFX does not support the precision: "
      << precision
      << std::endl;
    return;
  }

  if (!ExchangeReaderBFX::isValidOrderbookFrequency(frequency)) {
    std::cerr
      << "BFX does not support the frequency: "
      << frequency
      << std::endl;
  }

  // We need to make sure that the websocket client is actually connected.
  this->m_connectTask.wait();

  json::value msgJSON = json::value::object();
  msgJSON["event"] = json::value::string("subscribe");
  msgJSON["channel"] = json::value::string("book");
  msgJSON["pair"] = json::value::string(maybePair.value());
  msgJSON["prec"] = json::value::string(precision);
  msgJSON["freq"] = json::value::string(frequency);

  websocket_outgoing_message msg;
  msg.set_utf8_message(msgJSON.serialize());
  this->m_client.send(msg);
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

bool ExchangeReaderBFX::isValidOrderbookPrecision(const std::string& precision)
{
  return precision == "P0"
    || precision == "P1"
    || precision == "P2"
    || precision == "P3";
}

bool ExchangeReaderBFX::isValidOrderbookFrequency(const std::string& frequency)
{
  return frequency == "F0"
    || frequency == "F1"
    || frequency == "F2"
    || frequency == "F3";
}
