# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(algorithmic_trading)

set(CMAKE_CXX_STANDARD 14)

add_executable(algorithmic_trading
    src/Order.cpp
    src/OrderDetails.cpp
    src/LimitOrderDetails.cpp
    src/OrderBook.cpp
    src/main.cpp
)

target_include_directories(algorithmic_trading PRIVATE include)
