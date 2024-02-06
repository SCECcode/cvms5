# Autoconf/automake file

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS}
AM_FCFLAGS = ${FCFLAGS}
AM_LDFLAGS = ${LDFLAGS}

install:
	mkdir -p ${prefix}/data/s5
	cp ./config ${prefix}/data
	cp ./s5/* ${prefix}/data/s5
	chmod +x ${prefix}/data/s5
	chmod -R og+rw ${prefix}/data/*
