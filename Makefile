# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 17:11:29 by lbuisson          #+#    #+#              #
#    Updated: 2025/01/09 15:28:52 by lbuisson         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

C_NAME = client
S_NAME = server
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -MMD -MP

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
LIBFT_FLAGS = -L$(LIBFT_DIR) $(LIBFT_A)
LIBFT_DEPS = $(addprefix $(LIBFT_DIR)/, $(patsubst %.c, %.o, $(notdir $(FUNCTIONS))))

DEPS = $(C_OBJS:.o=.d) $(S_OBJS:.o=.d) $(C_OBJS_BONUS:.o=.d) $(S_OBJS_BONUS:.o=.d) $(LIBFT_DEPS)

all: $(C_NAME) $(S_NAME)

$(C_NAME): $(C_OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(C_OBJS) $(LIBFT_FLAGS) -o $(C_NAME)

$(S_NAME): $(S_OBJS)
	$(CC) $(CFLAGS) $(S_OBJS) $(LIBFT_FLAGS) -o $(S_NAME)

bonus: .bonus_server .bonus_client

.bonus_client: $(C_OBJS_BONUS)
	$(CC) $(CFLAGS) $(C_OBJS_BONUS) $(LIBFT_FLAGS) -o $(C_NAME)
	@touch .bonus_client

.bonus_server: $(S_OBJS_BONUS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(S_OBJS_BONUS) $(LIBFT_FLAGS) -o $(S_NAME)
	@touch .bonus_server

$(OBJDIR)/%.o: %.c Makefile $(LIBFT_A)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) -rf $(OBJDIR)
	$(RM) .bonus_client .bonus_server
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(C_NAME) $(S_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY : all clean fclean re bonus

-include $(DEPS)
