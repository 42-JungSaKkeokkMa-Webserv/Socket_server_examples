NAME = webserv

CXX				= clang++
CXXFLAGS		= -Wall -Werror -Wextra -std=c++98
# CXXFLAGS		= -std=c++98 -fsanitize=address

SRCS_PATH		= ./srcs
INCS_PATH		= ./includes
OBJS_PATH		= ./objs

# SRCS_PATH 내의 모든 .cpp 파일을 OBJ_PATH 내에 .o 파일로 컴파일
# wildcard를 썼으므로 실제 프로젝트에서는 이를 SRCS에 해당하는 파일들을 명시해준 뒤
# SRCS_PATH 내에 SRCS에 해당하는 파일들을 OBJS에 해당하는 파일들로 컴파일하도록 수정해야 함
SRCS			= $(wildcard $(SRCS_PATH)/*.cpp)
OBJS			= $(patsubst $(SRCS_PATH)/%.cpp, $(OBJS_PATH)/%.o, $(SRCS))

# OBJS_PATH 내에 .o 파일이 없으면 OBJS_PATH 내에 .o 파일 생성
$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.cpp
	@mkdir -p $(OBJS_PATH)
	$(CXX) $(CXXFLAGS) -I $(INCS_PATH) -c $< -o $@

# OBJS_PATH 내에 .o 파일이 있으면 OBJS_PATH 내에 .o 파일을s NAME 파일로 링크
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -I $(INCS_PATH) -o $(NAME) $(OBJS)



TESTCLIENT = client

all: $(NAME)

clean:
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(TESTCLIENT)

re: fclean all

client:
	gcc -o $(TESTCLIENT) clientExample.cpp
	./$(TESTCLIENT)

.PHONY: all clean fclean re