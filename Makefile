CXX			=	c++
CXXFLAGS	=	-std=c++98 -g -Wall -Wextra -Werror --static

CLASSES		=	classes/SysData/SysData.cpp classes/Locations/Locations.cpp\
				classes/Servers/Servers.cpp classes/RequestData/RequestData.cpp\
				classes/ResponseData/ResponseData.cpp classes/CommandLine/CommandLine.cpp

TOOLS		=	tools/notify.cpp tools/terminate.cpp tools/trim.cpp\
				tools/split.cpp tools/terminateOnSignal.cpp\
				tools/pathCombs.cpp tools/strIntConv.cpp\
				tools/autoIndexTools.cpp tools/isCGI.cpp\
				tools/captureLog.cpp

PARSING		=	parsing/parsingChecks.cpp parsing/parseSystem.cpp\
				parsing/parseServers.cpp parsing/parseRoutes.cpp\
				parsing/loadConfig.cpp

REQUESTS	=	network/RequestParsing/extractData.cpp network/RequestParsing/getServer.cpp\
				network/RequestParsing/RequestParsing.cpp

RESPONSE	=	network/generateResponse/generateResponse.cpp network/generateResponse/handleGet.cpp\
				network/generateResponse/CGI_Get.cpp network/generateResponse/handlePost.cpp\
				network/generateResponse/CGI_Post.cpp network/generateResponse/handleDelete.cpp\
				network/generateResponse/CGI_Delete.cpp

NETWORK		=	network/setSockets.cpp network/processReq.cpp\
				network/startServers.cpp $(REQUESTS) $(RESPONSE)

FILES		=	$(CLASSES) $(TOOLS) $(PARSING) $(NETWORK) main.cpp
OBJ			=	$(FILES:.cpp=.o)
NAME		=	webserver

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

docker_img:
	docker build -t webserver:latest .

docker_kill:
	docker kill webserver 2>/dev/null || true
	docker rm webserver 2>/dev/null || true

docker_run:		all docker_kill
	docker run --rm --name webserver -v $(shell pwd):/data --network host -e "IS_CONTAINER=true" -d webserver:latest

docker_clean: fclean docker_kill
	docker image rm -f webserver:latest

clean:
	rm -rf $(OBJ)

fclean:		clean
	rm -rf $(NAME)

re:			fclean all