CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

TARGET = my_blockchain

SOURCES := main.c \
		  $(shell find $(SOURCEDIR/lib) -name '*.c')

OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean fclean

clean:
	@rm $(OBJECTS)

fclean: clean
	@rm $(TARGET) 