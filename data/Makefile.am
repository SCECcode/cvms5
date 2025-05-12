# Autoconf/automake file

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS}
AM_FCFLAGS = ${FCFLAGS}
AM_LDFLAGS = ${LDFLAGS}

all:
if WITH_CVMS5_LARGEDATA_DIR
	echo "USING WITH_CVMS5_LARGEDATA_DIR in cvms5"
else
	if [ ! -d "${prefix}/data/s5" ]; then \
		./make_data_files.py; \
	fi
endif

install:
if WITH_CVMS5_LARGEDATA_DIR
	if [ ! -d "${prefix}/data/s5" ]; then \
		$(MKDIR_P) ${prefix}/data; \
		$(LN_S) -f $(CVMS5_LARGEDATA_DIR) ${prefix}/data/s5; \
		echo "USING WITH_CVMS5_LARGEDATA_DIR in cvms5"; \
	fi
	cp config ${prefix}/data
else
	if [ ! -d "${prefix}/data/s5" ]; then \
		$(MKDIR_P) ${prefix}/data; \
		mv s5 ${prefix}/data; \
		$(LN_S) -f ${prefix}/data/s5 .; \
	fi
	cp config ${prefix}/data
endif

clean:
	echo "clean"
