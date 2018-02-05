# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/08 07:06:09 by angavrel          #+#    #+#              #
#    Updated: 2018/02/05 15:40:47 by angavrel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######### MISC ########

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
LIBFT_PATH	=	./libft/
INCL		=	./incl/

CFLAGS		=	-I$(LIBFT_PATH)incl/ -I $(INCL) $(FLAGS)


LINKS		=	-L $(LIBFT_PATH) -lft

####### CHECKER #######

NAME_CHK	=	checker
NAME_PSWAP	=	push_swap

### PATH ###

SRCS_PATH	=	srcs/

SRCS_CHK	=	main.c \

SRCS_CHK2	=	$(addprefix $(SRCS_PATH)srcs_check/, $(SRCS_CHK))

SRCS_PSWAP	=	main.c \

SRCS_PSWAP2	=	$(addprefix $(SRCS_PATH)srcs_pswap/, $(SRCS_PSWAP)) \

OBJ_CHK		=	$(SRCS_CHK2:.c=.o)
OBJ_PSWAP	=	$(SRCS_PSWAP2:.c=.o)

######### RULES #######

all : libs $(NAME_CHK) $(NAME_PSWAP)

$(NAME_CHK) : $(OBJ_CHK)
	$(CC) -o $(NAME_CHK) $(OBJ_CHK) $(CFLAGS) $(LINKS)

$(NAME_PSWAP) : $(OBJ_PSWAP)
	$(CC) -o $(NAME_PSWAP) $(OBJ_PSWAP) $(CFLAGS) $(LINKS)

clean:
	@/bin/rm -rf $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean
	@echo "\033[31mObjects files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@/bin/rm -rf $(NAME_CHK)
	@/bin/rm -rf $(NAME_PSWAP)
	@/bin/rm -rf $(LIBFT_PATH)libftprintf.a
	@echo "\033[31mBin \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all

libs:
	@make -C $(LIBFT_PATH)

.PHONY: all re clean fclean libs
