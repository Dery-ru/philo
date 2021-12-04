NAME		= philo

HEADER_FILE	= includes/philo.h

HEADER		= -I includes/

SDIR		= ./

SRCS		= $(wildcard ./*.c)

BONUS		= 

OBJS		= ${SRCS:.c=.o}

BONUS_OBJS	= ${BONUS:.c=.o}

CC			= gcc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -g

all:		${NAME}

.c.o:	
		 	${CC} ${CFLAGS} $(HEADER) -c $< -o $(<:.c=.o)

$(NAME):	${OBJS} ${HEADER_FILE}
				$(CC) $(CFLAGS) $(HEADER) $(OBJS) -o $(NAME)
		
clean:
					${RM} ${OBJS} ${BONUS_OBJS}

fclean:		clean
					${RM} ${NAME}

re:					fclean all

.PHONY:		all clean fclean re bonus