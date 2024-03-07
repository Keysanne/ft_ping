NAME= ft_ping
COMPILER= gcc 
FILES=	main.c \
		utils.c

all: ${NAME}

${NAME}:
		${COMPILER} ${FILES} -o ${NAME}

clean:
		rm ${NAME}

re: clean all