NAME = parser

SRC = cJSON.c parser.c parser_utils.c parser_memory.c stack_utils.c \
	  data_extractor/rooms_extractor.c data_extractor/helper.c data_extractor/item_extractor.c

OBJS = $(SRC:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror -g

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

run:
	./$(NAME) world.json

valgrind: all
	valgrind --leak-check=full ./parser world.json

.PHONY: re clean all fclean run valgrind
