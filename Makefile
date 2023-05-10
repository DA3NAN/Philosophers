# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adnane <adnane@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/27 17:04:12 by adnane            #+#    #+#              #
#    Updated: 2023/05/10 17:36:15 by adnane           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC =	$(wildcard *.c)
OBJ = $(SRC:.c=.o)
HEADER = philo.h
CC = cc
FLAGS = -Wall -Wextra -Werror -g -pthread

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

printf :
	make -C $(PRINTF)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re