#include <iostream>
#include <thread>
#include <gtest/gtest.h>

TEST(OriginServer, StartsUp) {
    std::system("./mock_server &");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Tear down
    std::system("pkill -f ./mock_server");
}
