NAME 		=	./a.out

CC		=	gcc

CFLAGS		=	

LIBS		=	-lXext -lX11

LIBS_INC	=	-I $(MLX_PATH)

MLX_PATH	=	./minilibx-linux/

MLX		=	$(addprefix $(MLX_PATH), libmlx_Linux.a)

SRCS		=	main.c

OBJS		=	$(SRCS:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(MLX)
			$(CC) $(CFLAGS) $^ -o $@ $(MLX) $(LIBS) $(LIBS_INC)

$(OBJS):		$(SRCS)
			$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) $(LIBS_INC)

$(MLX):			
			$(MAKE) -C $(MLX_PATH)

clean:		
			rm -f $(OBJS)

fclean:			clean
			rm -f $(NAME)

re:			fclean all

test:			re
			./a.out

.PHONY:			re fclean all test

