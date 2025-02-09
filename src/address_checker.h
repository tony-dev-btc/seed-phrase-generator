#pragma once


#include <string>
#include <vector>

#include <Windows.h>
#include <Winineti.h>
#include <WinSock2.h>

#include <json/json.h>

#pragma comment (lib, "Wininet.lib")
#pragma comment (lib, "jsoncpp.lib")

#define CHECKER_ERROR_FAILED 1
#define CHECKER_ERROR_BUSY 2
#define CHECKER_ERROR_BANNED 3
#define CHECKER_ERROR_UNKNOWN 4

#define WAL_TYPE_BTC 0
#define WAL_TYPE_EVM 1


struct wallet_data {
    std::string address;
    int type;
    float btc_amount;  
    float eth_amount;
    float bnb_amount;
    float matic_amount;
};


class wallet_checker {
public:
    bool initialize();

    wallet_data get_wallet_data(std::string address, int type);

private:
    bool check_connection();
    json request_btc_balance(std::string address);
    json request_eth_balance(std::string address);
    json request_bnb_balance(std::string address);
    json request_matic_balance(std::string address);
};


namespace binance_api {
    float get_btc_udst_price();
    float get_eth_usdt_price();
    float get_bnb_usdt_price();
    float get_matic_usdt_price();
}