# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eveiled <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 12:45:23 by eveiled           #+#    #+#              #
#   Updated: 2021/11/22 20:07:16 by eveiled          ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME		= philo
#
SOURSE = main.c create_all.c destroy.c\
		ft_atoi.c lsts.c philo_life.c utils_1.c
# 
CFLAGS		= -Wall -Werror -Wextra -I $(HEADER)
HEADER	= philosophers.h
OBJ = $(SOURSE:%.c=%.o)
CC = gcc
#
.PHONY : all clean fclean re bonus
#
all : $(NAME)
#
$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(SOURSE) -o $(NAME)
#
%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
#
clean :
	@rm -f $(OBJ)
#
fclean : clean
	@rm -f $(NAME)
#
re : fclean all



