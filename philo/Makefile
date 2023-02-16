NAME					=	philo
CC						=	cc
FLAGS					=	-Wall -Wextra -Werror -g
RM						=	rm -f

# LIBRARY
PTHREAD_LIB				=	pthread

# PATH
OBJ_PATH  = build/
HEADER = includes/
SRC_PATH  = sources/
LIBFT = libft/

### All sources ###
SOURCES		=	main.c parsing.c routine.c time_meals.c utils.c utils_libft.c

### All objects ###

SRCS = $(addprefix $(SRC_PATH),$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH),$(SOURCES:.c=.o))
DEPS = $(addprefix $(OBJ_PATH),$(SOURCES:.c=.d))

### COLORS ###
NOC         = \033[0m
GREEN       = \033[1;32m
CYAN        = \033[1;36m

all:	header tmp $(NAME)

tmp:
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH) $(SRC_PATH)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ -l $(PTHREAD_LIB) -o $(NAME)
	@echo "$(GREEN)Project compiled succesfully$(NOC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) -MMD $(FLAGS) -c -o $@ $<
	@echo "$(CYAN)Creation of object file -> $(CYAN)$(notdir $@)... $(GREEN)[Done]$(NOC)"

clean :
	@echo "clean: $(GREEN)Cleaning object files$(NOC)"
	rm -rf $(OBJ_PATH)

fclean : clean
	@echo "fclean: $(GREEN)Cleaning executable$(NOC)"
	rm -f $(NAME)

re : fclean all

header:
	clear
	@echo "$(CYAN) $$HEADER_PROJECT"

-include $(DEPS)

.PHONY: all clean fclean re

define HEADER_PROJECT


 ______   __  __     __     __         ______     ______     ______     ______   __  __     ______     ______     ______    
/\  == \ /\ \_\ \   /\ \   /\ \       /\  __ \   /\  ___\   /\  __ \   /\  == \ /\ \_\ \   /\  ___\   /\  == \   /\  ___\   
\ \  _-/ \ \  __ \  \ \ \  \ \ \____  \ \ \/\ \  \ \___  \  \ \ \/\ \  \ \  _-/ \ \  __ \  \ \  __\   \ \  __<   \ \___  \  
 \ \_\    \ \_\ \_\  \ \_\  \ \_____\  \ \_____\  \/\_____\  \ \_____\  \ \_\    \ \_\ \_\  \ \_____\  \ \_\ \_\  \/\_____\ 
  \/_/     \/_/\/_/   \/_/   \/_____/   \/_____/   \/_____/   \/_____/   \/_/     \/_/\/_/   \/_____/   \/_/ /_/   \/_____/ 
                                                                                                                            


endef
export HEADER_PROJECT
