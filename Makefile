# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 12:06:23 by siuol             #+#    #+#              #
#    Updated: 2025/08/05 18:27:23 by tripham          ###   ########.fr        #
=======
#    By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 12:06:23 by siuol             #+#    #+#              #
#    Updated: 2025/08/07 19:43:44 by htran-th         ###   ########.fr        #
>>>>>>> main
#                                                                              #
# **************************************************************************** #

NAME 		= ircserv
CC			= c++
FLAG		= -std=c++20 #-Wall -Wextra -Werror
RM			= rm -rf
INCLUDE 	= -Iinclude

#--DIRECTORIES--
SRC			= src
CORE		= src/core
PRS			= src/parser
SRV			= src/server
IRC			= src/irc
INFRAS		= src/server/infras

#CORE
CORE_SRC	=	$(CORE)/main.cpp			\
				$(CORE)/notifyer.cpp

#PARSING
PRS_SRC		=	$(PRS)/parseSystem.cpp		\
				$(PRS)/parseGeneral.cpp   	\
				$(PRS)/parseHandler.cpp		\
				$(PRS)/parseMode.cpp		\
				$(PRS)/parseSignin.cpp		\
				$(PRS)/parseUtility.cpp	

#SERVER
SRV_SRC		=	$(SRV)/cmd/cmdHandler.cpp					\
				$(SRV)/cmd/cmdModeHandler.cpp				\
				$(SRV)/implementation/serverClean.cpp		\
				$(SRV)/implementation/serverUtility.cpp		\
				$(SRV)/implementation/serverValidation.cpp

#IRC
IRC_SRC		=	$(IRC)/channel/channelFunctional.cpp		\
				$(IRC)/channel/channelGetter.cpp			\
				$(IRC)/channel/channelSetter.cpp			\
				$(IRC)/channel/channelUnsetter.cpp			\
				$(IRC)/channel/channelValidation.cpp		\
				$(IRC)/client/implementation.cpp

#INFRAS
INFRAS_SRC =	$(INFRAS)/sv_bind_and_listen.cpp \
				$(INFRAS)/sv_init.cpp			\
				$(INFRAS)/sv_poll_and_accept.cpp \
				$(INFRAS)/sv_socket_init.cpp

SRCS		= $(CORE_SRC) $(PRS_SRC) $(SRV_SRC) $(IRC_SRC) $(INFRAS_SRC)
OBJS		= ${SRCS:.cpp=.o}

all : $(NAME)

%.o : %.cpp
		@$(CC) $(FLAG) $(INCLUDE) -c $< -o $@

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