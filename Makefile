SERVER_NAME = client

SRC = parser/cJSON.c parser/parser.c parser/parser_utils.c parser/stack_utils.c \
	  parser/data_extractor/rooms_extractor.c parser/data_extractor/helper_part_1.c \
	  parser/data_extractor/helper_part_2.c parser/data_extractor/item_extractor.c \
	  parser/data_extractor/npc_extractor.c parser/data_extractor/quest_extractor.c \
	  parser/data_extractor/mission_extractor.c parser/data_extractor/dialogue_extractor.c \
	  parser/data_extractor/group_extractor.c \
	  parser/memory_manager/memory_manager_1.c parser/memory_manager/memory_manager_2.c \
	  parser/memory_manager/memory_manager.c

EXCEPT_FILES = cJSON.c

FILES_TO_LINT = $(filter-out $(EXCEPT_FILES), $(SRC))

OBJS = $(SRC:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror -g

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(SERVER_NAME)

$(SERVER_NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(SERVER_NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(SERVER_NAME)

re: fclean all

run:
	./$(SERVER_NAME) world.json

valgrind: all
	valgrind --leak-check=full ./parser world.json

lint:
	norminette $(FILES_TO_LINT)

.PHONY: re clean all fclean run valgrind
