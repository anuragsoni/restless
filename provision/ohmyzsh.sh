#!/bin/zsh

# Clone oh-my-zsh
git clone --depth=1 https://github.com/robbyrussell/oh-my-zsh.git /home/vagrant/.oh-my-zsh

# Create a new zsh configuration from the provided template
cp /home/vagrant/.oh-my-zsh/templates/zshrc.zsh-template /home/vagrant/.zshrc

echo "\033[0;34mCopying your current PATH and adding it to the end of ~/.zshrc for you.\033[0m"
sed -i -e "/export PATH=/ c\\
export PATH=\"$PATH\"
" /home/vagrant/.zshrc
