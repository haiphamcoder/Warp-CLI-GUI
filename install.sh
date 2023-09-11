#!/bin/bash

# Check if user is root
if [ $EUID -ne 0 ]; then
    echo "Please run as root"
    exit
fi

# Install dependencies
sudo apt install -y curl gnupg

# Add Cloudflare gpg key
curl https://pkg.cloudflareclient.com/pubkey.gpg | sudo gpg --yes --dearmor --output /usr/share/keyrings/cloudflare-warp-archive-keyring.gpg

# Add Cloudflare repository
echo "deb [arch=amd64 signed-by=/usr/share/keyrings/cloudflare-warp-archive-keyring.gpg] https://pkg.cloudflareclient.com/ $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/cloudflare-client.list

# Update apt and install Cloudflare Warp
sudo apt update && sudo apt install cloudflare-warp

# Using WARP
# Initial Connection
warp-cli register

# Install Warp Cloudflare GUI
sudo make install
