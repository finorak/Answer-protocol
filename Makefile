# just for the moment
CLIENT_NAME = parser_cli

# source files for the sever
SRC = parser/parser.c parser/parser_utils.c \
	  parser/data_extractor/rooms_extractor.c parser/data_extractor/helper_part_1.c \
	  parser/data_extractor/helper_part_2.c parser/data_extractor/item_extractor.c \
	  parser/data_extractor/npc_extractor.c parser/data_extractor/quest_extractor.c \
	  parser/data_extractor/mission_extractor.c parser/data_extractor/dialogue_extractor.c \
	  parser/data_extractor/group_extractor.c parser/data_validator/data_validator.c \
	  parser/data_validator/data_validator_helper.c parser/memory_manager/memory_manager.c \
	  parser/cJSON.c

# put here files that we didn't create our own
EXCEPT_FILES = parser/cJSON.c

FILES_TO_LINT = $(filter-out $(EXCEPT_FILES), $(SRC))

OBJS = $(SRC:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror -g

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(CLIENT_NAME)

$(CLIENT_NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(CLIENT_NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(CLIENT_NAME)

re: fclean all

run:
	./$(CLIENT_NAME) world.json

valgrind: all
	valgrind --leak-check=full ./$(CLIENT_NAME) world.json

lint:
	norminette $(FILES_TO_LINT)

.PHONY: re clean all fclean run valgrind
