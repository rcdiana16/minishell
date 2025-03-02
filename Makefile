# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 11:45:57 by diana             #+#    #+#              #
#    Updated: 2025/03/02 16:33:31 by cosmos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = minishell

CC              = gcc
CFLAGS          = -Wall -Wextra -Werror
RD				= -lreadline
RM              = rm -rf

SRCS            = main.c \
					src/path/path.c \
					src/input/get_input.c \
					src/split/split_bis.c \
					src/split/util_split.c \
					src/split/util2.split.c \
					src/path/find_ex_path.c \
					src/check_cmd/check_builtins.c \
					src/ft_list/list.c \
					src/free/free.c \
					src/builtins/pwd.c \
					src/builtins/util2_pwd.c \
					src/builtins/util_pwd.c \
					src/builtins/cd.c \
					src/builtins/echo.c \
					src/builtins/env.c \
					src/utils/util.c \
					src/builtins/export.c \
					src/builtins/unset.c \

OBJS            = $(SRCS:.c=.o)

LIBFT_PATH      = ./libft
LIBFT           = $(LIBFT_PATH)/libft.a

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

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