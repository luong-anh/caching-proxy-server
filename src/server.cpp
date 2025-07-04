#include <iostream>

int main(int argc, char* argv[]) {
    const std::vector<std::string> args(argv + 1, argv + argc);
    // Usage:
    //  ./caching-proxy-server --port 3000 --origin http://localhost:4000
    //  ./caching-proxy-server --clear-cache
    int port = 0;
    std::string origin;
    bool clear_cache = false;

    for (size_t i = 0; i < args.size(); i++) {
        const std::string& arg = args[i];
        if (arg == "--port" && i + 1 < args.size()) {
            port = std::stoi(args[++i]);
        } else if (arg == "--origin" && i + 1 < args.size()) {
            origin = args[++i];
        } else if (arg == "--clear-cache") {
            clear_cache = true;
        } else {
            std::cerr << "Unknown or incomplete argument: " << arg << "\n";
            std::cout << "Usage:\n";
            std::cout << "\t./caching-proxy-server --port <PORT> --origin <URL>\n";
            std::cout << "\t./caching-proxy-server --clear-cache\n";
            return 1;
        }
    }

    if (clear_cache) {
        std::cout << "Clearing cache\n";
        return 0;
    }

    if (port == 0 || origin.empty()) {
        std::cerr << "Missing required arguments.\n";
        std::cout << "Usage:\n";
        std::cout << "\t./caching-proxy-server --port <PORT> --origin <URL>\n";
        return 1;
    }

    std::cout << "Starting proxy server on port " << port << " with origin " << origin << "\n";
    return 0;
}
