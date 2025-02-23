# Seed Phrase Generator - WalletGen

**Wallet-Gen** is a tool designed for brute force and generating cryptocurrency wallets (such as Bitcoin and EVM-based wallets like ETH, BNB, MATIC, etc.), as well as discovering forgotten or lost - wallets that contain an existing balance.

<p align="left">
    <img src="/assets/gonalva.webp" />
</p>

## Overview

Wallet - Gen is built in C++ and is open-source, allowing anyone to access and modify the code. Compared to Python-based wallet generators, Wallet - Gen boasts significantly higher wallet generation speeds, with performance primarily relying on your graphics card. 
For generating - EVM wallets (ETH, BNB, MATIC, etc.), Wallet - Gen uses the keccak256 algorithm, while Bitcoin - wallets are created using the Segwit format under Bech32.

## Features

- Generate - a single Bitcoin wallet.
- Generate - a single EVM wallet (ETH, BNB, MATIC, etc.).
- Search for - Bitcoin wallets with a balance.
- Search for - EVM wallets with a balance.

![video gif](/assets/fettnannhalf.gif)

# Searching for Crypto Wallets

Wallet - Gen allows you to search using brute force method for two types of crypto wallets with an existing balance. To search for BTC wallets, press key `3` in the menu or run `start_search_btc.bat`. For searching EVM wallets (such as Ethereum, BNB, etc.), press key `4` in the menu or run `start_search_evm.bat`. 

The search speed is determined by your hardware, especially your graphics card. To increase your chances of finding a wallet with a balance, you can run multiple instances of the program, from 1 to 4 or more, depending on the power of your graphics card.

## My Finds

I’ve personally recovered two BTC - wallets with a balance. The first had 0.000032 BTC,  the second contained 0.0528 BTC (roughly $4800 at the time of discovery).  
Here’s the link to the wallet: [bc1qk3m62hx2hh5mhvc0tj45f9xflzcnu0sur3rvay](mempool.space/address/bc1qk3m62hx2hh5mhvc0tj45f9xflzcnu0sur3rvay).

<p align="left">
    <img src="/assets/tocozu.webp" />
</p>

## Download
- [Windows x64](../../releases)
- [Linux](../../releases)

## Build
1. Open the project file (`Wallet-Gen.sln`) in Visual Studio or any other compatible C++ compiler.
2. Install the necessary dependencies and build the project.

### Installing vcpkg and libssl

```cmd
> git clone https://github.com/microsoft/vcpkg
> .\vcpkg\bootstrap-vcpkg.bat
> .\vcpkg\vcpkg integrate install
> .\vcpkg\vcpkg install openssl:x64-windows
```

## Todo
1. Сreate a version of the program for Linux.
2. Search for missing words in a seed phrase.

## Contribute
Contributions are welcome! If you have ideas, bug reports, or want to contribute to the codebase, feel free to submit a pull request.

## License
This project is licensed under the [Apache 2.0 License](/LICENSE)

## Donate
**BTC:** bc1qeyrshy5ntsguwxe9m8tp2x2yqhddz7ymkj44h9

**ETH:** 0x76c2E75B92Eb340f01B378e332FC7d8954893693
