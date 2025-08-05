# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 12:06:23 by siuol             #+#    #+#              #
#    Updated: 2025/08/05 18:27:23 by tripham          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= ircserv
CC			= c++
FLAG		= -Wall -Wextra -Werror -std=c++20
RM			= rm -rf
INCLUDE 	= -Iinclude include/system.hpp

#--DIRECTORIES--
SRC			= src
CORE		= src/core
PRS			= src/parser
SRV			= src/server
IRC			= src/irc

#CORE
CORE_SRC	=	$(CORE)/CORE.cpp

#PARSING
PRS_SRC		= 

#SERVER
SRV_SRC	=

#IRC
IRC_SRC	=


SRCS		= $(CORE_SRC) $(PRS_SRC) $(SRV_SRC) $(IRC_SRC)
OBJS		= ${SRCS:.cpp=.o}

all : $(NAME)

%.o : %.cpp
		@$(CC) $(FLAG) -c $< -o $@

$(NAME): $(OBJS)
		@$(CC) $(FLAG) $(INCLUDE) $(OBJS) -o $@
		@printf "\033[1;33m42VN-Pasila \033[1;32m 💻Launching"
		@for i in 1 2 3; do \
			printf "\033[0;32m."; sleep 0.15; \
		done; \
		for i in 1 2 3; do \
			printf "\b \b"; sleep 0.15; \
		done; \
		for i in 1 2 3; do \
			printf "\033[0;32m."; sleep 0.15; \
		done; \
		for i in 1 2 3; do \
			printf "\b \b"; sleep 0.15; \
		done; \
		printf "\033[0m\n"

clean :
		@$(RM) $(OBJS)

fclean: clean
			@printf "\033[1;33m42VN-Pasila\033[1;32m 💻Cleaning"
			@for i in 1 2 3; do \
				printf "\033[0;32m."; sleep 0.15; \
			done; \
			for i in 1 2 3; do \
				printf "\b \b"; sleep 0.15; \
			done; \
			for i in 1 2 3; do \
				printf "\033[0;32m."; sleep 0.15; \
			done; \
			for i in 1 2 3; do \
				printf "\b \b"; sleep 0.15; \
			done; \
			printf "\033[0m\n"
			@echo "\033[1;33m42VN-Pasila\033[1;32m ✅Done"
		@rm -f $(NAME)

re :fclean all

.PHONY : all clean fclean re