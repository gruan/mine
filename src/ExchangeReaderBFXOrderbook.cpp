#include <cpprest/json.h>
#include <cpprest/ws_client.h>
#include <iostream>
#include <string>

#include "CurrencyPairEnum.hpp"
#include "ExchangeReaderBFXOrderbook.hpp"

ExchangeReaderBFXOrderbook::ExchangeReaderBFXOrderbook()
  : ExchangeReaderBFX()
{
  this->m_client.set_message_handler([](websocket_incoming_message msg) {
    msg.extract_string()
      .then([](std::string body) {
        std::cout << body << std::endl;
      });
  });
}

void ExchangeReaderBFXOrderbook::subscribe(
  const CurrencyPairEnum& pair,
  const std::string& precision,
  const std::string& frequency
)
{
  auto maybePair = ExchangeReaderBFX::getMaybeBFXPairFromCurrencyPair(pair);
  if (!maybePair) {
    std::cerr << "`pair` is an unsupported BFX currency pair." << std::endl;
    return;
  }

  if (!ExchangeReaderBFXOrderbook::isValidPrecision(precision)) {
    std::cerr
      << "BFX orderbook channel does not support the precision: "
      << precision
      << std::endl;
    return;
  }

  if (!ExchangeReaderBFXOrderbook::isValidFrequency(frequency)) {
    std::cerr
      << "BFX orderbook channel does not support the frequency: "
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

bool ExchangeReaderBFXOrderbook::isValidPrecision(const std::string& precision)
{
  return precision == "P0"
    || precision == "P1"
    || precision == "P2"
    || precision == "P3";
}

bool ExchangeReaderBFXOrderbook::isValidFrequency(const std::string& frequency)
{
  return frequency == "F0"
    || frequency == "F1"
    || frequency == "F2"
    || frequency == "F3";
}
