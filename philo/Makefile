NAME	= 	philo

SRC 		=	main.c utils.c routine.c actions.c 

HDR		=	philo.h

CFLAGS		=	-Wall -Wextra -Werror -lpthread -g -fsanitize=address

# Regular Colors
#Black=\033[0;30m        # Black
#Red=\033[0;31m          # Red
Green=\033[0;32m        # Green
#Yellow=\033[0;33m       # Yellow
#Blue=\033[0;34m         # Blue
#Purple=\033[0;35m       # Purple
Cyan=\033[0;36m         # Cyan
White=\033[0;37m        # White

all: $(NAME)

$(NAME): $(SRC)
	@ cc $(CFLAGS) -o $(NAME) $(SRC)
	@ echo "${Green}philo ${White}is ready"

clean:
	@ /bin/rm -f $(OBJ)
	@ echo "${Cyan}object files${White}deleted"
	
fclean: clean
	@ /bin/rm -f $(NAME)
	@ echo "${Cyan}all files${White}deleted"

re: fclean all

.PHONY: all clean fclean re
