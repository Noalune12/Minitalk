# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 17:11:29 by lbuisson          #+#    #+#              #
#    Updated: 2025/01/13 12:11:01 by lbuisson         ###   ########lyon.fr    #
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
LIBFT_SRCDIR = $(LIBFT_DIR)/srcs
LIBFT_OBJDIR = $(LIBFT_DIR)/objs

LIBFT = $(LIBFT_SRCDIR)/libft
PRINTF = $(LIBFT_SRCDIR)/ft_printf
GNL = $(LIBFT_SRCDIR)/gnl

LIBFT_FUNCTIONS = $(LIBFT)/ft_atoi.c $(LIBFT)/ft_bzero.c $(LIBFT)/ft_calloc.c $(LIBFT)/ft_isalnum.c $(LIBFT)/ft_isalpha.c $(LIBFT)/ft_isascii.c \
	$(LIBFT)/ft_isdigit.c $(LIBFT)/ft_isprint.c $(LIBFT)/ft_itoa.c $(LIBFT)/ft_memchr.c $(LIBFT)/ft_memcmp.c \
	$(LIBFT)/ft_memcpy.c $(LIBFT)/ft_memmove.c $(LIBFT)/ft_memset.c $(LIBFT)/ft_putchar_fd.c $(LIBFT)/ft_putendl_fd.c \
	$(LIBFT)/ft_putnbr_fd.c $(LIBFT)/ft_putstr_fd.c $(LIBFT)/ft_split.c $(LIBFT)/ft_strchr.c $(LIBFT)/ft_strdup.c \
	$(LIBFT)/ft_strjoin.c $(LIBFT)/ft_strlcat.c $(LIBFT)/ft_strlcpy.c $(LIBFT)/ft_strlen.c $(LIBFT)/ft_strmapi.c \
	$(LIBFT)/ft_striteri.c $(LIBFT)/ft_strncmp.c $(LIBFT)/ft_strnstr.c $(LIBFT)/ft_strrchr.c $(LIBFT)/ft_substr.c \
	$(LIBFT)/ft_strtrim.c $(LIBFT)/ft_tolower.c $(LIBFT)/ft_toupper.c \
	$(LIBFT)/ft_lstnew.c $(LIBFT)/ft_lstadd_front.c $(LIBFT)/ft_lstsize.c $(LIBFT)/ft_lstlast.c $(LIBFT)/ft_lstadd_back.c \
	$(LIBFT)/ft_lstdelone.c $(LIBFT)/ft_lstclear.c $(LIBFT)/ft_lstiter.c $(LIBFT)/ft_lstmap.c \
	$(PRINTF)/ft_numbers.c $(PRINTF)/ft_words_pointer.c $(PRINTF)/ft_printf.c \
	$(GNL)/get_next_line.c $(GNL)/get_next_line_utils.c

LIBFT_OBJS = $(patsubst $(LIBFT_SRCDIR)/%.c,$(LIBFT_OBJDIR)/%.o,$(LIBFT_FUNCTIONS))
LIBFT_DEPS = $(LIBFT_OBJS:.o=.d)

DEPS = $(C_OBJS:.o=.d) $(S_OBJS:.o=.d) $(C_OBJS_BONUS:.o=.d) $(S_OBJS_BONUS:.o=.d) $(LIBFT_DEPS)

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

$(LIBFT_A): $(LIBFT_OBJS)
	$(MAKE) -C $(LIBFT_DIR)

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

.PHONY : all clean fclean re bonus clean_bonus

-include $(DEPS)
