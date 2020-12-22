NAME = cube.out

LIBFT = libftprintf.a

MINILIBX = libmlx.dylib

INCLUDES = includes/

SRC = srcs/

FLAGS = -Wall -Wextra -Werror -L. -lftprintf -lmlx -g3 -fsanitize=address

CC = gcc $(FLAGS)

FILES = cubeddd.c \
		config/cub_parser.c config/resolution.c \
		config/texture.c config/map.c \
		config/check_map.c config/treat_sprite.c \
		engine/controls/key_control.c \
		engine/render/rendering.c engine/render/drawer.c \
		engine/controls/move_player.c engine/controls/move_camera.c \
		engine/render/sprite_init.c engine/player_manager.c \
		utils/initer.c utils/exit.c utils/save.c utils/paths.c

RM = rm -f

OBJ = $(addprefix $(SRC), $(FILES))

$(NAME): $(LIBFT) $(MINILIBX)
	@$(CC) $(OBJ) -o $@ -I$(INCLUDES) -Ilibftprintf/${INCLUDES} -Ilibft/${INCLUDES} -Iminilibx
	@printf "$(notdir $@) [\033[32m✔️\033[0m]\n"

$(MINILIBX):
	make -C minilibx/
	@cp minilibx/$(MINILIBX) .

$(LIBFT):
	make -C libftprintf/
	@cp libftprintf/$(LIBFT) .

all: $(NAME)

main: all
	@clear
	@./$(NAME) map.cub --save

clean:
	@make clean -C libftprintf/
	@make clean -C minilibx/
	@$(RM) $(LIBFT)
	@printf "$(LIBFT) [\033[31mX\033[0m]\n"
	@$(RM) $(MINILIBX)
	@printf "$(MINILIBX) [\033[31mX\033[0m]\n"

fclean: clean
	@make fclean -C libftprintf/
	@$(RM) $(NAME)
	@printf "$(NAME) [\033[31mX\033[0m]\n"

re: fclean all

.PHONY: all clean fclean re cube.out libftprintf.a main