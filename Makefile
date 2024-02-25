CXX			=	c++
CXXFLAGS	=	-std=c++98 -g

CLASSES		=	classes/SysData/SysData.cpp classes/Locations/Locations.cpp

PARSING		=	

FILES		=	$(CLASSES) $(PARSING) main.cpp
OBJ			=	$(FILES:.cpp=.o)
NAME		=	webserver

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:		clean
	rm -rf $(NAME)

re:			fclean all