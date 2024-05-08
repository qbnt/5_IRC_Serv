NAME = ircserv
CC = g++
CFLAGS = -Wall -Wextra -Werror -g -std=c++98

INC_DIR = includes
SRC_DIR = srcs
OBJ_DIR = obj

INCLUDES = -I$(INC_DIR)

SRC_FILES = main.cpp \
			Channel.cpp \
			Client.cpp \
			CommandsUse.cpp \
			Server.cpp \
			commands/InvitCommand.cpp \
			commands/JoinCommand.cpp \
			commands/KickCommand.cpp \
			commands/ListCommand.cpp \
			commands/ModeCommand.cpp \
			commands/NickCommand.cpp \
			commands/NoticeCommand.cpp \
			commands/PartCommand.cpp \
			commands/PassCommand.cpp \
			commands/PingCommand.cpp \
			commands/PrivMsgCommand.cpp \
			commands/QuitCommand.cpp \
			commands/UserCommand.cpp \
			commands/WhoCommand.cpp \

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Colors
RESET = \033[0m
GREEN = \033[32m
ORANGE_Q = \033[38;2;230;126;34m
GREEN_Q = \033[38;2;60;120;60m
BROWN_Q = \033[38;2;139;69;19m
GREEN_M = \033[38;2;170;180;90m
YELLOW = \033[33m
RED = \033[31m
BLUE = \033[34m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Compilation successful!$(RESET)"
	@sleep 0

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(BLUE)Compiling: $<$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)Cleaning object files...$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Full clean completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re