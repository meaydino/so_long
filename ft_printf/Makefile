NAME = libftprintf.a
CC= cc
FLAG = -Wall -Wextra -Werror

SRC = ft_format.c ft_printf.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(FLAG) -c $< -o $@

$(OBJ): ft_printf.h

clean:
	@rm -f  $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
