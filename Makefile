# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eveiled <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 12:45:23 by eveiled           #+#    #+#              #
#   Updated: 2021/11/11 14:02:43 by eveiled          ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME		= so_long
#
SOURSE = utils_1.c utils_2.c get_next_line.c get_next_line_utils.c\
		messages.c main.c ft_putnbr_fd.c ft_putstr_fd.c utils_3.c
# 
CFLAGS		= -Wall -Werror -Wextra -I $(HEADER)
HEADER	= so_long.h
HEADER_2 = get_next_line.h
OBJ = $(SOURSE:%.c=%.o)
CC = gcc
#
.PHONY : all clean fclean re bonus
#
all : $(NAME)
#
$(NAME) : $(OBJ) $(HEADER) $(HEADER_2)
	$(CC) $(CFLAGS) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit $(SOURSE) -o $(NAME)
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



