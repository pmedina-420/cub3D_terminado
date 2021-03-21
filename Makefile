SRCS = ./code/cub3d.c ./code/raycasting.c ./code/sprites.c ./code/fillpaths.c ./code/readmap.c ./code/map_utils.c ./code/get_paths.c ./code/textures.c ./code/key_actions.c ./code/positions.c ./code/pixel_rgb.c ./code/screenshot.c ./code/event_listeners.c ./code/utils.c ./libs/gnl/get_next_line.c ./libs/gnl/get_next_line_utils.c ./libs/libft/ft_atoi.c ./libs/libft/ft_bzero.c ./libs/libft/ft_calloc.c ./libs/libft/ft_isalnum.c ./libs/libft/ft_isalpha.c ./libs/libft/ft_isascii.c ./libs/libft/ft_isdigit.c ./libs/libft/ft_isprint.c ./libs/libft/ft_itoa.c ./libs/libft/ft_lstadd_back_bonus.c ./libs/libft/ft_lstadd_front_bonus.c ./libs/libft/ft_lstclear_bonus.c ./libs/libft/ft_lstdelone_bonus.c ./libs/libft/ft_lstiter_bonus.c ./libs/libft/ft_lstlast_bonus.c ./libs/libft/ft_lstmap_bonus.c ./libs/libft/ft_lstnew_bonus.c ./libs/libft/ft_lstsize_bonus.c ./libs/libft/ft_memccpy.c ./libs/libft/ft_memchr.c ./libs/libft/ft_memcmp.c ./libs/libft/ft_memcpy.c ./libs/libft/ft_memmove.c ./libs/libft/ft_memset.c ./libs/libft/ft_putchar_fd.c ./libs/libft/ft_putendl_fd.c ./libs/libft/ft_putnbr_fd.c ./libs/libft/ft_putstr_fd.c ./libs/libft/ft_split.c ./libs/libft/ft_strchr.c ./libs/libft/ft_strdup.c ./libs/libft/ft_strjoin.c ./libs/libft/ft_strlcat.c ./libs/libft/ft_strlcpy.c ./libs/libft/ft_strlen.c ./libs/libft/ft_strmapi.c ./libs/libft/ft_strncmp.c ./libs/libft/ft_strnstr.c ./libs/libft/ft_strrchr.c ./libs/libft/ft_strtrim.c ./libs/libft/ft_substr.c ./libs/libft/ft_tolower.c ./libs/libft/ft_toupper.c
OBJS = ${SRCS:.c=.o}

NAME	= cub3d.a
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra -g
.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		make -sC ./libs/libft/
		cp ./libs/libft/libft.a .
		ar -rc  $(NAME) $(OBJS)
		ranlib $(NAME)

all:	$(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		@$(RM) $(NAME) cub3D *.a cub3d.bmp libs/libft/libft.a
		@echo "\nSe ha limpiado todo correctamente"

re:	fclean all
		@clear
		@gcc -lmlx -framework OpenGL -framework AppKit -o "cub3D" $(NAME)
		@./cub3D ./maps/map.cub

run: 
	@clear
	@./cub3D ./maps/map.cub

.PHONY:	all clean fclean re
