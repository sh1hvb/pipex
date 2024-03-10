CC = cc
CFLAGS = -Wall -Wextra -Werror 
RM = rm -rf

NAME = pipex
BONUS = pipexB

SRCS = Mandatory/main.c Mandatory/utils.c

BONUS_SRCS = bonus/main_bonus.c bonus/utils_bonus.c bonus/handle_error.c

OBJS = $(SRCS:.c=.o)
BOBJ = $(BONUS_SRCS:.c=.o)

all: ${NAME} ${BONUS}

${NAME}: ${OBJS} libft/libft.a
	${CC} ${CFLAGS} -o $@ $^

${BONUS}: ${BOBJ} libft/libft.a
	${CC} ${CFLAGS} -o $@ $^

libft/libft.a:
	${MAKE} -C ./libft

clean:
	${MAKE} -C ./libft clean
	${RM} ${OBJS} ${BOBJ}

fclean: clean
	${MAKE} -C ./libft fclean
	${RM} ${NAME} ${BONUS}

re: fclean all
