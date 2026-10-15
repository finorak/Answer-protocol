SHELL := /bin/bash

# just for the moment
SERVER_APPLICATION_NAME := server_cli


FILE_TO_DEBUG ?= $(SERVER_APPLICATION_NAME)

HEADERS := includes/data_extractor.h includes/parser.h includes/world.h

SERVER_SRC := parser/parser.c parser/parser_utils.c \
	  parser/data_extractor/rooms_extractor.c parser/data_extractor/helper_part_1.c \
	  parser/data_extractor/helper_part_2.c parser/data_extractor/item_extractor.c \
	  parser/data_extractor/npc_extractor.c parser/data_extractor/quest_extractor.c \
	  parser/data_extractor/mission_extractor.c parser/data_extractor/dialogue_extractor.c \
	  parser/data_extractor/group_extractor.c parser/data_validator/data_validator.c \
	  parser/data_validator/data_validator_helper.c parser/memory_manager/memory_manager.c \
	  parser/cJSON.c parser/data_validator/bfs_helper_1.c parser/data_validator/interconnect.c \
      parser/data_validator/bfs_helper_2.c

# put here files that we didn't create our own
C_EXCEPT_FILES := parser/cJSON.c
HEADER_EXCEPT_FILES := includes/cJSON.h

FILES_TO_LINT := $(filter-out $(C_EXCEPT_FILES), $(SERVER_SRC))
HEADER_TO_LINT := $(filter-out $(HEADER_EXCEPT_FILES), $(HEADERS))

SERVER_OBJS := $(SERVER_SRC:.c=.o)

CC := cc

DEBUG_FLAGS := --leak-check=full --show-leak-kinds=all

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
	valgrind $(DEBUG_FLAGS) ./$(SERVER_APPLICATION_NAME) world.json

lint:
	norminette $(FILES_TO_LINT) $(HEADER_TO_LINT)

	@if [[ "$(FILE_TO_DEBUG)" == "$(firstword $())" ]]; then \
		echo "server"; \
	else \
		echo "client"; \
	fi

.PHONY: re clean all fclean run valgrind lint debug
