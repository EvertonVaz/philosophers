# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 19:13:08 by egeraldo          #+#    #+#              #
#    Updated: 2024/03/09 16:13:25 by etovaz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# Colors Definition
GREEN = "\033[32;1m"
WHITE = "\033[37;1;4m"
COLOR_LIMITER = "\033[0m"

BIN_PATH = ./bin/

SRC_PATH = ./

M_SRC = ft_atoi.c     ft_isalpha.c  ft_memchr.c   ft_memset.c   ft_strlcpy.c \
	ft_strrch.c   ft_bzero.c    ft_isascii.c  ft_memcmp.c   ft_strchr.c \
	ft_strlen.c   ft_tolower.c  ft_calloc.c   ft_isdigit.c  ft_memcpy.c \
	ft_strdup.c   ft_strncmp.c  ft_toupper.c  ft_isalnum.c  ft_isprint.c \
	ft_memmove.c  ft_strlcat.c  ft_strnstr.c  ft_substr.c   ft_strjoin.c \
	ft_strtrim.c  ft_split.c    ft_itoa.c     ft_strmapi.c  ft_striteri.c \
	ft_putchar_fd.c  ft_putstr_fd.c  ft_putendl_fd.c  ft_putnbr_fd.c \
	ft_isnum.c ft_atol.c get_next_line.c ft_is_whitespace.c  ft_mtxlen.c \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
	ft_strcpy_delim.c ft_strjoin_char.c ft_remove_quotes.c char_to_str.c \
	ft_strcmp.c

M_OBJ = $(M_SRC:%.c=%.o)

OBJECTS = $(addprefix $(BIN_PATH), $(M_SRC:%.c=%.o))

HEADER = libft.h

FLAGS = -Wall -Wextra -Werror -g3

all: $(BIN_PATH) $(NAME)

$(NAME): $(OBJECTS)

$(BIN_PATH)%.o: $(SRC_PATH)%.c $(HEADER)
	@echo $(GREEN)[Compiling libft]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))$(COLOR_LIMITER)
	@cc $(FLAGS) -c $< -o $@
	@ar -rcs $(NAME) $@

$(BIN_PATH):
	@mkdir -p $(BIN_PATH)

clean:
	rm -rf $(BIN_PATH) $(B_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

rebonus: fclean all bonus

.PHONY:		all clean fclean re bonus rebonus