NAME					=	philo
CC						=	cc
FLAGS					=	-Wall -Wextra -Werror -g
RM						=	rm -f

# LIBRARY
PTHREAD_LIB				=	pthread

#FILES AND PATH
HEADERS_SRC				=	philo.h
HEADERS_DIR				=	-I includes/
HEADER					=	$(addprefix $(HEADERS_DIR), $(HEADERS_SRC))

_PHILO_FILES			=	main.c init.c routine.c time.c free.c error.c
PHILO_SRC_DIR			=	./sources/
PHILO_SRCS				=	$(addprefix $(PHILO_SRC_DIR), $(_PHILO_FILES))
PHILO_OBJS				=	$(PHILO_SRCS:.c=.o)

_UTILS_PHILO			=	ft_atoi.c
UTILS_DIR				=	./utils/
UTILS_PHILO_SRCS		=	$(addprefix $(UTILS_DIR), $(_UTILS_PHILO))
UTILS_OBJS				=	$(UTILS_PHILO_SRCS:.c=.o)


ALL_SRCS				=	$(_PHILO_FILES) $(_UTILS_PHILO)
BUILD_DIR				=	build

ALL_OBJS				= $(patsubst %.c, $(BUILD_DIR)/%.o, $(ALL_SRCS))

# $(BUILD_DIR)/%.o: 	$(PHILO_SRC_DIR)/%.c $(UTILS_DIR)/%.c
# 	@mkdir -p $(@D)
# 	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

# all :
# 	@echo $(ALL_OBJS)

$(NAME) : $(PHILO_OBJS) $(UTILS_OBJS)
	$(CC) $(FLAGS) $(PHILO_OBJS) $(UTILS_OBJS) -l $(PTHREAD_LIB) -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	/bin/$(RM) $(PHILO_OBJS)
	/bin/$(RM) $(UTILS_OBJS)

fclean : clean
	/bin/$(RM) -f $(NAME)

re :
	make fclean
	make

.PHONY: all clean fclean re