CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = fdf
LIBFT = libft/libft.a
LIBFT_DIR = ./libft
SRC = src/error.c src/get_next_line_utils.c src/get_next_line.c src/init_data.c  src/main.c \
src/parse_fdf_map.c src/parse_utils.c  src/parse_utils2.c  src/draw_map.c \
src/draw_map_utils.c src/draw_map_utils2.c src/draw_map_utils3.c src/draw_map_utils4.c src/hex_to_int.c \
src/press_key.c src/press_key2.c  src/draw_map_utils5.c \
 printf/ft_printf.c printf/print_c.c  printf/print_d.c printf/print_p.c printf/print_s.c printf/print_u.c printf/print_x.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -g -I/mlx_linux  -I/include -I/libft -O3 -c $< -o $@ 

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) -g $(OBJ) -L$(LIBFT_DIR) -lft -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ)
	make -C $(LIBFT_DIR) fclean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: clean fclean re all




