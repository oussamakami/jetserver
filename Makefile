CXX			=	c++
CXXFLAGS	=	-std=c++98 -g

CLASSES		=	classes/SysData/SysData.cpp classes/Locations/Locations.cpp\
				classes/Servers/Servers.cpp

TOOLS		=	tools/notify.cpp tools/terminate.cpp tools/trim.cpp\
				tools/split.cpp

PARSING		=	parsing/parsingChecks.cpp parsing/parseSystem.cpp\
				parsing/parseServers.cpp parsing/parseRoutes.cpp\
				parsing/loadConfig.cpp

NETWORK		=	network/setSockets.cpp network/handleConnections.cpp

FILES		=	$(CLASSES) $(TOOLS) $(PARSING) $(NETWORK) main.cpp
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