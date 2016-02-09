# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/22 13:15:39 by gbersac           #+#    #+#              #
#    Updated: 2014/06/06 18:09:18 by gbersac          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# BASIC VARIABLES															   #
################################################################################

SRCS				:= main.cpp io.cpp connect.cpp env.cpp interpret_cmd.cpp \
						cmds.cpp

PATH_OBJ			:= obj
PATH_SRC			:= src
PATH_INC			:= inc

CFLAGS				:= -Wall -Wextra -Werror
OBJECTS				:= $(patsubst %.cpp, $(PATH_OBJ)/%.o, $(SRCS))

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

all: $(NAME_CLIENT)

$(NAME_CLIENT): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LIBRARY) $(DEBUG)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.cpp)
	@mkdir -p $(PATH_OBJ)
	$(CXX) -c -o $@ $(CFLAGS) $^ $(DEBUG) -x c $(INCLUDES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME_CLIENT)

re: fclean $(NAME_CLIENT)
