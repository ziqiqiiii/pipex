NAME		= pipex

CC			= gcc
CCD			= gcc -fsanitize=address
CFLAGS		= -Wall -Wextra -Werror

RM 			= rm -r

SRC_DIR	 	= ./src
OBJ_DIR		= ./obj

SRCS		= pipex.c path.c utils.c
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)


INCLUDES	= -Iincludes -Ilibft 
LIB			= -Llibft -lft


all: $(NAME)

$(NAME): $(OBJS) $(GNL_OBJ) libft/libft.a
		$(CCD) $(CFLAGS) $(OBJS) $(GNL_OBJ) $(INCLUDES) $(LIB) $(MLX) -o $@

libft/libft.a:
	@make all -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(INCLUDES) -c $< -o $@


test:
	make && ./pipex infile "ls -l" "wc -l" outfile 

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re