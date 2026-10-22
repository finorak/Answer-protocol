SHELL := /bin/bash

# just for the moment
SERVER_APPLICATION_NAME := server_cli
CLIENT_APPLICATION_NAME := client_cli
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
PRINTF_DIR := ft_printf
PRINTF := $(PRINTF_DIR)/libftprintf.a

FILE_TO_DEBUG ?= $(SERVER_APPLICATION_NAME)

HEADERS := includes/data_extractor.h includes/parser.h includes/world.h \
		   server/tools/tools.h server/validation/validation.h \
		   server/execution/execution.h server/main_utils.h

SERVER_SRC := parser/parser_utils.c parser/data_extractor/rooms_extractor.c \
	  parser/data_extractor/helper_part_1.c parser/data_extractor/helper_part_2.c \
	  parser/data_extractor/item_extractor.c parser/data_extractor/npc_extractor.c \
	  parser/data_extractor/quest_extractor.c parser/data_extractor/mission_extractor.c \
	  parser/data_extractor/dialogue_extractor.c parser/data_extractor/group_extractor.c \
	  parser/data_validator/data_validator.c parser/memory_manager/memory_manager.c parser/cJSON.c \
	  parser/data_validator/bfs_helper_1.c parser/data_validator/interconnect.c parser/buffer_utils.c \
      parser/data_validator/bfs_helper_2.c parser/data_validator/exit_verifiyer.c \
	  server/main.c server/val_exec.c server/main_utils.c server/tools/list.c server/tools/other.c \
	  server/tools/group_and_world.c server/tools/player_manager.c server/tools/room_and_world.c \
	  server/tools/player_and_world.c server/validation/tools_1.c server/validation/tools_2.c \
	  server/validation/validation.c server/execution/cmd_attack.c server/execution/cmd_chat.c \
	  server/execution/cmd_connect.c server/execution/cmd_drop.c server/execution/cmd_group.c \
	  server/execution/cmd_inventory.c server/execution/cmd_look.c server/execution/cmd_move.c \
	  server/execution/cmd_quest.c server/execution/cmd_quests.c server/execution/cmd_status.c \
	  server/execution/cmd_take.c server/execution/cmd_talk.c server/execution/cmd_who.c \
	  server/execution/execution.c server/execution/late_utils.c server/execution/main_distribution.c \
	  server/execution/cmd_complete_quest.c

CLIENT_SRC := client/main.c

# put here files that we didn't create our own
C_EXCEPT_FILES := parser/cJSON.c parser/debug.c
HEADER_EXCEPT_FILES := includes/cJSON.h includes/debug.h

FILES_TO_LINT := $(filter-out $(C_EXCEPT_FILES), $(SERVER_SRC))
HEADER_TO_LINT := $(filter-out $(HEADER_EXCEPT_FILES), $(HEADERS))

SERVER_OBJS := $(SERVER_SRC:.c=.o)
CLIENT_OBJS := $(CLIENT_SRC:.c=.o)

CC := cc

DEBUG_FLAGS := --leak-check=full --show-leak-kinds=all \
			   --track-origins=yes --error-exitcode=1

FLAGS := -Wall -Wextra -Werror -g

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(LIBFT) $(PRINTF) $(SERVER_APPLICATION_NAME) $(CLIENT_APPLICATION_NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(SERVER_APPLICATION_NAME): $(SERVER_OBJS)
	$(CC) $(FLAGS) $(SERVER_OBJS) ./$(PRINTF) -o $(SERVER_APPLICATION_NAME)

$(CLIENT_APPLICATION_NAME): $(CLIENT_OBJS)
	$(CC) $(FLAGS) $(CLIENT_OBJS) ./$(LIBFT) ./$(PRINTF) -o $(CLIENT_APPLICATION_NAME)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(PRINTF_DIR)
	rm -rf $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(PRINTF_DIR)
	rm -rf $(SERVER_APPLICATION_NAME) $(CLIENT_APPLICATION_NAME)

re: fclean all

run:
	./$(SERVER_APPLICATION_NAME) world.json

valgrind: all
	valgrind $(DEBUG_FLAGS) ./$(SERVER_APPLICATION_NAME) world.json

lint:
	norminette $(FILES_TO_LINT) $(HEADER_TO_LINT)
	$(MAKE) lint -C $(LIBFT_DIR)
	$(MAKE) lint -C $(PRINTF_DIR)

debug:
	@if [[ "$(FILE_TO_DEBUG)" == "$(SERVER_APPLICATION_NAME)" ]]; then \
		gdb --args ./$(SERVER_APPLICATION_NAME) world.json; \
	else \
		gdb --args ./$(CLIENT_APPLICATION_NAME) test; \
	fi

.PHONY: re clean all fclean run valgrind lint debug
