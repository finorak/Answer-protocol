NAME = parser

SRC = cJSON.c parser.c parser_utils.c parser_memory.c stack_utils.c \
	  ../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c \

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

.PHONY: re clean all fclean run
