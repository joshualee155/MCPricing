cmake_minimum_required(VERSION 3.6)
project(MCPricing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB MCPricing_SRC
        "*.cpp"
)

add_executable(MCPricing ${MCPricing_SRC})