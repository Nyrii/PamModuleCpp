##
## Makefile for Makefile in /Users/wilmot_g/Epitech/Crypto/Pamela
##
## Made by Nyrandone Noboud-Inpeng
## Login   <noboud_n@epitech.net>
##
## Started on  Mon Oct 12 17:58:00 2016 Nyrandone Noboud-Inpeng
## Last update Sat Oct  8 16:17:48 2016 Nyrandone Noboud-Inpeng
##

SRC	+= Crypt.cpp
SRC	+= Logger.cpp
SRC	+= Pamela.cpp
SRC	+= Session.cpp

MAIN	= Main.cpp

OBJ	= $(addprefix $(OBJDIR), $(SRC:.cpp=.o))
OBJMAIN	= $(addprefix $(OBJDIR), $(MAIN:.cpp=.o))

RM	= rm -f

CXX	= g++ -std=c++11 -g

NAME	= pam_ela.so
TEST	= pamtest

OBJDIR	= obj/
SRCDIR	= src/
INCDIR	= -I inc/

MAKEOBJ	= obj

LDFLAGS		+= -lpam -ldl -lcrypto
CXXFLAGS	+= -W -Wall -Wextra -Werror -fpic -rdynamic -ansi -D_POSIX_SOURCE

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
