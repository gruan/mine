/**
 * ConfigStore is a singleton responsible for reading in config files
 * and providing an API to read values from them.
 */

#pragma once

#include <boost/optional.hpp>
#include <fstream>
#include <string>
#include <unordered_map>

class ConfigStore {
  public:
    static ConfigStore& get();

    void parseFile(std::ifstream& inStream);
    boost::optional<std::string> getMaybeValue(std::string key);

  private:
    ConfigStore();

    std::unordered_map<std::string, std::string> m_storedConfig;
};
