CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -MMD

NAME = ft_containers_test
SOURCES = ft_vector_test.cpp
HEADERSROOT = ../includes
HEADERS =	$(HEADERSROOT)/ft_algorithm.hpp \
			$(HEADERSROOT)/ft_iterator.hpp \
			$(HEADERSROOT)/ft_vector.hpp \
			$(HEADERSROOT)/until.hpp \
			tester.hpp
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = $(OBJECTS:.o=.d)

$(NAME): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(DEPS)
	rm -rf out_ft out_std err_ft err_std

fclean: clean
	rm -f $(NAME)

all: $(NAME)

re: fclean all

#test:
#	$(CXX) $(CFLAGS) $(SRCS) -DTEST=0 -o $(NAME)
#	@./$(NAME) > out_ft 2>err_ft
#	$(CXX) $(CFLAGS) $(SRCS) -DTEST=1 -o $(NAME)
#	@./$(NAME) > out_std 2>err_std
# # ret(1) cause make error.  ||: force ret(0)
#	diff out_ft out_std ||:
#	@echo "---ft_err---"
#	@cat err_ft
#	@echo "---std_err---"
#	@cat err_std
#
#test0:
#	$(CXX) $(CFLAGS) $(SRCS) -DTEST=0 -o $(NAME)
#	@./$(NAME) > out_ft 2>err_ft
#	@cat out_ft
#	@cat err_ft
#
#test1:
#	$(CXX) $(CFLAGS) $(SRCS) -DTEST=1 -o $(NAME)
#	@./$(NAME) > out_std 2>err_std
#	@cat out_std
#	@cat err_std