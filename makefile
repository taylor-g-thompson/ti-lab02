###############################################################################
# purpose: makefile for Lab 2
#
# 'make'        build executable file
# 'make clean'  removes all intermediate (lex.yy.c and *.o) and executable files
#
# This makefile purposely avoids macros to make the rules more clear.
# For more information about makefiles:
#      http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#      http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#      http://www.gnu.org/software/make/manual/make.html
#
###############################################################################
# variables used in the following rules
LEX      = flex
CXX      = g++
CC       = gcc
RM       = rm
# generate debug information for gdb
CXXFLAGS = -g
CCFLAGS  = -g
# don't ever remove these files
.PRECIOUS = rules.l driver.cpp lexer.h parser.h

parse: lex.yy.o driver.o parser.o
	$(CXX) $(CXXFLAGS) -o parse lex.yy.o driver.o parser.o

#     -o flag specifies the output file
#
#     The above rule could be written with macros as
#        $(CXX) $(CXXFLAGS) -o $@ $^

driver.o: driver.cpp parser.h lexer.h
	$(CXX) $(CXXFLAGS) -o driver.o -c driver.cpp
#      -c flag specifies stop after compiling, do not link

parser.o: parser.cpp parser.h lexer.h 
	$(CXX) $(CXXFLAGS) -o parser.o -c parser.cpp

lex.yy.o: lex.yy.c lexer.h
	$(CC) $(CCFLAGS) -o lex.yy.o -c lex.yy.c

lex.yy.c: rules.l lexer.h
	$(LEX) -o lex.yy.c rules.l

clean: 
	$(RM) *.o lex.yy.c parse

