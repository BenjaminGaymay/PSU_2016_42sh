##
## Makefile for 42sh in /home/benoit.pingris/delivery/PSU/PSU_2016_42sh
##
## Made by benoit pingris
## Login   <benoit.pingris@epitech.net>
##
## Started on  Thu May 18 09:42:38 2017 benoit pingris
## Last update Thu Jun  1 15:21:48 2017 Benjamin GAYMAY
##

CC	=	gcc

NAME	=	42sh

SRC	=	./srcs/my_printf/flag.c				\
		./srcs/my_printf/hexa.c				\
		./srcs/my_printf/octal_bin.c			\
		./srcs/my_printf/my_printf.c			\
		./srcs/my_printf/my_putstr_printf.c		\
		./srcs/my_printf/my_strlen_printf.c		\
		./srcs/my_printf/my_put_nbr_printf.c		\
		./srcs/my_printf/my_putchar_printf.c		\
		./srcs/my_printf/my_put_nbr_unsigned.c		\
		./srcs/my_fprintf/fflag.c			\
		./srcs/my_fprintf/fhexa.c			\
		./srcs/my_fprintf/my_fprintf.c			\
		./srcs/my_fprintf/foctal_bin.c			\
		./srcs/my_fprintf/my_putstr_fprintf.c		\
		./srcs/my_fprintf/my_strlen_fprintf.c		\
		./srcs/my_fprintf/my_putchar_fprintf.c		\
		./srcs/my_fprintf/my_put_nbr_fprintf.c		\
		./srcs/my_fprintf/my_put_nbr_funsigned.c	\
		./srcs/builtins/exit.c				\
		./srcs/builtins/echo.c				\
		./srcs/builtins/cd.c				\
		./srcs/builtins/setenv.c			\
		./srcs/builtins/alias.c				\
		./srcs/builtins/where.c				\
		./srcs/builtins/which.c				\
		./srcs/builtins/create_alias.c			\
		./srcs/builtins/check_builtins.c		\
		./srcs/builtins/do_builtins.c			\
		./srcs/builtins/do_builtins_2.c			\
		./srcs/builtins/do_builtins_3.c			\
		./srcs/builtins/set.c				\
		./srcs/builtins/var_basics.c			\
		./srcs/array/use_array.c			\
		./srcs/array/copy_array.c			\
		./srcs/array/inhib.c				\
		./srcs/array/my_showtab.c			\
		./srcs/useful/get_next_line.c			\
		./srcs/useful/quotes.c				\
		./srcs/useful/my_calloc.c			\
		./srcs/useful/chained_list.c			\
		./srcs/useful/my_itoa.c				\
		./srcs/useful/inhib.c				\
		./srcs/useful/my_putchar.c			\
		./srcs/useful/replace_line.c			\
		./srcs/useful/my_putstr.c			\
		./srcs/operator/pipe.c				\
		./srcs/operator/operator.c			\
		./srcs/operator/operator_basics.c		\
		./srcs/operator/redirection.c			\
		./srcs/operator/redirect_basic.c		\
		./srcs/operator/redirect_error.c		\
		./srcs/operator/is_redir.c			\
		./srcs/main.c					\
		./srcs/mysh.c					\
		./srcs/prompt.c					\
		./srcs/path.c					\
		./srcs/fork.c					\
		./srcs/ptr_fc.c					\
		./srcs/ps1.c					\
		./srcs/parent.c					\
		./srcs/check_command.c				\
		./srcs/my_get.c					\
		./srcs/variables.c				\
		./srcs/string/str.c				\
		./srcs/string/my_strcat.c			\
		./srcs/string/my_strlen.c			\
		./srcs/string/my_getnbr.c			\
		./srcs/string/my_strcmp.c			\
		./srcs/string/my_strcpy.c			\
		./srcs/string/my_strstr.c			\
		./srcs/string/my_strncat.c			\
		./srcs/string/my_strncmp.c			\
		./srcs/string/clear_my_str.c			\
		./srcs/string/my_str_isnum.c			\
		./srcs/string/my_add_slash.c			\
		./srcs/string/error.c				\
		./srcs/string/my_malloc_strncpy.c		\
		./srcs/parsing/quote.c

OBJ	=	$(SRC:.c=.o)

CFLAGS +=	-I./include -W -Wall -Wextra -Werror

RM	=	rm -f

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
