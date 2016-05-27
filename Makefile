# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssicard <ssicard@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/20 16:17:18 by ssicard           #+#    #+#              #
#    Updated: 2016/05/07 16:38:45 by ssicard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIB = ls.a

INC_DIR = includes

CC = gcc

CFLAGS = -I$(INC_DIR)

SOURCES = link_list.c\
		  link_list2.c\
		  link_list3.c\
		  sort_list.c\
		  init.c\
		  try.c\
		  utils.c\
		  show.c\
		  data.c\

SRC = $(addprefix sources/,$(SOURCES))

OBJ = $(SRC:.c=.o)

all : $(NAME) $(LIB)

$(NAME) : $(LIB)
	@$(CC) -o $(NAME) main.c $(LIB) $(CFLAGS) libft/libft.a libft/libftprintf.a
	@echo "MiniOns Arrived!"
	@echo "A New Challenger!"

$(LIB) : $(OBJ)
	@ar -r $(LIB) $(OBJ)
	@ranlib $(LIB)
	@echo "Cpt. ft_ls Lib. Arrived."

clean :
	@rm -rf $(OBJ)
	@echo "MiniOns Died!"

fclean : clean
	@rm -rf $(NAME) $(LIB)
	@echo "All's Destroyed! R.I.P :'("

re : fclean all
	@echo "And The Rain Against! ^^"

.PHONY: all clean fclean re
