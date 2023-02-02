NAME = webserv

CXX				= clang++
CXXFLAGS		= -Wall -Werror -Wextra -std=c++98

SRCS_PATH		= ./src
OBJS_PATH		= ./obj

SRCS			= $(wildcard $(SRCS_PATH)/*.cpp)
OBJS			= $(patsubst $(SRCS_PATH)/%.cpp, $(OBJS_PATH)/%.o, $(SRCS))

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.cpp
	@mkdir -p $(OBJS_PATH)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(TESTCLIENT)

re: fclean all

.PHONY: all clean fclean re