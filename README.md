[![Build Status](https://travis-ci.org/FndNur1Labs/Catalyst-Evo.svg?branch=master)](https://travis-ci.org/FndNur1Labs/Catalyst-Evo)

<h2>Introduction</h2>

We’ve built a custom platform to Future of Cryptocurrency. CryptonoteEvo is a platform technology for next generation of cryptonight.

Catalyst Coin is the most secure, stable, and decentralized platform amongst the thousands of digital currencies in the market today.
Catalyst is an innovative, cryptographically-secured digital asset ledger based on blockchain technology. Developed in part from the core code behind Karbo.

<h2>We are trying to do things no cryptocurrency has ever done before. The Completly Masternode Solution in cryptonote world.</h2>

For more details visit our Website :

https://catalyst.cash

-= Building CatalystCoin =-

<h2>On *nix:</h2>

Dependencies: GCC 4.7.3 or later, CMake 3.11.3 or later, Boost_1_67 or later.

You may download them from:

http://gcc.gnu.org/

http://www.cmake.org/

http://www.boost.org/

Alternatively, it may be possible to install them using a package manager.

To build, change to a directory where this file is located, and run `make'. The resulting executables can be found in build/release/src.

Advanced options:

Parallel build: run `make -j<number of threads>' instead of `make'.

Debug build: run `make build-debug'.

Test suite: run `make test-release' to run tests in addition to building. Running `make test-debug' will do the same to the debug version.

<h2>On Linux (Ubuntu 16.04):</h2>
Install Dependencies:

```bash
apt install build-essential libqt4-dev qt5-qmake cmake qttools5-dev libqt5webkit5-dev qttools5-dev-tools qt5-default python-sphinx texlive-latex-base inotify-tools openssl libssl-dev libdb++-dev libminiupnpc-dev git sqlite3 libsqlite3-dev g++ libpng-dev gedit python gcc make libbz2-dev libdb-dev libssl-dev  libreadline-dev autoconf libtool libleveldb-dev libblkid-dev e2fslibs-dev libboost-all-dev libaudit-dev automake nano qtbase5-dev qt4-dev-tools libncurses5-dev fakeroot wget bzip2 bison flex dctrl-tools libelf-dev libuv1-dev libmicrohttpd-dev pkg-config libevent-dev libunbound-dev libminiupnpc-dev libunwind8-dev libldns-dev libexpat1-dev libgtest-dev doxygen graphviz screen curl git python

sudo apt update

sudo apt upgrade

git clone https://github.com/CatalystCash/Catalyst-Evo.git catalyst
cd catalyst
git submodule init
git submodule update --remote
make -j4
```
Note : If you need cmake version error please follow below setps.

```bash

cd catalyst/modules/cmake
./bootstrap && make && make install
```

<h2>On Windows:</h2>

Dependencies: MSVC 2017 or later, CMake 3.11.3 or later, and Boost_1_67_0-msvc-14.1 or later. You may download them from:

http://www.microsoft.com/

http://www.cmake.org/

http://www.boost.org/

To build, change to a directory where this file is located, and run this commands: (VisualStudio 2017)

```bash
git clone https://github.com/CatalystCash/Catalyst-Evo.git catalyst
cd catalyst
git submodule init
git submodule update --remote
mkdir build && cd build && cmake .. -G "Visual Studio 15 Win64" ..
```
then open catalyst.sln File on Visual Studio

In VS' Solution Explorer select upnpc-static' Properies -> C/C++ -> Code Generation -> Runtime Library - > change it to Multi-threaded (/MT)

And Finaly do the Build.

Good luck!

Powered by Nur1Labs[twitter:@nur1labs] Engine
