# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/22 13:15:39 by gbersac           #+#    #+#              #
#    Updated: 2015/12/02 15:35:56 by gbersac          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


################################################################################
# BASIC VARIABLES															   #
################################################################################

SRCS_MAIN		:= clean_fd.c client_read.c interpret_cmd.c \
					 main.c main_loop.c srv_accept.c \
					srv_create.c update_env.c update_env_fct.c map.c time.c \
					init_env.c new_turn.c cmd_msg.c map_str.c incantation.c

SRCS_CLI		:=	cli/ser_avance.c cli/ser_droite.c cli/ser_gauche.c cli/ser_voir.c \
					cli/ser_inventaire.c cli/ser_prend.c cli/ser_pose.c cli/ser_expulse.c \
					cli/ser_broadcast.c cli/ser_incantation.c cli/ser_fork.c \
					cli/ser_connect_nbr.c

SRCS_GFX		:=	gfx/gfx_pex.c gfx/gfx_pbc.c gfx/gfx_pie.c gfx/gfx_pfk.c \
					gfx/gfx_pdr.c gfx/gfx_pgt.c gfx/gfx_pdi.c gfx/gfx_enw.c \
					gfx/gfx_eht.c gfx/gfx_ebo.c gfx/gfx_edi.c gfx/gfx_seg.c \
					gfx/gfx_smg.c

SRCS			:= $(SRCS_MAIN) $(SRCS_CLI) $(SRCS_GFX)

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

$(PATH_OBJ)/cli/%.o: $(addprefix $(PATH_SRC)/cli/,%.c)
	@mkdir -p $(PATH_OBJ)/cli
	$(CC) -c -o $@ $(CFLAGS) $^ $(DEBUG) $(INCLUDES)

$(PATH_OBJ)/gfx/%.o: $(addprefix $(PATH_SRC)/gfx/,%.c)
	@mkdir -p $(PATH_OBJ)/gfx
	$(CC) -c -o $@ $(CFLAGS) $^ $(DEBUG) $(INCLUDES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME_SERVEUR)

re: fclean $(NAME_SERVEUR)
