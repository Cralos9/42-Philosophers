# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 12:44:54 by cacarval          #+#    #+#              #
#    Updated: 2023/10/11 11:39:14 by cacarval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = srcs/philo.c srcs/utils.c srcs/eating_actions.c srcs/clean_exit.c

OBJS = ${SRC:.c=.o}

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I include
GREEN := \e[1;32m
RED := \e[1;31m
YELLOW := \e[1;33m
RESET := \033[0m

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		${CC} ${CFLAGS} -fsanitize=thread ${INCLUDE} ${OBJS} -o ${NAME} -pthread
		@echo "${GREEN}---./philo was created---${RESET}"

all:	${NAME}

valgrind: ${OBJS}
		${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME} -pthread
		@echo "${GREEN}---./philo without sanitize was created---${RESET}"


clean:
		${RM} ${OBJS}
		@echo "${YELLOW}---Objects were removed---${RESET}"

fclean: clean
		${RM} ${NAME}
		@echo "${RED}---./philo was removed---${RESET}"

fclear: clean
		${RM} ${NAME}
		clear

re: fclean all

.PHONY: all clean fclean re

.SILENT: