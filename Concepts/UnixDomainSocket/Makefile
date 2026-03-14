CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror \
			-Wstrict-prototypes \
			-Wmissing-prototypes \
			-Wshadow \
			-Wconversion \
			-pedantic

BIN		=	bin/server

SRC		=	main.c \
			src/myFunctions.c \
			src/udsServer.c

INCLUDE	=	-I include

all: $(BIN)

$(BIN): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $(BIN)

run: $(BIN)
	./$(BIN)

clean:
	rm -rf bin

re: clean all

debug: CFLAGS += -g -fsanitize=address -fsanitize=undefined
debug: $(BIN)

.PHONY: all run clean re debug