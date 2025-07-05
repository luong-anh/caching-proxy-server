cmake_minimum_required(VERSION 3.15)
project(caching_proxy_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(http_server STATIC
    tests/http-server/src/HttpRequest.cpp
    tests/http-server/src/HttpResponse.cpp
)
target_include_directories(http_server PUBLIC
    ${CMAKE_SOURCE_DIR}/tests/http-server/include
)

# Add your main executable
add_executable(caching-proxy-server
    src/server.cpp
)
target_include_directories(caching-proxy-server PRIVATE src)

target_link_libraries(caching-proxy-server PRIVATE http_server)
target_include_directories(caching-proxy-server PRIVATE
    ${CMAKE_SOURCE_DIR}/tests/http-server/src
)

add_custom_target(build_origin_server ALL
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/tests/http-server make
    COMMENT "Building HTTP origin server with Makefile"
)

add_custom_command(
  TARGET build_origin_server POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
          ${CMAKE_SOURCE_DIR}/tests/http-server/server
          ${CMAKE_BINARY_DIR}/mock_server
)

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
