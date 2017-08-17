cmake_minimum_required(VERSION 3.9)
project(mine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

# Needed since Apple got rid of the native OpenSSL header files.
# This is used to link against HomeBrew's OpenSSL header files.
set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)

find_library(CPPREST_LIB NAMES cpprest_2_9d cpprest_2_9 cpprestd cpprest)
find_package(Boost REQUIRED COMPONENTS
  atomic
  chrono
  date_time
  filesystem
  random
  regex
  system
  thread
)
find_package(OpenSSL 1.0.0 REQUIRED)

set(SOURCE_FILES
  main.cpp
  ConfigStore.cpp
  ExchangeReaderBFX.cpp
  ExchangeReaderBFXOrderbook.cpp
)

add_executable(mine ${SOURCE_FILES})
target_link_libraries(mine
  ${CPPREST_LIB}
  Boost::atomic
  Boost::boost
  Boost::chrono
  Boost::date_time
  Boost::filesystem
  Boost::random
  Boost::regex
  Boost::system
  Boost::thread
  OpenSSL::SSL
)
