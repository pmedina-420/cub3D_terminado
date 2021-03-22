SRC_BASE = ./code/
LIBFT_BASE = ./libs/libft/
GNL_BASE = ./libs/gnl/

SRCS 	= cub3d.c 						\
		  raycasting.c 			 		\
		  sprites.c 					\
		  fillpaths.c 					\
		  readmap.c 					\
		  map_utils.c 					\
		  get_paths.c 					\
		  textures.c 					\
		  key_actions.c 				\
		  positions.c 					\
		  pixel_rgb.c 					\
		  screenshot.c 					\
		  event_listeners.c 			\
		  utils.c 

SRCS_GNL = get_next_line.c 				\
		   get_next_line_utils.c 

SRCS_LIBFT	= ft_atoi.c 				\
			ft_bzero.c 					\
			ft_calloc.c 				\
		  ft_isalnum.c 					\
		  ft_isalpha.c 					\
		  ft_isdigit.c					\
		  ft_isprint.c					\
		  ft_isascii.c					\
		  ft_itoa.c 					\
		  ft_lstadd_back_bonus.c  		\
		  ft_lstadd_front_bonus.c 		\
		  ft_lstclear_bonus.c 			\
		  ft_lstdelone_bonus.c 			\
		  ft_lstiter_bonus.c  			\
		  ft_lstlast_bonus.c 			\
		  ft_lstmap_bonus.c 			\
		  ft_lstnew_bonus.c 			\
		  ft_lstsize_bonus.c 			\
		  ft_memccpy.c 					\
		  ft_memchr.c 					\
		  ft_memcmp.c 					\
		  ft_memcpy.c 					\
		  ft_memmove.c 					\
		  ft_memset.c 					\
		  ft_putchar_fd.c 				\
		  ft_putendl_fd.c 				\
		  ft_putnbr_fd.c 				\
		  ft_putstr_fd.c 				\
		  ft_split.c 					\
		  ft_strchr.c 					\
		  ft_strdup.c 					\
		  ft_strjoin.c 					\
		  ft_strlcat.c 					\
		  ft_strlcpy.c 					\
		  ft_strlen.c 					\
		  ft_strmapi.c 					\
		  ft_strncmp.c 					\
		  ft_strnstr.c 					\
		  ft_strrchr.c 					\
		  ft_strtrim.c 					\
		  ft_substr.c 					\
		  ft_tolower.c 					\
		  ft_toupper.c 

SRCS 		:= $(addprefix $(SRC_BASE), $(SRCS))
SRCS_LIBFT 	:= $(addprefix $(LIBFT_BASE), $(SRCS_LIBFT))
SRCS_GNL 	:= $(addprefix $(GNL_BASE), $(SRCS_GNL))

OBJS_GNL	= ${SRCS_GNL:.c=.o}
OBJS_LIBFT	= ${SRCS_LIBFT:.c=.o}
OBJS = ${SRCS:.c=.o}

LIBFT_PATH	= ./trash/
LIB_LIBFT	= -L$(LIBFT_PATH) -lft
LIBFT 		= $(LIBFT_PATH)$(NAME_LIBFT)
NAME_LIBFT	= libft.a
NAME		= ./cub3D
CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra -g
CUFLAGS 	= -lmlx -framework OpenGL -framework AppKit

$(NAME): $(LIBFT) ${OBJS}
		$(CC) $(OBJS) -o $(NAME) ${CUFLAGS} $(CFLAGS) $(LIB_LIBFT)

$(LIBFT): $(OBJS_GNL)
		make -sC $(LIBFT_BASE)
		$(RM) -r $(LIBFT_PATH)
		mkdir $(LIBFT_PATH)
		cp $(LIBFT_BASE)$(NAME_LIBFT) $(LIBFT_PATH)
		ar rc $(LIBFT_PATH)$(NAME_LIBFT) $(OBJS_GNL)

all:	$(NAME)

clean:
		@$(RM) $(OBJS) $(OBJS_LIBFT) $(OBJS_GNL)

fclean:	clean
		@$(RM) $(NAME) *.bmp $(LIBFT_BASE)$(NAME_LIBFT)
		@$(RM) -r $(LIBFT_PATH)
		@echo "\nSe ha limpiado todo correctamente"

re:	fclean all
		
run: 	all
		@clear
		@$(NAME) ./maps/map.cub

.PHONY:	all clean fclean re
