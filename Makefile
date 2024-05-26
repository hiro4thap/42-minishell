NAME		= minishell

COMPILER	= cc
CFLAGS		= -Wall -Wextra -Werror
INCL		= inc/

SRC_DIR		= src/
O_DIR		= obj/

INCL_LIBFT	= lib/libft/includes/
LINK_LIBFT	= lib/libft/

INCL_RL 	= /usr/local/opt/readline/include/
LINK_RL		= /usr/local/opt/readline/lib

LIBFT		= $(addprefix $(LINK_LIBFT), libft.a)
LIBS		= -L$(LINK_LIBFT) -lft -L$(LINK_RL) -lreadline

C_FILES		= main.c validation.c execute.c checker.c utils.c parse.c redirection.c  \
				builtin_cd.c builtin_echo.c builtin_env.c builtin_exit.c \
				builtin_export.c builtin_pwd.c builtin_unset.c env_utils.c \
				signal.c terminal.c
C_FILES_DIR	= $(addprefix $(SRC_DIR), $(C_FILES)) 
O_FILES		= $(C_FILES:.c=.o)
O_FILES_DIR	= $(addprefix $(O_DIR), $(O_FILES))

all: $(NAME)

clean:
	make -C lib/libft/ clean
	rm -rf $(O_DIR)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all

$(NAME): $(O_FILES_DIR)
	make -C $(LINK_LIBFT)
	$(COMPILER) $(CFLAGS) -I$(INCL) -I$(INCL_LIBFT) -I$(INCL_RL) $(O_FILES_DIR) $(LIBS) -o $@

$(O_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p obj/
	$(COMPILER) $(CFLAGS) -I$(INCL) -I$(INCL_LIBFT) -I$(INCL_RL) -c $< -o $@

debug: $(C_FILES_DIR)
	$(COMPILER) $(CFLAGS) -I$(INCL) -I$(INCL_LIBFT) -I$(INCL_RL) $(LIBS) $(C_FILES_DIR) -g -o $@

.PHONY: all clean fclean re
