#!/bin/sh

MV="4.4"

ftcc() {
	tcc --version && {
        	printf "tcc is installed...\n";
	} || {
		cd /usr/src;
		git clone https://github.com/TinyCC/tinycc;
		cd tinycc;
		./configure \
			--enable-cross;
		make;
		make test;
		make install;
		tcc --version
	}
}

printf "\n"

if make --version; then
	printf "\n" > /dev/null
else
	cd /usr/src
	wget https://fosszone.csd.auth.gr/gnu/make/make-$MV.tar.gz
	tar xf make-$MV.tar.gz
	rm make-$MV.tar.gz
	cd make-$MV
	./build.sh
	cp make /usr/bin
	make --version
fi
