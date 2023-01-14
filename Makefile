# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 12:06:44 by arabiai           #+#    #+#              #
#    Updated: 2023/01/14 20:50:21 by arabiai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

COLOUR_GREEN=\033[92m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m
COLOUR_YELLOW=\033[0;33m

SOURCES = pipex_main.c pipex_utils.c errors_utils.c \

# BONUS_SOURCES = 

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

ECHO1 = @echo "$(COLOUR_GREEN)Compiled all files successfully!$(COLOUR_END)"
ECHO2 = @echo "$(COLOUR_YELLOW)the executable $(NAME) created successfully!$(COLOUR_END)"
ECHO3 = @echo "$(COLOUR_RED)Object files removed!$(COLOUR_END)"
ECHO4 = @echo "$(COLOUR_RED)the executable $(NAME) removed!$(COLOUR_END)"

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME) libftprintf pipe_exc

$(NAME) : $(OBJECTS) pipex.h
	$(ECHO1)
	ar rcs library $(OBJECTS)
   #ar rcs lib $? meaning add the newest changed objects

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

pipe_exc : pipex.h
	$(CC) $(CFLAGS) pipex_main.c libftprintf.a library -o $(NAME)
	$(ECHO2)

libftprintf :
	@cd ft_printf && make && mv libftprintf.a ../

clean :
	$(RM) $(OBJECTS)
	$(ECHO3)

fclean : clean
	$(RM) $(NAME) library libftprintf.a && cd ft_printf && make fclean
	$(ECHO4)

re : fclean all

.PHONY : clean fclean all re bonus