CC			= gcc
C_FLAGS		= -Wall -Wextra -Werror -Wshadow -Wunreachable-code -Wunused \
			  -Wconversion -Wsign-conversion -Wfloat-equal \
			  -Wnull-dereference -Wstrict-prototypes -Wmissing-prototypes \
			  -Wdouble-promotion -Wpedantic -Wformat=2 -Wundef \
			  -fstack-protector-strong

INCLUDE		= -I include/

SRC			= $(wildcard src/*.c)

OUTPUT		= -o bin/udsClient

all:
	$(CC) $(C_FLAGS) main.c $(SRC) $(INCLUDE) $(LIB_INCLUDE) $(LIB_SRC) $(OUTPUT)

clean:
	rm bin/udsClient