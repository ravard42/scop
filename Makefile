CC = gcc
NAME = scop
FLAGS = -Wall -Wextra -Werror
SRC = lib/glad/src/glad.c\
			src/main.c\
			src/init.c\
			src/init_tabs.c\
			src/event.c\
			src/load_shader.c\
			src/parser/parsing_tools.c\
			src/parser/verif_obj_file.c\
			src/parser/error.c\
			src/parser/load_parsing_struct.c\
			src/parser/load_vertex_struct.c\
			src/parser/parse.c\
			src/send_data_to_gpu.c\
			src/mouv_cam.c\
			src/transfo.c\
			src/texture_and_color.c\
			src/xpm_loader.c\
			src/exit.c\
	
OBJ = $(SRC:.c=.o)

INCL = -I lib/libft/include -I lib/glfw3/include -I lib/glad/include -I include/ -I f_xpm/
LIB = -L ./lib/libft -lft -L ./lib/glfw3 -lglfw3 -framework AppKit -framework IOKit -framework CoreVideo

all : $(NAME)

$(NAME) : ./lib/libft/libft.a $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(FLAGS) $(INCL) $(LIB)

./lib/libft/libft.a :
	make -C lib/libft

%.o : %.c
	$(CC) -o $@ -c $< $(FLAGS) $(INCL)

clean : 
	rm -f $(OBJ)
	make -C lib/libft/ fclean

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)
