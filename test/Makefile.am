# Autoconf/automake file

bin_PROGRAMS = test_cvms5

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS} ${ETREE_INCLUDES} ${PROJ_INCLUDES} -I../src
AM_LDFLAGS = ${LDFLAGS} ${ETREE_LDFLAGS} ${PROJ_LDFLAGS} -L../src -lcvms5 -lm 

objects = test_api.o
TARGETS = $(bin_PROGRAMS)

all: $(bin_PROGRAMS)

install:
	mkdir -p ${prefix}/tests
	cp test_cvms5 ${prefix}/tests

test_cvms5$(EXEEXT): $(objects)
	$(CC) -o $@ $^ $(AM_LDFLAGS)

$(objects): %.o: %.c
	$(CC) -o $@ -c $^ $(AM_CFLAGS)

run_unit : test_cvms5
	./run_unit

clean :
	rm -rf *~ *.o test_cvms5

