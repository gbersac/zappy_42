# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/30 12:40:20 by gbersac           #+#    #+#              #
#    Updated: 2015/12/02 21:44:50 by gbersac          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# SOURCES       															   #
################################################################################

SRC			:= init_trantorian.c resource.c resource2.c resources_to_str.c

################################################################################
# BASIC VARIABLES															   #
################################################################################

PATH_OBJ	:= obj
PATH_SRC	:= src
PATH_INC	:= inc

NAME		:= libgen.a
CFLAGS		:= -Wall -Wextra -Werror
OBJECTS		:= $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))
INCLUDES	:= -I$(PATH_INC) -I../$(DIR_FT)/inc
DEBUG		:= -g -O0

################################################################################
# RULES																		   #
################################################################################

.PHONY: all

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rc $@ $(OBJECTS)
	@ranlib $(NAME)
	@echo Creating Library $(NAME) $(words $(OBJECTS)) files inside

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.c)
	@mkdir -p $(PATH_OBJ)
	$(CC) -c -o $@ $(CFLAGS) $^ -O0 -g $(INCLUDES)

clean:
	@rm -f $(OBJECTS)
	@echo Delete $(words $(OBJECTS)) object file

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
