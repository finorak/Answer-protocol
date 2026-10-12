SERVER_APPLICATION_NAME := parser_cli
CLIENT_APPLICATION_NAME := client_cli

SRC := parser/parser.c parser/parser_utils.c \
	  parser/data_extractor/rooms_extractor.c parser/data_extractor/helper_part_1.c \
	  parser/data_extractor/helper_part_2.c parser/data_extractor/item_extractor.c \
	  parser/data_extractor/npc_extractor.c parser/data_extractor/quest_extractor.c \
	  parser/data_extractor/mission_extractor.c parser/data_extractor/dialogue_extractor.c \
	  parser/data_extractor/group_extractor.c parser/data_validator/data_validator.c \
	  parser/data_validator/data_validator_helper.c parser/memory_manager/memory_manager.c \
	  parser/cJSON.c

# put here files that we didn't create our own
EXCEPT_FILES := parser/cJSON.c

FILES_TO_LINT := $(filter-out $(EXCEPT_FILES), $(SRC))

SERVER_OBJS := $(SRC:.c=.o)

CC := cc

FLAGS := -Wall -Wextra -Werror -g

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(SERVER_APPLICATION_NAME)

$(SERVER_APPLICATION_NAME): $(SERVER_OBJS)
	$(CC) $(FLAGS) $(SERVER_OBJS) -o $(SERVER_APPLICATION_NAME)

clean:
	rm -rf $(SERVER_OBJS)

fclean: clean
	rm -rf $(SERVER_APPLICATION_NAME)

re: fclean all

run:
	./$(SERVER_APPLICATION_NAME) world.json

valgrind: all
	valgrind --leak-check=full ./$(SERVER_APPLICATION_NAME) world.json

lint:
	norminette $(FILES_TO_LINT)

.PHONY: re clean all fclean run valgrind
