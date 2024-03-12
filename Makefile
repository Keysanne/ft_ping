NAME= ft_ping
COMPILER= gcc 
FILES=	main.c  \
		utils.c  \
		options.c \
		check_ip.c \
		time.c

all: ${NAME}

${NAME}:
		${COMPILER} ${FILES} -o ${NAME} -g -lm

clean:
		rm -f ${NAME}

re: clean all