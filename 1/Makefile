CC = c++

NAME = ft_containers

CFLAGS = -Wall -Werror -Wextra -std=c++98

OBJDIR = ./obj
OBJECTS = $(OBJDIR)/*.o
SRC =	tests.cpp \

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

$(OBJECTS): $(SRC)
	$(CC) -c $(CFLAGS) $(SRC)
	@rm -rf $(OBJDIR); mkdir $(OBJDIR)
	@mv *.o $(OBJDIR)

clean:
	@rm -f $(OBJECTS)
	@rm -rf $(OBJDIR)
	@rm -rf logs
	@rm -rf std_containers
	@rm -rf ft_containers

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)
