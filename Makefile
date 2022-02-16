NAME 		=	./a.out

CC		=	gcc

CFLAGS		=	-g3

LIBS		=	-lXext -lX11

LIBFT		=	./libft/libft.a -I ./libft/includes

LIBS_INC	=	-I $(MLX_PATH)\
				-I ./libft/includes

MLX_PATH	=	./minilibx-linux/

MLX		=	$(addprefix $(MLX_PATH), libmlx_Linux.a)

SRCS		=	main.c

OBJS		=	$(SRCS:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(MLX)
			$(CC) $(CFLAGS) $^ -o $@ $(MLX) $(LIBS) $(LIBS_INC) $(LIBFT)

$(OBJS):		$(SRCS)
			$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) $(LIBS_INC)

$(MLX):			
			$(MAKE) -C $(MLX_PATH)

clean:		
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

test:		re
			./a.out

.PHONY:			re fclean all test

