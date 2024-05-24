# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/19 17:27:27 by jhughes           #+#    #+#              #
#    Updated: 2024/05/24 18:13:14 by jhughes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

COMPILER	= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INCL)
INCL		= includes/

SRC_DIR		= src/
O_DIR		= obj/

C_IO		= ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				get_next_line.c
C_IO_PRINTF	= ft_printf.c ft_printf_utils.c print_i.c print_scp.c print_u.c put_e.c
C_LIST		= ft_lstnew.c ft_lstsize.c ft_lstlast.c \
				ft_lstadd_front.c ft_lstadd_back.c ft_lstdelone.c\
				ft_lstclear.c ft_lstiter.c ft_lstmap.c
C_MEM		= ft_calloc.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
				ft_memmove.c ft_memchr.c ft_memcmp.c
C_STR		= ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strconcat.c \
				ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_strfind.c \
				ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_split_ws.c\
				ft_strmapi.c ft_striteri.c ft_strdup.c \
				ft_strarr_len.c ft_strarr_clear.c ft_strarr_resize.c
C_TYPE		= ft_atoi.c ft_itoa.c ft_toupper.c ft_tolower.c \
				ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
				ft_isspace.c ft_isxdigit.c

C_FILES		= $(C_IO) $(C_IO_PRINTF) $(C_LIST) $(C_MEM) $(C_STR) $(C_TYPE)
C_FILES_DIR	= $(addprefix io/, $(C_IO)) $(addprefix io/printf/, $(C_IO_PRINTF)) \
				$(addprefix lst/, $(C_LIST)) $(addprefix mem/, $(C_MEM)) \
				$(addprefix str/, $(C_STR)) $(addprefix type/, $(C_TYPE))
O_FILES		= $(C_FILES:.c=.o)
O_DEP		= $(addprefix $(O_DIR), $(O_FILES))

all: $(NAME)

clean:
	rm -rf $(O_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(O_DEP)
	ar -rcs $(NAME) $(O_DEP)

$(O_DIR)%.o:  src/io/%.c
	@mkdir -p $(O_DIR)
	$(COMPILER) -c $(CFLAGS) $< -o $@

$(O_DIR)%.o:  src/io/printf/%.c
	@mkdir -p $(O_DIR)
	$(COMPILER) -c $(CFLAGS) $< -o $@

$(O_DIR)%.o:  src/lst/%.c
	@mkdir -p $(O_DIR)
	$(COMPILER) -c $(CFLAGS) $< -o $@

$(O_DIR)%.o:  src/mem/%.c
	@mkdir -p $(O_DIR)
	$(COMPILER) -c $(CFLAGS) $< -o $@

$(O_DIR)%.o:  src/str/%.c
	@mkdir -p $(O_DIR)
	$(COMPILER) -c $(CFLAGS) $< -o $@

$(O_DIR)%.o:  src/type/%.c
	@mkdir -p $(O_DIR)
	$(COMPILER) -c $(CFLAGS) $< -o $@

.PHONY: all clean fclean re
