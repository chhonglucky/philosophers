# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanhhon <chanhhon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 20:45:02 by chanhhon          #+#    #+#              #
#    Updated: 2024/07/18 20:50:47 by chanhhon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		=	cc
CFLAGS 	=	-Wall -Wextra -Werror
NAME 	=	philo
SRCS	=	main.c
			
OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean :
	@rm -rf $(OBJS)

fclean :	clean
	@rm -rf $(NAME)

re :
	@make fclean
	@make	all

.PHONY : re fclean clean all bonus