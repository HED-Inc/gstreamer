#! /bin/bash

set -eux

# Install Rust
RUSTUP_VERSION=1.27.0
RUST_VERSION=1.79.0
RUST_ARCH="x86_64-unknown-linux-gnu"

RUSTUP_URL=https://static.rust-lang.org/rustup/archive/$RUSTUP_VERSION/$RUST_ARCH/rustup-init
curl -o rustup-init $RUSTUP_URL

export RUSTUP_HOME="/usr/local/rustup"
export CARGO_HOME="/usr/local/cargo"
export PATH="/usr/local/cargo/bin:$PATH"

chmod +x rustup-init;
./rustup-init -y --no-modify-path --default-toolchain $RUST_VERSION;
rm rustup-init;
chmod -R a+w $RUSTUP_HOME $CARGO_HOME

cargo install --locked cargo-c --version 0.9.31+cargo-0.78.0

rustup --version
cargo --version
rustc --version

# Cleanup the registry after install
# so we don't have to save 200mb of the index in the ci image
rm -rf "$CARGO_HOME/registry"
