NAME= ft_ping
COMPILER= gcc 
FILES=	main.c \
		utils.c \
		options.c \
		check_ip.c

all: ${NAME}

${NAME}:
		${COMPILER} ${FILES} -o ${NAME}

clean:
		rm -f ${NAME}

re: clean all