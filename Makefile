# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/22 13:15:39 by gbersac           #+#    #+#              #
#    Updated: 2016/01/06 12:23:53 by gbersac          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# BASIC VARIABLES															   #
################################################################################

export DEBUG		:= -g -O0
export CC			:= clang

################################################################################
# LIBRARY VARIABLES															   #
################################################################################

export DIR_FT		:= libft
export DIR_GEN		:= gen
export LIB_LINKER	:= -L../$(DIR_GEN) -lgen -L../$(DIR_FT) -lft

export NAME_SERVEUR	:= serveur
DIR_SERVEUR			:= ser
export DIR_LIB		:= $(DIR_FT) $(DIR_GEN)

APPS				:= $(DIR_SERVEUR)

################################################################################
# RULES																		   #
################################################################################

.PHONY: all $(APPS) $(DIR_LIB)

all:  $(APPS)

$(DIR_LIB):
	@echo
	@echo \	MAKE $(RULE) in directory : $@
	@$(MAKE) --directory=$@  $(RULE)

$(DIR_SERVEUR): $(DIR_LIB)
	@echo
	@echo \	MAKE $(RULE) in directory : $@
	@$(MAKE) --directory=$@  $(RULE)
	@echo
	@rm -f $(NAME_SERVEUR)
	@cp -n $(DIR_SERVEUR)/$(NAME_SERVEUR) . || :

clean:
	make RULE=clean

fclean:
	make RULE=fclean

re:
	make RULE=re

