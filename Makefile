##
## Makefile for  in /Users/Saursinet/danone
##
## Made by Florian Saurs
## Login   <Saursinet@epitech.net>
##
## Started on  Mon Sep 19 18:38:47 2016 Florian Saurs
## Last update Mon Sep 19 18:38:49 2016 Florian Saurs
##

CC = g++

CXXFLAGS = -std=c++11

LDFLAGS = -lpam

rm = rm -f

SRCS = pamela.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = pamela

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

all: $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all
