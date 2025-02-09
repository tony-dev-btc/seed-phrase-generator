#pragma once

#pragma warning (disable : 4996)

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <cassert>

#include <openssl/sha.h>  // Äëÿ SHA256
#include <openssl/hmac.h> // Äëÿ HMAC
#include <openssl/ripemd.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/bn.h>
#include <openssl/obj_mac.h>
#include <openssl/pem.h>
#include <openssl/err.h>


int base58_encode(const  std::vector<unsigned char> input, int len, unsigned char result[]);

std::string keccak256(const std::string& input);
std::vector<unsigned char> ripemd160(const std::vector<unsigned char>& data);
std::vector<unsigned char> sha256(const std::vector<unsigned char>& data);
std::vector<unsigned char> hmacSha512(const std::string& key, const std::string& message);


std::vector<int> create_bech32_checksum(const std::vector<int>& data);
std::string bech32_encode(const std::vector<unsigned char>& data);

std::vector<uint8_t> mnemonic_to_seed(const std::string& mnemonic, const std::string& passphrase = "");
std::string bytearray2hex(const std::vector<uint8_t>& byteArray);