# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 17:11:29 by lbuisson          #+#    #+#              #
#    Updated: 2025/01/17 14:58:33 by lbuisson         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

C_NAME = client
S_NAME = server
NAME = $(C_NAME) $(S_NAME)
CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
RM = rm -f

C_SRCS = client.c
S_SRCS = server.c

OBJDIR = objs

C_OBJS = $(addprefix $(OBJDIR)/, $(C_SRCS:.c=.o))
S_OBJS = $(addprefix $(OBJDIR)/, $(S_SRCS:.c=.o))

BONUS_DIR = bonus
C_BONUS = client_bonus.c
S_BONUS = server_bonus.c
C_BONUS_FILES = $(addprefix $(BONUS_DIR)/, $(C_BONUS))
S_BONUS_FILES = $(addprefix $(BONUS_DIR)/, $(S_BONUS))
C_OBJS_BONUS = $(addprefix $(OBJDIR)/, $(C_BONUS_FILES:.c=.o))
S_OBJS_BONUS = $(addprefix $(OBJDIR)/, $(S_BONUS_FILES:.c=.o))

LIBFT_DIR = libft
LIBFT_A = libft/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) $(LIBFT_A) -lft

DEPS = $(C_OBJS:.o=.d) $(S_OBJS:.o=.d) $(C_OBJS_BONUS:.o=.d) $(S_OBJS_BONUS:.o=.d)

all: $(LIBFT_A) $(NAME)

$(C_NAME): $(C_OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(C_OBJS) $(LIBFT_FLAGS) -o $(C_NAME)
	$(RM) $(C_OBJS_BONUS) $(C_OBJS_BONUS:.o=.d)
	@echo "💫✨💫 \033[92mClient compiled\033[0m 💫✨💫"

$(S_NAME): $(S_OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(S_OBJS) $(LIBFT_FLAGS) -o $(S_NAME)
	$(RM) $(S_OBJS_BONUS) $(S_OBJS_BONUS:.o=.d)
	@echo "💫✨💫 \033[92mServer compiled\033[0m 💫✨💫"

$(OBJDIR)/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_OBJDIR)/%.o: $(LIBFT_SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A): libft

libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

bonus: .bonus_server .bonus_client

.bonus_client: $(C_OBJS_BONUS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(C_OBJS_BONUS) $(LIBFT_FLAGS) -o $(C_NAME)
	$(RM) $(C_OBJS) $(C_OBJS:.o=.d)
	@touch .bonus_client
	@echo "💫✨💫 \033[92mClient Bonus compiled\033[0m 💫✨💫"

.bonus_server: $(S_OBJS_BONUS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(S_OBJS_BONUS) $(LIBFT_FLAGS) -o $(S_NAME)
	$(RM) $(S_OBJS) $(S_OBJS:.o=.d)
	@touch .bonus_server
	@echo "💫✨💫 \033[92mServer Bonus compiled\033[0m 💫✨💫"

clean:
	$(RM) -rf $(OBJDIR)
	$(RM) .bonus_client .bonus_server
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(C_NAME) $(S_NAME) $(LIBFT_A)
	@echo "🧹🧹🧹 \033[92mCleaning minitalk complete\033[0m 🧹🧹🧹"

re : fclean all

.PHONY : all clean fclean re bonus libft

-include $(DEPS)
