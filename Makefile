# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 11:45:57 by diana             #+#    #+#              #
#    Updated: 2025/02/25 20:05:42 by maximemarti      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = minishell

CC              = gcc
CFLAGS          = -Wall -Wextra -Werror
RD				= -lreadline
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
				@$(CC) $(CFLAGS) $(RD) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
				make -C $(LIBFT_PATH)

clean:
				make -C $(LIBFT_PATH) clean
				$(RM) $(OBJS)

fclean:         clean
				make -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)

re:             fclean all