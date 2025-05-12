# Autoconf/automake file

bin_PROGRAMS = test_cvms5

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS} ${ETREE_INCLUDES} ${PROJ_INCLUDES}
AM_LDFLAGS = ${LDFLAGS} ${ETREE_LDFLAGS} ${PROJ_LDFLAGS}

objects = test_api.o
TARGETS = $(bin_PROGRAMS)

all: $(bin_PROGRAMS)

install:
	mkdir -p ${prefix}/tests
	cp test_cvms5 ${prefix}/tests

test_cvms5: $(objects)
	$(CC) -o $@ $^ $(AM_LDFLAGS)

run_unit : test_cvms5
	./test_cvms5

clean :
	rm -rf *~ *.o test_cvms5

