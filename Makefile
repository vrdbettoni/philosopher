# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 17:14:33 by vroth-di          #+#    #+#              #
#    Updated: 2020/06/08 20:56:51 by vroth-di         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	philosophers

CC			=	gcc
INCL1		=	philo_one/philo_one.h
INCL1		=	philo_two/philo_two.h
INCL1		=	philo_three/philo_three.h
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=thread

OBJS_PATH1	=	philo_one
OBJS_PATH2	=	philo_two
OBJS_PATH3	=	philo_three

OBJ			=	$(SRCS:.c=.o)
OBJI		=	$(SRCS3:.c=.o)
OBJ1		=	$(addprefix $(OBJS_PATH1)/, $(SRCS:.c=.o))
OBJ2		=	$(addprefix $(OBJS_PATH2)/, $(SRCS:.c=.o))
OBJ3		=	$(addprefix $(OBJS_PATH3)/, $(SRCS3:.c=.o))

SRCS		=	main.c				actions.c\
				threads.c				utils.c

SRCS3		=	main.c				actions.c\
				threads.c				utils.c\
				itoa.c

all:		$(NAME)

############	FOR LINUX	############
$(NAME): 	$(OBJ1) $(OBJ2) $(OBJ3)
			@cd philo_one && $(CC) $(CFLAGS) -o philo_one -pthread $(OBJ)
			@cd philo_two && $(CC) $(CFLAGS) -o philo_two -pthread $(OBJ)
			@cd philo_three && $(CC) $(CFLAGS) -o philo_three -pthread $(OBJI)

############	 FOR MAC	############
#$(NAME): 	$(OBJ1) $(OBJ2) $(OBJ3)
#			@cd philo_one && $(CC) $(CFLAGS) -o philo_one -lpthread $(OBJ)
#			@cd philo_two && $(CC) $(CFLAGS) -o philo_two -lpthread $(OBJ)
#			@cd philo_three && $(CC) $(CFLAGS) -o philo_three -lpthread  $(OBJI)

			@echo "\033[32m > \033[1m$(NAME)\033[0;32m created !\033[0m"

%/*.o:	%/*.c
					@$(CC) $(CFLAGS) -c $< -o $@


clean:
			@rm philo_one/*.o 2>/dev/null || true
			@rm philo_two/*.o 2>/dev/null || true
			@rm philo_three/*.o 2>/dev/null || true
			@echo "\033[31m > \033[1mobjs/*\033[0;31m delete.\033[0m"

fclean:		clean
			@rm -rf philo_one/philo_one 2>/dev/null || true
			@rm -rf philo_two/philo_two 2>/dev/null || true
			@rm -rf philo_three/philo_three 2>/dev/null || true
			@echo "\033[31m > \033[1m$(NAME)\033[0;31m delete.\033[0m"

re:			fclean all

.PHONY:		all clean fclean re
