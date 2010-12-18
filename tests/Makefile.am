TESTS = check-main
check_PROGRAMS = check-main
check_main_SOURCES = check-main.c \
                     check-mini-readline.c check-mini-readline.h \
                     check-mini-strip.c check-mini-strip.h \
                     $(top_builddir)/src/mini-strip.h

check_main_CFLAGS = @CHECK_CFLAGS@
check_main_LDADD = $(top_builddir)/src/libmini.la @CHECK_LIBS@
