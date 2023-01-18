# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 12:06:44 by arabiai           #+#    #+#              #
#    Updated: 2023/01/18 20:09:46 by arabiai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipexbonus

COLOUR_GREEN=\033[92m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m
COLOUR_YELLOW=\033[0;33m

bold := $(shell tput bold)
sgr0 := $(shell tput sgr0)

SOURCES = mandatory/pipex_main.c mandatory/pipex_utils.c mandatory/errors_utils.c \

BONUS_SOURCES = bonus/pipex_main_bonus.c bonus/pipex_utils_bonus.c bonus/errors_utils_bonus.c \
bonus/bonus_utils.c bonus/ft_split.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

ECHO1 = @echo "$(COLOUR_GREEN)$(bold)Compiled all files successfully!$(sgr0)$(COLOUR_END)"
ECHO1_B = @echo "$(COLOUR_GREEN)$(bold)Compiled all BOONUS files successfully!$(sgr0)$(COLOUR_END)"
ECHO2 = @echo "$(COLOUR_YELLOW)$(bold)the executable $(NAME) created successfully!$(sgr0)$(COLOUR_END)"
ECHO2_B = @echo "$(COLOUR_YELLOW)$(bold)the executable $(BONUS_NAME) created successfully!$(sgr0)$(COLOUR_END)"
ECHO3 = @echo "$(COLOUR_RED)$(bold)All Object files removed!$(sgr0)$(COLOUR_END)"
ECHO4 = @echo "$(COLOUR_RED)$(bold)the executable $(NAME) and $(BONUS_NAME) removed!$(sgr0)$(COLOUR_END)"

OBJECTS = $(SOURCES:.c=.o)
BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

all : $(NAME) libftprintf pipe_exc

$(NAME) : $(OBJECTS) mandatory/pipex.h
	$(ECHO1)
	ar rcs library $(OBJECTS)
    #ar rcs lib $? meaning add the newest changed objects

%.o: %.c mandatory/pipex.h bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

pipe_exc : mandatory/pipex.h
	$(CC) $(CFLAGS) mandatory/pipex_main.c libftprintf.a library -o $(NAME)
	$(ECHO2)

bonus : $(BONUS_OBJECTS) libftprintf bonus/pipex_bonus.h get_next_line/get_next_line.h
	$(ECHO1_B)
	ar rcs bonus_library $(BONUS_OBJECTS)
	$(CC) $(CFLAGS) bonus/pipex_main_bonus.c libftprintf.a bonus_library -o $(BONUS_NAME)
	$(ECHO2_B)

libftprintf :
	@cd ft_printf && make && mv libftprintf.a ../

clean :
	$(RM) $(OBJECTS) $(BONUS_OBJECTS)
	$(ECHO3)

fclean : clean
	$(RM) $(NAME) $(BONUS_NAME) library bonus_library libftprintf.a
	cd ft_printf && make fclean
	cd Get_next_line && rm -rf *.o
	$(ECHO4)

re : fclean all

.PHONY : clean fclean all re bonus