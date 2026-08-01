#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "messages.pb.h"

#define EXPORT extern "C" __declspec(dllexport)

using boost::asio::ip::tcp;

struct Target {
    int id;
    double max_price;
};

std::vector<Target> targets;
std::atomic<bool> is_running(false);

// Глобальные объекты сети
boost::asio::io_context io_ctx;
boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tlsv12);
std::unique_ptr<boost::asio::ssl::stream<tcp::socket>> game_socket;

EXPORT bool connect_to_server(const char* handshake) {
    try {
        tcp::resolver resolver(io_ctx);
        auto endpoints = resolver.resolve("server.boltgaming.io", "2223");
        game_socket = std::make_unique<boost::asio::ssl::stream<tcp::socket>>(io_ctx, ssl_ctx);
        boost::asio::connect(game_socket->lowest_layer(), endpoints);
        boost::asio::ip::tcp::no_delay option(true);
        game_socket->lowest_layer().set_option(option);
        game_socket->handshake(boost::asio::ssl::stream_base::client);
        return true;
    } catch (...) { return false; }
}

EXPORT void clear_targets() { targets.clear(); }
EXPORT void add_target(int id, double price) { targets.push_back({id, price}); }

EXPORT void run_sniper_multi() {
    if (is_running) return;
    is_running = true;
    std::thread([]() {
        while (is_running) {
            for (auto& t : targets) {
                if (!is_running) break;
                // Здесь будет сверхбыстрая проверка цены через сокет
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }).detach();
}

EXPORT void stop_sniper() { is_running = false; }