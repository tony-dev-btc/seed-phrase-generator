

#include <iostream>

#include <Windows.h>
#include "bip39-words.hpp"
#include "addres_generator.h"
#include "address_checker.h"


std::string save_found_path = "found_wallets.txt";

void set_color(int color = 7) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void print_logo() {
    std::cout << "***************************************************************************\n";
    std::cout << "*__        __    _ _      _    ____                                       *\n";
    std::cout << "*\\ \\      / /_ _| | | ___| |_ / ___| ___ _ __                             *\n";
    std::cout << "* \\ \\ /\\ / / _` | | |/ _ \\ __| |  _ / _ \\ '_ \\                            *\n";
    std::cout << "*  \\ V  V / (_| | | |  __/ |_| |_| |  __/ | | |                           *\n";
    std::cout << "*   \\_/\\_/ \\__,_|_|_|\\___|\\__|\\____|\\___|_| |_|             ____  _       *\n";
    std::cout << "*                  | |__  _   _  |_   _|__  _ __  _   _    | __ )| |_ ___ *\n";
    std::cout << "*                  | '_ \\| | | |   | |/ _ \\| '_ \\| | | |   |  _ \\| __/ __|*\n";
    std::cout << "*                  | |_) | |_| |   | | (_) | | | | |_| |   | |_) | || (__ *\n";
    std::cout << "*                  |_.__/ \\__, |   |_|\\___/|_| |_|\\__, |___|____/ \\__\\___|*\n";
    std::cout << "*                         |___/                   |___/_____|             *\n";
    std::cout << "***************************************************************************\n";
    std::cout << "\n";
}

int show_menu() {
    set_color(9);
 point1:
    std::cout << "================================================================\n";
    std::cout << "'1' - generate one Bitcoin wallet.                             =\n";
    std::cout << "'2' - generate one EVM wallet (ETH, BNB, MATIC e.t.c)          =\n";
    std::cout << "'3' - start searching for Bitoin wallets with balance          =\n";
    std::cout << "'4' - start searching for EVM wallets with balance             =\n";
    std::cout << "'5' - support the developer                                    =\n";
    std::cout << "'6' - exit                                                     =\n";
    std::cout << "================================================================\n";
    set_color();

    std::cout << "select an action using the key: ";

    int action;
    std::cin >> action;
    return action;
}

void print_wallet(wallet wal, int type) {
    set_color(8);
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << (type == 0 ? "BTC" : "EVM") << " address: " << wal.address << "\n";
    std::cout << "public key:  " << wal.public_key << "\n";
    std::cout << "private key: " << wal.private_key << "\n";
    std::cout << "mnemonic:    " << wal.mnemonic << "\n";
    std::cout << "-----------------------------------------------------------------------------\n\n";
    set_color();
}

void save_wallet_data(wallet wal, wallet_data wal_data, int type) {
    std::string save_text = "";
    if (type == WAL_TYPE_BTC) {
        save_text = "[Bitoin]\naddress: " + wal.address + "\npublic key: " + wal.public_key + "\nprivate key: " + wal.private_key + "\nmnemonic: " + wal.mnemonic + 
            "\nbtc_amount: " + std::to_string(wal_data.btc_amount);
    }
    else {
        save_text = "[EVM]\naddress: " + wal.address + "\npublic key: " + wal.public_key + "\nprivate key: " + wal.private_key + "\nmnemonic: " + wal.mnemonic +
            "\neth_amount: " + std::to_string(wal_data.eth_amount) + "\nbnb_amount: " + std::to_string(wal_data.bnb_amount) + "\matic_amount: " + std::to_string(wal_data.matic_amount);
    }

    HANDLE hfile = CreateFileA(save_found_path.c_str(), FILE_ALL_ACCESS, NULL, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (!hfile) {
        std::cout << save_text << "\n";
        return;
    }

    if (!WriteFile(hfile, save_text.c_str(), save_text.size(), nullptr, nullptr)) {
        std::cout << save_text;
    }

    CloseHandle(hfile);

}

void start_search_btc_wallets();
void start_search_evm_wallets();

int main(int argc, char** argv) {
  //  test();


    if (!load_bip39_words()) {
        std::cout << "failed to load bip39 words from 'bip39-words.txt'.\n";
        system("pause");
        return 0;
    }

    if (argc > 1) {
        if (strstr(argv[1], "gen-btc")) {
            int count = 1;
            if (argc > 2)
                count = std::atoi(argv[2]);
            for (int i = 0; i < count; ++i) {
                std::string mnemonic = generate_mnemonic(12);
                wallet wal = generate_bitcoin_wallet(mnemonic);
                print_wallet(wal, 0);
            }
        }
        else if (strstr(argv[1], "gen-evm") || strstr(argv[1], "gen-eth")) {
            int count = 1;
            if (argc > 2)
                count = std::atoi(argv[2]);
            for (int i = 0; i < count; ++i) {
                std::string mnemonic = generate_mnemonic(12);
                wallet wal = generate_evm_wallet(mnemonic);
                print_wallet(wal, 0);
            }

        }
        else if (strstr(argv[1], "search-btc")) {
            start_search_btc_wallets();
        }
        else if (strstr(argv[1], "search-evm") || strstr(argv[1], "search-eth")) {
            start_search_evm_wallets();
        }
        else {
            std::cout << "invalid parameters\n";
        }
        return 0;
    }

    SetConsoleTitleA("[WalletGen] - Menu");
    set_color(6);
    print_logo();
    set_color();

    while (true) {
        int action = show_menu();
        std::cout << "\n";

        if (action == 1) {
            std::string mnemonic = generate_mnemonic(12);
            wallet wal = generate_bitcoin_wallet(mnemonic);
            print_wallet(wal, 0);
        }
        else if (action == 2) {
            std::string mnemonic = generate_mnemonic(12);
            wallet wal = generate_evm_wallet(mnemonic);
            print_wallet(wal, 1);
        }
        else if (action == 3) {
            start_search_btc_wallets();
        }
        else if (action == 4) {
            start_search_evm_wallets();
        }
        else if (action == 5) {
            std::cout << "---------------------------------------------------------------------------------\n";
            std::cout << "| my crypto wallets:                                                            |\n";
            std::cout << "| Bitcoin:                       bc1qm2hla5zg735uqpgjtp3va4djqhh9zd8derzrwx     |\n";
            std::cout << "| EVM (ETH, BNB, MATIC, e.t.c):  0x8BCa04cA3e65fa7ECE2314e02149F6Ef4F3A0060     |\n";
            std::cout << "| Litecoin:                      ltc1qa4ermet8czres4aunf33zwe35sk6peq6tg6cc8    |\n";
            std::cout << "| USDT TRC20:                    TFu3ydp1tSDhCtrHNsVSVxriVGhHvVzUu9             |\n";
            std::cout << "---------------------------------------------------------------------------------\n";
        }
        else if (action == 6) {
            break;
        }
        else {
            std::cout << "invalid action\n";
        }

        std::cout << "\n\n";

    }

    return 0;
}

void start_search_btc_wallets()
{
    wallet_checker checker;
    if (!checker.initialize()) {
        MessageBoxA(GetConsoleWindow(), "Failed to initialize checker. check your internet connection", "Message", MB_ICONERROR);
        return;
    }
    if (binance_api::get_btc_udst_price() == 0.0f) {
        MessageBoxA(GetConsoleWindow(), "Failed to connect to the Binance API", "Message", MB_ICONWARNING);
    }

    unsigned long long checked_mnemonics = 0;
    float found_balance = 0.0f;
    int speed = 0, speed_check = 0, mnemonics_by_sec = 0;

    while (true) {
        std::string mnemonic = generate_mnemonic(12);
        wallet wal = generate_bitcoin_wallet(mnemonic);
        wallet_data wal_data = checker.get_wallet_data(wal.address, WAL_TYPE_BTC);
        
        std::cout << "mnemonic: " << wal.mnemonic << "\naddress:  " << wal.address << "\nbalance:  " << wal_data.btc_amount << " btc\n";

        if (wal_data.btc_amount > 0) {
            save_wallet_data(wal, wal_data, WAL_TYPE_BTC);
            found_balance += wal_data.btc_amount * binance_api::get_btc_udst_price();
        }
        if (time(0) - speed_check > 1) {
            speed = mnemonics_by_sec;
            mnemonics_by_sec = 0;
            speed_check = time(0);
        }

        checked_mnemonics++;
        mnemonics_by_sec++;

        std::string new_title = "[WalletGen] - Seaching for BTC wallets / [Checked mnemonics: " + std::to_string(checked_mnemonics) + " | Found balance: " + std::to_string(found_balance) +
            "$ | Speed: " + std::to_string(speed) + "/s]";
        SetConsoleTitleA(new_title.c_str());
    }
   

}

void start_search_evm_wallets()
{
    wallet_checker checker;
    if (!checker.initialize()) {
        MessageBoxA(GetConsoleWindow(), "Failed to initialize checker. check your internet connection", "Message", MB_ICONERROR);
        return;
    }
    if (binance_api::get_btc_udst_price() == 0.0f) {
        MessageBoxA(GetConsoleWindow(), "Failed to connect to the Binance API", "Message", MB_ICONWARNING);
    }

    unsigned long long checked_mnemonics = 17256100;
    float found_balance = 0.0f;
    int speed = 0, speed_check = 0, mnemonics_by_sec = 0;

    while (true) {

        std::string mnemonic = generate_mnemonic(12);
        wallet wal = generate_evm_wallet(mnemonic);
        wallet_data wal_data = checker.get_wallet_data(wal.address, WAL_TYPE_EVM);

        std::cout << "mnemonic: " << wal.mnemonic << "\naddress:  " << wal.address << "\nbalance:  ";

        if (wal_data.eth_amount == 0 && wal_data.bnb_amount == 0 && wal_data.matic_amount == 0) {
            std::cout << "(empty)\n";
        }
        else {
            std::cout << "(with balance)\n";
            save_wallet_data(wal, wal_data, WAL_TYPE_BTC);
            found_balance += (wal_data.eth_amount * binance_api::get_eth_usdt_price()) + (wal_data.bnb_amount * binance_api::get_bnb_usdt_price()) +
                (wal_data.matic_amount * binance_api::get_matic_usdt_price());
        }

        if (time(0) - speed_check > 1) {
            speed = mnemonics_by_sec;
            mnemonics_by_sec = 0;
            speed_check = time(0);
        }

        checked_mnemonics++;
        mnemonics_by_sec++;

        std::string new_title = "[WalletGen] - Seaching for EVM wallets / [Checked mnemonics: " + std::to_string(checked_mnemonics) + " | Found balance: " + std::to_string(found_balance) + 
            "$ | Speed: " + std::to_string(speed) + "/s]";
        SetConsoleTitleA(new_title.c_str());

    }

}
