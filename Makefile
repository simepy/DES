# @Author: sime
# @Date:   November 12th 2018, 9:10:43 pm
# @Last modified by:   sime
# @Last modified time: November 28th 2018, 7:35:46 pm



SRC	= main-des.c \
			key-des.c \
			msg-des.c \
			utils-des.c

OBJ	= $(SRC:.c=.o)

NAME	= my_des

CFLAGS	= -Wextra -Wall

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc $(OBJ) -o $(NAME) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
