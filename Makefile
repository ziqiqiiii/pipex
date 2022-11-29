NAME		= pipex

# MANDATORY
SRC_DIR		= ./mandatory
OBJ_DIR		= ./obj
SRCS		= pipex.c path.c utils.c ft_utils.c 
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

# BONUS
B_SRC_DIR	= ./bonus
B_OBJ_DIR	= ./b_obj
B_SRCS		= pipex_bonus.c path_bonus.c utils_bonus.c children.c ft_utils.c
B_OBJS		= $(B_SRCS:%.c=$(B_OBJ_DIR)/%.o)

# GNL
GNL_DIR 	= ./get_next_line
GNL_SRCS	= get_next_line.c get_next_line_utils.c
GNL_OBJ		= $(GNL_SRCS:%.c=$(B_OBJ_DIR)/%.o)

CC			= gcc
CCD			= gcc
CFLAGS		= -Wall -Wextra -Werror -D BUFFER_SIZE=100

RM 			= rm -rf

INCLUDES	= -Iincludes -Ilibft -Iget_next_line
LIB			= -Llibft -lft


all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
		$(CCD) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIB) -o $@

libft/libft.a:
	@make all -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@$(CCD) $(INCLUDES) -c $< -o $@

$(B_OBJ_DIR)/%.o: $(B_SRC_DIR)/%.c
		@mkdir -p $(B_OBJ_DIR)
		@$(CCD) $(INCLUDES) -c $< -o $@

$(B_OBJ_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CCD) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(B_OBJS) $(GNL_OBJ) libft/libft.a
	$(CCD) $(CFLAGS) $(B_OBJS) $(GNL_OBJ) $(INCLUDES) $(LIB) -o $(NAME)

test:
	make && ./pipex infile "ls -l" "wc -l" outfile 

clean:
	$(RM) $(OBJ_DIR) $(B_OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re