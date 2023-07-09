cmake_minimum_required(VERSION 3.10)
project(exchange_rate)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)

add_executable(exchange_rate main.cpp exchange_rates.cpp)

target_link_libraries(exchange_rate PRIVATE nlohmann_json::nlohmann_json CURL::libcurl)
