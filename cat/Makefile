CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
SOURCES=s21_cat.c main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=s21_cat

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

rebuild: clean all

style:
	clang-format -style=google -i *.c *.h

test:
	bash test_cat.sh

.PHONY: all clean rebuild style test
