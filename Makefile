# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 11:45:57 by diana             #+#    #+#              #
#    Updated: 2025/02/25 14:22:38 by cosmos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = minishell

CC              = gcc
CFLAGS          = -Wall -Wextra -Werror
RM              = rm -rf

SRCS            = main.c \
					path.c \
					get_env.c \
					get_input.c \

OBJS            = $(SRCS:.c=.o)

LIBFT_PATH      = ./libft
LIBFT           = $(LIBFT_PATH)/libft.a

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

all:            $(NAME)

$(NAME):        $(LIBFT) $(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
				make -C $(LIBFT_PATH)

clean:
				make -C $(LIBFT_PATH) clean
				$(RM) $(OBJS) $(BONUS_OBJS) $(NAME).bonus

fclean:         clean
				make -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)

re:             fclean all