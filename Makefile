# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 11:45:57 by diana             #+#    #+#              #
#    Updated: 2025/03/14 12:20:59 by cosmos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = minishell

CC              = gcc
CFLAGS          = -Wall -Wextra -Werror
RD				= -lreadline -lhistory
#LDFLAGS			= -L/opt/homebrew/opt/readline/lib
#CPPFLAGS		= -I/opt/homebrew/opt/readline/include
RM              = rm -rf

SRCS            = main.c \
					src/path/path.c \
					src/path/path_utils.c \
					src/input/get_input.c \
					src/input/utils_input.c \
					src/input/rep_env_var.c \
					src/input/handle_input.c \
					src/split/split_bis.c \
					src/split/util_split.c \
					src/split/util2.split.c \
					src/execute/execute_utils.c \
					src/execute/execute.c \
					src/execute/execute_utils_env.c \
					src/check_cmd/check_builtins.c \
					src/ft_list/list.c \
					src/free/free.c \
					src/free/free_bis.c \
					src/builtins/pwd.c \
					src/builtins/cd.c \
					src/builtins/cd_utils.c \
					src/builtins/echo.c \
					src/builtins/env.c \
					src/builtins/exit.c \
					src/builtins/export.c \
					src/builtins/unset.c \
					src/signals/ctrl_c.c \
					src/signals/ctrl_nothing.c \
					src/signals/signal_pipex.c \
					src/utils/utils.c \

OBJS            = $(SRCS:.c=.o)

LIBFT_PATH      = ./libft
LIBFT           = $(LIBFT_PATH)/libft.a

%.o: %.c
				$(CC) $(CFLAGS)  -c $< -o $@

all:            $(NAME)

$(NAME):        $(LIBFT) $(OBJS)
				@$(CC) $(CFLAGS)  $(OBJS) $(LIBFT) -o $(NAME) $(RD)

$(LIBFT):
				make -C $(LIBFT_PATH)

clean:
				make -C $(LIBFT_PATH) clean
				$(RM) $(OBJS)

fclean:         clean
				make -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)

re:             fclean all