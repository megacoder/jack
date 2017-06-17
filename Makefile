PREFIX	=/opt
BINDIR	=${PREFIX}/bin

CC	=gcc -march=i686
CFLAGS	=-Os -pipe -Wall -pedantic
LDFLAGS	=
LDLIBS	=

all:	jack

clean:
	${RM} *.o a.out core.*

distclean clobber: clean
	${RM} jack

check:	jack
	LANG=C man ls | ./jack

install: jack
	install -d ${BINDIR}
	install -c -s jack ${BINDIR}/

uninstall:
	${RM} ${BINDIR}/jack
