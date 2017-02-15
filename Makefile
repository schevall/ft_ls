# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schevall <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/10 10:27:19 by schevall          #+#    #+#              #
#    Updated: 2017/02/11 15:53:42 by schevall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAG = -Wall -Wextra -Werror
OPTION = -c
SRC = main_ft_ls.c\
	  option_parser.c\
	  print_dir.c\
	  print_file.c\
	  add_node.c\
	  create_elem.c\
	  get_spec_for_l_opt.c\
	  tools.c\
	  print_acl.c\
	  ls_error.c\
	  free_tree.c\

OBJ_NAME = $(SRC:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
OBJ_PATH = obj/

$(NAME): $(OBJ)
	make -C ./libft/
	@gcc -o $(NAME) -L ./libft -lft -L ./libft/printf/ -lftprintf $(FLAG) $(OBJ)

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p obj
	@gcc -c $(FLAG) -o $@ $<

clean:
	@make clean -C ./libft/
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@make fclean -C ./libft/
	@/bin/rm -f $(NAME)

re: fclean all
