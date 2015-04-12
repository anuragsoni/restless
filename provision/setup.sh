#!/usr/bin/env bash

echo ">>> Installing CMAKE"

sudo apt-get install -y cmake

echo ">>> Installing g++4.9"

sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -y
sudo apt-get install -y g++-4.9

sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 30
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 30
sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++ 30

echo ">>> Installing clang"
sudo apt-get install -y clang-3.5

echo ">>> Installing curl"
sudo apt-get install -y libcurl4-openssl-dev

echo ">>> Installing git"
sudo add-apt-repository -y ppa:git-core/ppa
sudo apt-get update -y
sudo apt-get install -y git

echo ">>> Installing zsh"
sudo apt-get install -y zsh
sudo chsh -s /bin/zsh vagrant
zsh
