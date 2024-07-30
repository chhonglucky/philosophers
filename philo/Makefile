# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanhhon <chanhhon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/24 19:23:07 by chanhhon          #+#    #+#              #
#    Updated: 2024/07/30 19:36:33 by chanhhon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		=	cc
CFLAGS 	=	-Wall -Wextra -Werror
NAME 	=	philo
SRCS	=	actions.c free.c init.c macro.c main.c utils.c			
OBJS	= 	$(SRCS:.c=.o)

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
