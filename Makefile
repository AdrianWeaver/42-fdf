<<<<<<< HEAD
NAME 			=	./fdf
=======
NAME 			=	./a.out
>>>>>>> d87b4cc571e9795d089779e7d81b33522b087848

CC				=	gcc

CFLAGS			=	-MMD -g3 -Wall -Wextra -Werror

SRCS_PATH		=	./sources/

OBJS_PATH		=	./objs/

LIBS			=	-lXext -lX11 -lm

LIBFT			=	./libft/libft.a

LIBFT_PATH		=	./libft/

INC				=	-I $(MLX_PATH)\
					-I ./includes/\
					-I ./libft/includes

MLX_PATH		=	./minilibx-linux/

MLX				=	$(addprefix $(MLX_PATH), libmlx_Linux.a)

SRCS			=	ft_put_pixel_img.c		\
					ft_parse_fdf.c			\
					ft_check_keys.c			\
					ft_key_functions.c		\
					ft_free_map.c			\
					ft_bresenham.c			\
					ft_draw.c				\
					ft_fdf_get.c			\
					ft_gradient.c			\
					ft_get_gradient.c		\
					main.c
					

OBJS			=	$(addprefix $(OBJS_PATH),$(SRCS:.c=.o))

DEPS			=	$(OBJS:.o=.d)

SILENT			=	--no-print-directory

all:				$(NAME)

$(NAME):			$(OBJS) $(MLX) $(LIBFT)
					@$(CC) $(CFLAGS) $^ -o $@ $(MLX) $(LIBS) $(INC) $(LIBFT)
					@echo "\33[1;32mLinking done.\33[m"

$(OBJS_PATH)%.o:	$(SRCS_PATH)%.c
					@mkdir -p $(OBJS_PATH)
					@$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) $(INC)
					@echo "\33[1;32mObj compiled \33[musing flag $(CFLAGS)"

$(MLX):			
					@$(MAKE) $(SILENT) -C $(MLX_PATH)
					@echo "\33[0;32m MLX COMPILED! \33[m"

$(LIBFT):			
					@$(MAKE) $(SILENT) -C $(LIBFT_PATH)

clean:		
					@rm -rf $(OBJS_PATH)
					@$(MAKE) $(SILENT) -C $(LIBFT_PATH) clean
					@echo "\33[0;36mCleaned objects and dependencies. \33[m"

fclean:				clean
					@$(MAKE) $(SILENT) -C $(LIBFT_PATH) fclean
					@rm -f $(NAME)
					@echo "\33[0;36mEverything is neat. \33[m"

re:					fclean all

retest:				re
<<<<<<< HEAD
					./fdf

test:				all
					./fdf test_maps/t1.fdf

valgrind:			re
					valgrind --leak-check=full --show-leak-kinds=all -s ./fdf test_maps/42.fdf
=======
					./a.out

test:				all
					./a.out test_maps/42powa.fdf

valgrind:			re
					valgrind --leak-check=full --show-leak-kinds=all -s ./a.out test_maps/42.fdf
>>>>>>> d87b4cc571e9795d089779e7d81b33522b087848

-include $(DEPS)

.PHONY:				re fclean all test
