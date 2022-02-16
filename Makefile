NAME 			=	./a.out

CC				=	gcc

CFLAGS			=	-MMD -g3 -Wall -Wextra -Werror

SRCS_PATH		=	./sources/

OBJS_PATH		=	./objs/

LIBS			=	-lXext -lX11

LIBFT			=	./libft/libft.a

LIBFT_PATH		=	./libft/

INC				=	-I $(MLX_PATH)\
					-I ./includes/\
					-I ./libft/includes

MLX_PATH		=	./minilibx-linux/

MLX				=	$(addprefix $(MLX_PATH), libmlx_Linux.a)

SRCS			=	ft_put_pixel_img.c		\
					ft_fdf_parse.c			\
					main.c
					

OBJS			=	$(addprefix $(OBJS_PATH),$(SRCS:.c=.o))

DEPS			=	$(OBJS:.o=.d)

all:				$(NAME)

$(NAME):			$(OBJS) $(MLX) $(LIBFT)
					$(CC) $(CFLAGS) $^ -o $@ $(MLX) $(LIBS) $(INC) $(LIBFT)

$(OBJS_PATH)%.o:	$(SRCS_PATH)%.c
					@mkdir -p $(OBJS_PATH)
					$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) $(INC)

$(MLX):			
					$(MAKE) -C $(MLX_PATH)

$(LIBFT):			
					$(MAKE) -C $(LIBFT_PATH)

clean:		
					rm -rf $(OBJS_PATH)
					@$(MAKE) -C $(LIBFT_PATH) clean

fclean:				clean
					$(MAKE) -C $(LIBFT_PATH) fclean
					rm -f $(NAME)

re:					fclean all

test:				all
					./a.out

valgrind:			re
					valgrind --leak-check=full --show-leak-kinds=all -s ./a.out -D BUFFER_SIZE=100

.PHONY:				re fclean all test

