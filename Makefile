# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2020/02/05 17:14:33 by vroth-di     #+#   ##    ##    #+#        #
#    Updated: 2020/02/05 18:11:09 by vroth-di    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME		=	philosophers

CC			=	gcc
INCL1		=	philo_one/philo_one.h
INCL1		=	philo_two/philo_two.h
INCL1		=	philo_three/philo_three.h
CFLAGS		=	-Wall -Wextra -Werror

SRCS_PATH1	=	philo_one
SRCS_PATH2	=	philo_two
SRCS_PATH3	=	philo_three
OBJS_PATH	=	objs
OBJS_PATH1	=	obj_one
OBJS_PATH2	=	obj_two
OBJS_PATH3	=	obj_three

# OBJ1		=	$(addprefix $(OBJS_PATH1)/, $(SRCS:.c=.o))
# OBJ2		=	$(addprefix $(OBJS_PATH2)/, $(SRCS:.c=.o))
# OBJ3		=	$(addprefix $(OBJS_PATH3)/, $(SRCS:.c=.o))
OBJ1		=	$(SRCS1:.c=.o)
OBJ2		=	$(SRCS2:.c=.o)
OBJ3		=	$(SRCS3:.c=.o)
SRCS1		=	philo_one/main.c				philo_one/actions.c\
				philo_one/threads.c				philo_one/utils.c
SRCS2		=	philo_two/main.c				philo_two/actions.c\
				philo_two/threads.c				philo_two/utils.c
SRCS3		=	philo_three/main.c				philo_three/actions.c\
				philo_three/threads.c			philo_three/utils.c

all:		$(NAME)

$(NAME): 	$(OBJ1) $(OBJ2) $(OBJ3)
			$(CC) $(CFLAGS) -o philosopher_one -pthread  $(OBJ1)
			$(CC) $(CFLAGS) -o philosopher_two -pthread  $(OBJ2)
			$(CC) $(CFLAGS) -o philosopher_three -pthread  $(OBJ3)
#$(NAME): 	$(OBJ1) $(OBJ2) $(OBJ3)
#			$(CC) $(CFLAGS) -o philosopher_one -lpthread  $(OBJ1)
#			$(CC) $(CFLAGS) -o philosopher_two -lpthread  $(OBJ2)
#			$(CC) $(CFLAGS) -o philosopher_three -lpthread  $(OBJ3)
			@echo "\033[32m > \033[1m$(NAME)\033[0;32m created !\033[0m"

%/*.o:	%/*.c
					@$(CC) $(CFLAGS) -c $< -o $@


clean:
			@rm philo_one/*.o 2>/dev/null || true
			@rm philo_two/*.o 2>/dev/null || true
			@rm philo_three/*.o 2>/dev/null || true
			@echo "\033[31m > \033[1m$(OBJS_PATH)/*\033[0;31m delete.\033[0m"

fclean:		clean
			@rm -rf philosopher_one 2>/dev/null || true
			@rm -rf philosopher_two 2>/dev/null || true
			@rm -rf philosopher_three 2>/dev/null || true
			@echo "\033[31m > \033[1m$(NAME)\033[0;31m delete.\033[0m"

re:			fclean all

.PHONY:		all clean fclean re
