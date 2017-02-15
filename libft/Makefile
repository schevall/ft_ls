# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schevall <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/10 10:27:19 by schevall          #+#    #+#              #
#    Updated: 2017/02/08 15:21:30 by schevall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAG = -Wall -Wextra -Werror
OPTION = -c
SRC = ft_atoi.c\
	  ft_isalnum.c\
	  ft_isalpha.c\
	  ft_bzero.c\
	  ft_isascii.c\
	  ft_isdigit.c\
	  ft_isprint.c\
	  ft_isspace.c\
	  ft_lstadd.c\
	  ft_lstiter.c\
	  ft_lstdelone.c\
	  ft_lstdel.c\
	  ft_memalloc.c\
	  ft_itoa.c\
	  ft_lstnew.c\
	  ft_memchr.c\
	  ft_memccpy.c\
	  ft_lstmap.c\
	  ft_memcmp.c\
	  ft_memdel.c\
	  ft_memcpy.c\
	  ft_putchar.c\
	  ft_putchar_fd.c\
	  ft_putendl.c\
	  ft_putendl_fd.c\
	  ft_memset.c\
	  ft_memmove.c\
	  ft_putstr.c\
	  ft_putnbr.c\
	  ft_putstr_fd.c\
	  ft_putnbr_fd.c\
	  ft_strcat.c\
	  ft_strclr.c\
	  ft_strchr.c\
	  ft_strcmp.c\
	  ft_strdel.c\
	  ft_strcpy.c\
	  ft_striter.c\
	  ft_strdup.c\
	  ft_strequ.c\
	  ft_striteri.c\
	  ft_strjoin.c\
	  ft_strnjoin.c\
	  ft_strlen.c\
	  ft_strlcat.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_strncat.c\
	  ft_strncpy.c\
	  ft_strncmp.c\
	  ft_strnew.c\
	  ft_strnstr.c\
	  ft_strnequ.c\
	  ft_strrchr.c\
	  ft_strstr.c\
	  ft_strsub.c\
	  ft_tolower.c\
	  ft_toupper.c\
	  ft_strtrim.c\
	  ft_strsplit.c\
	  get_next_line.c\
	  ft_power.c\
	  ft_nbrlen.c\
	  ft_strcnew.c\
	  ft_strupcase.c\
	  ft_sort_params.c\

OBJ_NAME = $(SRC:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
OBJ_PATH = obj/

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	make -C ./printf/

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p obj
	@gcc -c $(FLAG) -o $@ $<

clean:
	@make clean -C ./printf/
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@make fclean -C ./printf/
	@/bin/rm -f $(NAME)

re: fclean all
