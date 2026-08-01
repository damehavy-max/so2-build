cmake_minimum_required(VERSION 3.15)
project(MarketEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TOOLCHAIN_FILE "C:/Users/dameh/Documents/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Protobuf REQUIRED)

# Создаем именно библиотеку (DLL), а не EXE
add_library(market_engine SHARED market_engine.cpp messages.pb.cc)

target_link_libraries(market_engine PRIVATE 
    Boost::boost
    OpenSSL::SSL
    protobuf::libprotobuf
)
