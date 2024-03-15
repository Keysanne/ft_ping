NAME= ft_ping
COMPILER= gcc 
OBJS=	${FILES:.c=.o}
FILES=	main.c  \
		utils.c  \
		options.c \
		check_ip.c \
		time.c		\
		packet.c

all: ${NAME}

${NAME}: ${OBJS}
		${COMPILER} ${OBJS} -o ${NAME} -g -lm -lnet

${OBJS}: ${FILES}
		${COMPILER} -c ${FILES} -g -lm -lnet

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all