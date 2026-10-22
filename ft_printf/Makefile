CC = cc

FLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

SRCS = ft_putnbr.c ft_printf.c str_utils.c print_unsigned.c ft_puthex.c print_memory.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -pthread -c $< -o $@

all: $(NAME)

$(NAME):$(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

lint:
	norminette $(SRCS)

re: fclean all

.PHONY: all fclean re clean lint

