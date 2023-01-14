# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 14:20:54 by arabiai           #+#    #+#              #
#    Updated: 2022/11/16 17:57:43 by arabiai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

COLOUR_GREEN=\033[92m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m
COLOUR_YELLOW=\033[0;33m

SOURCES = ft_printf.c ft_printf_utils.c\

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

ECHO1 = @echo "$(COLOUR_GREEN)Compiled all files successfully!$(COLOUR_END)"
ECHO2 = @echo "$(COLOUR_YELLOW)Library $(NAME) created!$(COLOUR_END)"
ECHO3 = @echo "$(COLOUR_RED)Object files removed!$(COLOUR_END)"
ECHO4 = @echo "$(COLOUR_RED)Lilibrary $(NAME) removed!$(COLOUR_END)"

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS) ft_printf.h
	$(ECHO1)
	ar rc $(NAME) $?
	$(ECHO2)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJECTS)
	$(ECHO3)

fclean : clean
	$(RM) $(NAME)
	$(ECHO4)

re : fclean all

.PHONY : clean fclean all re
