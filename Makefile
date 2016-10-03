##
## Makefile for Makefile in /Users/wilmot_g/Epitech/Crypto/Pamela
##
## Made by Nyrandone Noboud-Inpeng
## Login   <noboud_n@epitech.net>
##
## Started on  Mon Oct 12 17:58:00 2016 Nyrandone Noboud-Inpeng
## Last update Mon Oct 21 23:48:44 2016 guillaume wilmot
##

SRC	= Pamela.cpp

OBJ	= $(addprefix $(OBJDIR), $(SRC:.cpp=.o))

RM	= rm -f

CXX	= g++ -std=c++11

NAME	= pamtest

OBJDIR	= obj/
SRCDIR	= src/
INCDIR	= -I inc/

MAKEOBJ	= obj

LDFLAGS 	+= -lpam
CXXFLAGS	+= -W -Wall -Wextra -Werror

all:
	@make --no-print-directory $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p $(MAKEOBJ)
	$(CXX) $(CXXFLAGS) $(INCDIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
