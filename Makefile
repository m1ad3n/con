#################
## DIRECTORIES ##
#################

DEB_DIR     =   ./build
REL_DIR     =   ./release
LIB_DIR     =   ./lib

SOURCE_DIR  =   ./src
OBJ_DIR     =   ./build
INC_DIR     =   ./build


####################
## COMPILER FLAGS ##
####################

CC          =   gcc
CFLAGS      =   -Wall -Wextra -ggdb -w -g -I$(INC_DIR) -MMD
LDFLAGS     =
LIBCFLAGS   =   -pedantic -fPIC -shared


###################
## SHELL COMMAND ##
###################

MD          =   mkdir -p
RM          =   rm -rvf


#############
## TARGETS ##
#############

PROJECT     =   $(notdir $(shell pwd))
DEB_TARGET  =   $(PROJECT)
VERSION     =
REL_TARGET  =   $(REL_DIR)/$(PROJECT)$(VERSION)
LIB_TARGET  =   $(LIB_DIR)/lib$(PROJECT).so


###############################
## SOURCES, OBJECTS, HEADERS ##
###############################

SRCS        =   $(shell find . -name "*.c")
OBJS        =   $(subst $(SOURCE_DIR),$(OBJ_DIR), $(subst .c,.o,$(SRCS)))
HEADERS     =   $(shell find . -name "*.h")


##########################
## OBJECT BUILD SECTION ##
##########################

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


#################################
## DEBUG(NORMAL BUILD) SECTION ##
#################################

$(DEB_TARGET): $(OBJS) | $(DEB_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)


#####################
## RELEASE SECTION ##
#####################

release: $(REL_TARGET)

$(REL_TARGET): $(OBJS) | $(REL_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)


#####################
## LIBRARY SECTION ##
#####################

library: $(LIB_TARGET)

$(LIB_TARGET): $(OBJS) | $(LIB_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)


#####################
## INSTALL SECTION ##
#####################

install:
ifneq (,$(wildcard $(LIB_TARGET)))
	sudo install $(LIB_TARGET) /usr/lib
endif

ifneq (,$(wildcard $(REL_TARGET)))
	sudo install $(REL_TARGET) /usr/bin
endif

ifneq (,$(wildcard $(HEADERS)))
	sudo install $(HEADERS) /usr/include
endif


run:
	$(DEB_TARGET)

#################
## CREATE DIRS ##
#################

$(DEB_DIR):
	@$(MD) $(DEB_DIR)

$(REL_DIR):
	@$(MD) $(REL_DIR)

$(LIB_DIR):
	@$(MD) $(LIB_DIR)

############################
## CLEAN AND INCLUDE FUNC ##
############################

.PHONY: clean
clean:
	@$(RM) $(TARGET_DIR)/**

-include $(shell find . -name "*.d")
