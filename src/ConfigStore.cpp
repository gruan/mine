#include <boost/optional.hpp>
#include <fstream>
#include <string>
#include <utility>
#include <iostream>

#include "ConfigStore.hpp"

ConfigStore& ConfigStore::get()
{
  static ConfigStore instance;
  return instance;
}

void ConfigStore::parseFile(std::ifstream& inStream)
{
  std::string configKey;
  std::string configValue;
  while (inStream >> configKey  >> configValue) {
    this->m_storedConfig.insert(std::make_pair(configKey, configValue));
  }
}

boost::optional<std::string> ConfigStore::getMaybeValue(std::string key)
{
  auto it = this->m_storedConfig.find(key);
  if (it == this->m_storedConfig.end()) {
    return boost::optional<std::string>();
  }

  return it->second;
}

ConfigStore::ConfigStore()
{}

