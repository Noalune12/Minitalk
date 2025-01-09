# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 17:11:29 by lbuisson          #+#    #+#              #
#    Updated: 2025/01/09 07:38:55 by lbuisson         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

C_NAME = client
S_NAME = server
CC = cc
# CFLAGS = -Wall -Werror -Wextra -g3

C_SRCS = client.c
S_SRCS = server.c

C_OBJS = $(C_SRCS:.c=.o)
S_OBJS = $(S_SRCS:.c=.o)
# BONUS_DIR = ./bonus
# BONUS = main_bonus.c exec_cmd_bonus.c utils_bonus.c dup_env_bonus.c split_cmd_bonus.c heredoc_bonus.c
# BONUS_FILES = $(addprefix $(BONUS_DIR)/, $(BONUS))
# OBJS_BONUS = $(BONUS_FILES:.c=.o)

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_FUNCTIONS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
	ft_striteri.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_substr.c \
	ft_strtrim.c ft_tolower.c ft_toupper.c \
	ft_printf/ft_numbers.c ft_printf/ft_words_pointer.c ft_printf/ft_printf.c \
	gnl/get_next_line.c gnl/get_next_line_utils.c
LIBFT_FILES = $(addprefix $(LIBFT_DIR)/, $(LIBFT_FUNCTIONS)) $(LIBFT_DIR)/libft.h $(LIBFT_DIR)/ft_printf/ft_printf.h $(LIBFT_DIR)/Makefile
LIBFT_FLAGS = -L$(LIBFT_DIR) $(LIBFT_A)

all: $(C_NAME) $(S_NAME)

$(S_NAME): $(S_OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(S_OBJS) $(LIBFT_FLAGS) -o $(S_NAME)

$(C_NAME): $(C_OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(C_OBJS) $(LIBFT_FLAGS) -o $(C_NAME)

# bonus: $(NAME) $(OBJS_BONUS)
# 	$(MAKE) fclean -C $(LIBFT_DIR)
# 	rm -f $(NAME)
# 	rm -rf $(OBJS)
# 	$(MAKE) -C $(LIBFT_DIR)
# 	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_FLAGS) -o $(NAME)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -I . -c $< -o $@

clean:
	rm -rf $(C_OBJS)
	rm -rf $(S_OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(C_NAME)
	rm -f $(S_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
