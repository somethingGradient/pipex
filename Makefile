# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akitty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 15:03:23 by akitty            #+#    #+#              #
#    Updated: 2022/03/07 15:03:25 by akitty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

#NAME_B		=	pipex_bonus

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

SRC			=	src/main.c src/utils.c

#SRC_B		=	pipex_bonus.c

OBJ			=	$(SRC:.c=.o)

#OBJ_B		=	$(SRC_B:.c=.o)

LIBFT_PATH	=	./libft

LIBFT		=	./libft/libft.a

all:		$(NAME)

#bonus:		$(NAME_B)

$(NAME):	$(OBJ)
			$(MAKE) all -C $(LIBFT_PATH)
			$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

#$(NAME_B):	$(OBJ_B)
#			$(MAKE) all -C $(LIBFT_PATH)
#			$(CC) $(FLAGS) $(OBJ_B) $(LIBFT) -o $(NAME_B)

%.o:		%.c
			$(CC) -c $(FLAGS) -o $@ $<

clean:
			$(MAKE) clean -C $(dir $(LIBFT))
			rm -rf $(OBJ) $(OBJ_B)

fclean: 	clean
			$(MAKE) fclean -C $(dir $(LIBFT))
			rm -rf $(NAME) $(NAME_B)

re:			fclean all

.PHONY:		all bonus clean fclean re
