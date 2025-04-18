# Autoconf/automake file

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS} ${ETREE_INCLUDES} ${PROJ_INCLUDES}
AM_LDFLAGS = ${LDFLAGS} ${ETREE_LDFLAGS} ${PROJ_LDFLAGS} -lm

TARGETS = libcvms5.a libcvms5.so

all: $(TARGETS)

install:
	mkdir -p ${prefix}
	mkdir -p ${prefix}/lib
	mkdir -p ${prefix}/include
	cp libcvms5.so ${prefix}/lib
	cp libcvms5.a ${prefix}/lib
	cp cvms5.h ${prefix}/include

libcvms5.a: cvms5_static.o
	$(AR) rcs $@ $^

libcvms5.so: cvms5.o 
	$(CC) -shared $(AM_CFLAGS) -o libcvms5.so $^ $(AM_LDFLAGS)

cvms5.o: cvms5.c
	$(CC) -fPIC -DDYNAMIC_LIBRARY -o $@ -c $^ $(AM_CFLAGS)
	
cvms5_static.o: cvms5.c
	$(CC) -o $@ -c $^ $(AM_CFLAGS)
	
clean:
	rm -rf $(TARGETS)
	rm -rf cvms5.o utm_geo.o

