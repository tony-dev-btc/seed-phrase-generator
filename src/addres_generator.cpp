#include "addres_generator.h"

wallet generate_evm_wallet(const std::string& mnemonic) {
    std::vector<uint8_t> seed = mnemonic_to_seed(mnemonic);
    std::string private_key = bytearray2hex(seed);
    std::string public_key = keccak256(private_key);
    std::string address = public_key.substr(public_key.size() - 40);
    address = "0x" + address;

    wallet wal;
    wal.address = address;
    wal.public_key = public_key;
    wal.private_key = private_key;
    wal.mnemonic = mnemonic;
    return wal;
}

wallet generate_bitcoin_wallet(const std::string& mnemonic) {
  
    std::vector<unsigned char> seed = mnemonic_to_seed(mnemonic);
    std::string private_key = bytearray2hex(seed);
    std::string public_key = keccak256(private_key);
    std::vector<unsigned char> pubKey(public_key.begin(), public_key.end());
    std::vector<unsigned char> sha256Hash = sha256(pubKey);
    std::vector<unsigned char> ripemd160Hash = ripemd160(sha256Hash);
    std::string address = bech32_encode(ripemd160Hash);

    wallet wal;
    wal.address = address;
    wal.public_key = public_key;
    wal.private_key = private_key;
    wal.mnemonic = mnemonic;
    return wal;
}