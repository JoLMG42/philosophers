# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 15:20:04 by jtaravel          #+#    #+#              #
#    Updated: 2022/05/18 17:05:41 by jtaravel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	./classics/ft_itoa.c ./classics/ft_atoi.c ./classics/ft_strncmp.c \
	./srcs/ft_routine_bonus.c ./srcs/ft_check_bonus.c ./srcs/ft_init_bonus.c \
	philo_bonus.c \

OBJS =	${SRCS:.c=.o}


HEADERS =	includes

NAME =	philo_bonus

CC =	gcc

RM =	rm -f

CFLAGS =	-Wall -Wextra -Werror -pthread -g3 -fsanitize=address

.c.o:
		${CC} ${CFLAGS} -I${HEADERS} -c $< -o ${<:.c=.o}


${NAME}:	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all clean flcean re
