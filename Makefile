##
## Makefile for Makefile in /Users/wilmot_g/Epitech/Crypto/Pamela
##
## Made by Nyrandone Noboud-Inpeng
## Login   <noboud_n@epitech.net>
##
## Started on  Mon Oct 12 17:58:00 2016 Nyrandone Noboud-Inpeng
## Last update Mon Oct 21 23:48:44 2016 guillaume wilmot
##

SRC	= Pamela.cpp	\
	  Session.cpp

MAIN	= Main.cpp

OBJ	= $(addprefix $(OBJDIR), $(SRC:.cpp=.o))
OBJMAIN	= $(addprefix $(OBJDIR), $(MAIN:.cpp=.o))

RM	= rm -f

CXX	= g++ -std=c++11

NAME	= pamela.so
TEST	= pamtest

OBJDIR	= obj/
SRCDIR	= src/
INCDIR	= -I inc/

MAKEOBJ	= obj

LDFLAGS 	+= -lpam
CXXFLAGS	+= -W -Wall -Wextra -Werror -fpic

all:
	@make --no-print-directory $(NAME)
	@make --no-print-directory $(TEST)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p $(MAKEOBJ)
	$(CXX) $(CXXFLAGS) $(INCDIR) -o $@ -c $<

$(TEST): $(OBJ) $(OBJMAIN)
	$(CXX) -o $(TEST) $(OBJ) $(OBJMAIN) $(LDFLAGS)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) -shared

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJMAIN)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST)
	$(RM) -R $(OBJDIR)

re: fclean all
