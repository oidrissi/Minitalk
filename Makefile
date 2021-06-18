# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/16 07:22:31 by oidrissi          #+#    #+#              #
#    Updated: 2021/06/17 12:23:13 by oidrissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client

SRCS = helpers.c

OBJECTS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror


all: $(SERVER) $(CLIENT) $(SRCS)

$(SERVER) : server.o minitalk.h
	@$(CC) server.o $(SRCS) -o $@

$(CLIENT) : client.o minitalk.h
	@$(CC) client.o $(SRCS) -o $@

clean:
		rm -f $(OBJECTS)

fclean: 
		rm -f $(OBJECTS) client.o server.o
		rm -f $(SERVER)
		rm -f $(CLIENT)

re: fclean all

bonus: