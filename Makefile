# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaydont <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/13 13:10:43 by chaydont          #+#    #+#              #
#    Updated: 2017/12/13 14:36:32 by chaydont         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c \
	  ft_printu.c \
	  ft_printi.c \
	  ft_prints.c \
	  ft_printc.c \
	  parsing.c \
	  ft_strchr.c \
	  ft_atoi.c \
	  ft_strlen.c \
	  ft_putchar.c \
	  ft_isdigit.c \
	  ft_nb_digit_base.c

OBJ = $(SRC:.c=.o)

HEADER = ft_printf.h

LIB = libft/libft.a

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@gcc -c $(FLAG) $(SRC)
	@echo "[Objects Created]"
	@ar rc $(NAME) $(OBJ)
	@echo "[$(NAME) Created]"

clean:
	@rm -f $(OBJ)
	@echo "[Objects Cleaned]"

fclean: clean
	@rm -f $(NAME)
	@echo "[$(NAME) Cleaned]"

re: fclean all
