NAME		= philo_bonus

HEADER_FILE	= includes/philo_bonus.h

HEADER		= -I includes/

BONUS		= $(wildcard ./*.c)

OBJS		= ${BONUS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror -g #remove -g flag

all:		${NAME}

.c.o:
			gcc ${CFLAGS} ${HEADER} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS} ${HEADER_FILE}
				gcc ${CFLAGS} ${HEADER} ${OBJS} -o ${NAME}
clean:
			rm -rf ${OBJS}

fclean:		clean
				rm -rf ${NAME}

re:				fclean all

.PHONY:		all clean fclean re
