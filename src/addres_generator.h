#pragma once

#include "utils.h"

struct wallet {
	std::string address;
	std::string public_key;
	std::string private_key;
	std::string mnemonic;
};

wallet generate_evm_wallet(const std::string& mnemonic);
wallet generate_bitcoin_wallet(const std::string& mnemonic);