# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/22 13:15:39 by gbersac           #+#    #+#              #
#    Updated: 2014/06/11 19:37:50 by gbersac          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


################################################################################
# BASIC VARIABLES															   #
################################################################################

SRCS			:= clean_fd.c client_read.c interpret_cmd.c \
					 main.c main_loop.c srv_accept.c \
					srv_create.c update_env.c update_env_fct.c map.c time.c \
					init_env.c new_turn.c \
					ser_avance.c ser_droite.c ser_gauche.c ser_voir.c \
					ser_inventaire.c ser_prend.c ser_pose.c ser_expulse.c \
					ser_broadcast.c ser_incantation.c ser_fork.c \
					ser_connect_nbr.c map_str.c incantation.c

PATH_OBJ		:= obj
PATH_SRC		:= src
PATH_INC		:= inc

CFLAGS			:= -Wall -Wextra -Werror
OBJECTS			:= $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRCS))

################################################################################
# LIBRARY VARIABLES															   #
################################################################################

export DIR_FT	:= ../$(DIR_FT)

export DIR_LIB 	:= $(patsubst %,../%,$(DIR_LIB))
LIBRARY			:= $(LIB_BASICS) $(LIB_LINKER)
INCLUDES		:= -I./$(PATH_INC) $(patsubst %,-I%/inc,$(DIR_LIB))

################################################################################
# BASIC RULES																   #
################################################################################

.PHONY: all

all: $(NAME_SERVEUR)

$(NAME_SERVEUR): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIBRARY) $(DEBUG)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.c)
	@mkdir -p $(PATH_OBJ)
	$(CC) -c -o $@ $(CFLAGS) $^ $(DEBUG) $(INCLUDES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME_SERVEUR)

re: fclean $(NAME_SERVEUR)
