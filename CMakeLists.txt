cmake_minimum_required(VERSION 3.15)
project(caching_proxy_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add your main executable
add_executable(caching-proxy-server
    src/server.cpp
)
target_include_directories(caching-proxy-server PRIVATE src)

# Add GoogleTest submodule
add_subdirectory(third_party/googletest)

enable_testing()

# Add your test executable
add_executable(tests
    tests/test.cpp
)
target_include_directories(tests PRIVATE src)
target_link_libraries(tests
    gtest
    gtest_main
)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(tests)
