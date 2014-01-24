#
# Generic makefile
#

SHELL = sh
UNAME := $(shell uname)

# define the C compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -Wall -g

# define any directories containing header files other than /usr/include
#
INCLUDES = 

# define library paths in addition to /usr/lib
LFLAGS =

# define any libraries to link into executable:
LIBS =

# Other flags
OTHER = 

# define the C source files

# Linux
LINUXSRCSRAW = $(foreach d,.,$(wildcard $(addprefix $(d)/linux/*,.cpp)))
# File that contains main
LINUX_MAIN = ./linux/main.cpp
LINUX_SRCS = $(filter-out $(LINUX_MAIN),$(LINUX_SRCSRAW))

# Shared
SHARED_SRCSRAW =  $(foreach d,.,$(wildcard $(addprefix $(d)/shared/*,.cpp)))
SHARED_FILTER =
SHARED_SRCS =  $(filter-out $(SHARED_FILTER),$(SHARED_SRCSRAW))

# define the C object files 
LINUX_OBJS = $(LINUX_SRCS:.cpp=.o)
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

# define the executable file
LINUX_BIN = linux_agent

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:    $(LINUX_BIN)
	@echo  Build Successful

# Linux agent
$(LINUX_BIN): $(LINUX_MAIN) $(LINUX_OBJS) $(SHARED_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(LINUX_BIN) $(LINUX_MAIN) $(LINUX_OBJS) $(SHARED_OBJS) $(LFLAGS) $(LIBS) $(OTHER)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(LINUX_BIN) $(LINUX_OBJS) $(SHARED_OBJS) *~

depend: $(SRCS) $(S_SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
