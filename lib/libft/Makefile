CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRC =	src/ft_printf/ft_printf.c\
		src/ft_printf/ft_sprintf.c\
		src/ft_printf/extract_specifier.c\
		src/ft_printf/conv.c\
		src/ft_printf/c_conv.c\
		src/ft_printf/s_conv.c\
		src/ft_printf/d_conv.c\
		src/ft_printf/oux_conv.c\
		src/ft_printf/bin_conv.c\
		src/ft_printf/undefined_conv.c\
		src/ft_printf/tools.c\
		src/ft_printf/str_tools.c\
		src/ft_printf/write.c\
		src/ft_printf/put_buffer.c\
		src/ft_printf/malloc.c\
		src/ft_printf/utf_32_to_8.c\
		src/ft_memalloc.c\
		src/ft_strcpy.c\
		src/ft_strncpy.c\
		src/ft_strcat.c\
		src/ft_strchr.c\
		src/get_next_line.c\
		src/ft_strdup.c\
		src/ft_strsplit.c\
		src/malloc_free_tools.c\
		src/ft_strcmp.c\
		src/ft_strncmp.c\
		src/ft_toupper.c\
		src/ft_atoi.c\
		src/rm_begin_whitespace.c\
		src/rm_multi_whitespace.c\

OBJ = $(SRC:.c=.o)
INCLUDE = ./include/

all: $(NAME)

$(NAME): $(OBJ)
	ar -r $(NAME) $^

%.o: %.c
	$(CC) -o $@ -c $< -I $(INCLUDE) $(FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
