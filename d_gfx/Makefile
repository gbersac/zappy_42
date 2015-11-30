# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/22 13:15:39 by gbersac           #+#    #+#              #
#    Updated: 2014/06/11 20:41:56 by gbersac          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# BASIC VARIABLES															   #
################################################################################

SRCS				:= main.c io.c connect.c ia.c env.c \
						gfx_bct.c gfx_edi.c gfx_enw.c gfx_pbc.c gfx_pdr.c \
						gfx_pfk.c gfx_pic.c gfx_pin.c gfx_pnw.c gfx_sbp.c \
						gfx_sgt.c gfx_suc.c gfx_ebo.c gfx_eht.c gfx_msz.c \
						gfx_pdi.c gfx_pex.c gfx_pgt.c gfx_pie.c gfx_plv.c \
						gfx_ppo.c gfx_seg.c gfx_smg.c gfx_tna.c

PATH_OBJ			:= obj
PATH_SRC			:= src
PATH_INC			:= inc

CFLAGS				:= -Wall -Wextra -Werror
OBJECTS				:= $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRCS))

################################################################################
# LIBRARY VARIABLES															   #
################################################################################

export DIR_FT		:= ../$(DIR_FT)

export DIR_LIB		:= $(patsubst %,../%,$(DIR_LIB))
LIBRARY				:= $(LIB_BASICS) $(LIB_LINKER)
INCLUDES			:= -I./$(PATH_INC) $(patsubst %,-I%/inc,$(DIR_LIB))

################################################################################
# BASIC RULES																   #
################################################################################

.PHONY: all

all: $(NAME_GFX)

$(NAME_GFX): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIBRARY) $(DEBUG)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.c)
	@mkdir -p $(PATH_OBJ)
	$(CC) -c -o $@ $(CFLAGS) $^ $(DEBUG) $(INCLUDES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME_GFX)

re: fclean $(NAME_GFX)
