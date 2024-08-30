#!/bin/sh

if tcc --version; then
        printf "\n"
else git clone https://github.com/TinyCC/tinycc
	cd tinycc
	./configure
	make
	make test
	make install
fi
