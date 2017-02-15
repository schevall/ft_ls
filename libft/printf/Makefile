# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schevall <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/10 10:34:27 by schevall          #+#    #+#              #
#    Updated: 2017/02/08 15:21:35 by schevall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAG = -Wall -Wextra -Werror

OPTION = -c

SRC = ft_printf.c\
	  format_tree.c\
	  format_for_signed.c\
	  tools_for_signed.c\
	  format_for_unsigned.c\
	  nbrlen_base.c\
	  tools_for_unsigned.c\
	  tools_for_pconv.c\
	  format_for_string.c\
	  format_for_char.c\
	  format_for_wchar.c\
	  format_for_wstring.c\
	  tools_for_wstring.c\
	  detect_conv_type.c\
	  get_arg_from_ap_list.c\
	  get_param.c\
	  is_params.c\

OBJ_NAME = $(SRC:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
OBJ_PATH = obj/

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p obj
	@gcc -c $(FLAG) -o $@ $<

clean:
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@/bin/rm -f $(NAME)

re : fclean all

