CC = cc
OFLAG =
DIR = ex00/
CFLAGS = -Wall -Wextra -Werror -I$(DIR) -g $(OFLAG)
SRC = $(wildcard $(DIR)*.c)

all: $(SRC)
	$(CC) $(CFLAGS) -o rush-01 $^

5x5: $(SRC)
	$(CC) $(CFLAGS) -D SIZE=5 -o rush-01 $^

6x6: $(SRC)
	$(CC) $(CFLAGS) -D SIZE=6 -o rush-01 $^

7x7: $(SRC)
	$(CC) $(CFLAGS) -D SIZE=7 -o rush-01 $^

8x8: $(SRC)
	$(CC) $(CFLAGS) -D SIZE=8 -o rush-01 $^

9x9: $(SRC)
	$(CC) $(CFLAGS) -D SIZE=9 -o rush-01 $^

clean:
	rm -f rush-01

re: clean all

.PHONY: all clean re