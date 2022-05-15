SRCS = ft_printf.c

OBJS = $(SRCS:.c=.o)

NAME =	libftprintf.a

CFLAGS	= -Wall -Werror -Wextra

$(NAME)	: $(OBJS)
		ar rcs $(NAME) $(OBJS)

all	: $(NAME)

clean :
		rm -f $(OBJS)

fclean : clean
		rm -f $(NAME)

re : fclean all
