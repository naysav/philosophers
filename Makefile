# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ralena <ralena@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/23 16:36:44 by ralena            #+#    #+#              #
#    Updated: 2022/01/23 16:36:45 by ralena           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philosohers
CC		=	gcc
FLAGS	=	-Wall -Werror -Wextra
HEADERS =	philosophers.h	
SRC		=	philosophers.c 					\
			parsing_and_initialization.c	\
			philosophers_lifecycle.c		\
			utils.c 
			
OBJ		=	$(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: ann clean fclean re
