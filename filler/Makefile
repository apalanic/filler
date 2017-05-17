# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apalanic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/15 14:06:16 by apalanic          #+#    #+#              #
#    Updated: 2017/03/15 14:24:53 by apalanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = filler

FLAGS = -Wall -Wextra -Werror
LIB = -L ./libft/ -lft

SRC =	main.c \
		filler.c \

SRCDIR = ./src/
OBJDIR = ./obj/
OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

all: obj $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@make -C libft/
	gcc $(FLAGS) -o $@ $(OBJ) $(LIB)

clean:
	@make -C libft/ clean
	rm -rf $(OBJDIR)

fclean: clean
	@make -C libft/ fclean
	rm -f $(NAME)

re: fclean all
