# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diana <diana@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 11:45:57 by diana             #+#    #+#              #
#    Updated: 2025/04/27 22:43:05 by diana            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = minishell
CC              = gcc
CFLAGS          = -Wall -Wextra -Werror
RD				= -lreadline -lhistory
LDFLAGS			= -L/opt/homebrew/opt/readline/lib
CPPFLAGS		= -I/opt/homebrew/opt/readline/include
RM              = rm -rf

SRCS            = main.c \
					src/path/path.c \
					src/path/path_utils.c \
					src/input/get_input.c \
					src/input/get_input_utils.c \
					src/input/utils_input.c \
					src/input/utils_input_2.c \
					src/input/rep_env_var.c \
					src/input/rep_env_var_utils.c \
					src/input/handle_input.c \
					src/input/quote.c \
					src/input/redirection.c \
					src/input/verify_and_split_cmd.c \
					src/input/verify_and_split_cmd_utils.c \
					src/input/check_syntax.c \
					src/input/check_syntax_utils.c \
					src/input/count_sp_ch.c \
					src/execute/execute_utils.c \
					src/execute/execute.c \
					src/execute/execute_utils_env.c \
					src/execute/execute_pipe.c \
					src/execute/execute_pipe_utils.c \
					src/execute/utils_pipe.c \
					src/execute/util.c \
					src/execute/check_redir.c \
					src/execute/here_doc.c \
					src/execute/redir.c \
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
					src/builtins/export_utils.c \
					src/builtins/export_utils_bis.c \
					src/builtins/export_utils_update.c \
					src/builtins/unset.c \
					src/signals/ctrl_c.c \
					src/signals/ctrl_nothing.c \
					src/utils/utils.c \

OBJS            = $(SRCS:.c=.o)

LIBFT_PATH      = ./libft
LIBFT           = $(LIBFT_PATH)/libft.a

%.o: %.c
				$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

all:            $(NAME)

$(NAME):        $(LIBFT) $(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME) $(RD)

$(LIBFT):
				make -C $(LIBFT_PATH)

clean:
				make -C $(LIBFT_PATH) clean
				$(RM) $(OBJS)

fclean:         clean
				make -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)

re:             fclean all
