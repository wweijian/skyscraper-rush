CC = cc
OFLAG =
DIR = ex00/
CFLAGS = -Wall -Wextra -Werror -I$(DIR) -g $(OFLAG)
SRC = $(wildcard $(DIR)*.c)

all: $(SRC)
	$(CC) $(CFLAGS) -o rush-01 $^

clean:
	rm -f rush-01

re: clean all

.PHONY: all clean re