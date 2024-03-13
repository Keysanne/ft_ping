NAME= ft_ping
COMPILER= gcc 
OBJS=	${FILES:.c=.o}
FILES=	main.c  \
		utils.c  \
		options.c \
		check_ip.c \
		time.c

all: ${NAME}

${NAME}: ${OBJS}
		${COMPILER} ${OBJS} -o ${NAME} -g -lm

${OBJS}: ${FILES}
		${COMPILER} -c ${FILES} -g -lm

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all