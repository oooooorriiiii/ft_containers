NAME := ft_containers_test
SRCS := $(shell find *.cpp)
OBJDIR := ./obj
OBJS := $(SRCS:%.cpp=$(OBJDIR)%.o)

CXX = clang++ -g -O0
#CFLAGS = -Wall -Werror -Wextra

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p obj

$(OBJDIR)%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJDIR)
	rm -rf out_ft out_std err_ft err_std

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	$(CXX) $(CFLAGS) $(SRCS) -DTEST=0 -o $(NAME)
	@./$(NAME) > out_ft 2>err_ft
	$(CXX) $(CFLAGS) $(SRCS) -DTEST=1 -o $(NAME)
	@./$(NAME) > out_std 2>err_std
 # ret(1) cause make error.  ||: force ret(0)
	diff out_ft out_std ||:
	@echo "---ft_err---"
	@cat err_ft
	@echo "---std_err---"
	@cat err_std

test0:
	$(CXX) $(CFLAGS) $(SRCS) -DTEST=0 -o $(NAME)
	@./$(NAME) > out_ft 2>err_ft
	@cat out_ft
	@cat err_ft

test1:
	$(CXX) $(CFLAGS) $(SRCS) -DTEST=1 -o $(NAME)
	@./$(NAME) > out_std 2>err_std
	@cat out_std
	@cat err_std