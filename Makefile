# nocs Version
MAJOR    := 1
MINOR    := 0
REVISION := 0

# Setting bash colors
RED    := $(shell tput -Txterm setaf 1)
YELLOW := $(shell tput -Txterm setaf 3)
GREEN  := $(shell tput -Txterm setaf 2)
PURPLE := $(shell tput -Txterm setaf 5)
WHITE  := $(shell tput -Txterm setaf 9)
LBLUE  := $(shell tput -Txterm setaf 6)
RESET  := $(shell tput -Txterm sgr0   )

#################################################################
#                         COMPILE OPTIONS                       #
#################################################################

OS      := ($(shell uname))
DEBUG   ?= 1

ifeq ($(OS),Darwin)
	BCXXFLAGS = -I$(SRCDIR) -I$(TESTDIR) -std=c++1z -stdlib=libstdc++
	BLINKERFLAGS = -stdlib=libstdc++
	CXXFLAGS = -D __apple__
else
	BCXXFLAGS = -I$(SRCDIR) -I$(TESTDIR) -march=native -std=c++1z -fPIC
endif

AR      := ar
ARFLAGS := rcs
SLIB    := libnocs.so
ALIB    := libnocs.a


#################################################################
#                         PARSE OPTIONS                         #
#################################################################

define config
	$(if $(filter $(1), $(2)), $(3), $(4) )
endef

BCXXFLAGS += $(strip $(call config, $(DEBUG),   1, -O0 -g -DDEBUG, -Ofast -DNDEBUG))

#################################################################
#                         SETTING DIRECTORIES                   #
#################################################################

SRCDIR  := ./src
TESTDIR := ./test

OBJDIR := ./obj
DEPDIR := ./dep
BINDIR := ./bin

SOBJDIR := ./obj/src
SDEPDIR := ./dep/src
TOBJDIR := ./obj/test
TDEPDIR := ./dep/test

TESTEXEC := Test.out
MAINEXEC := main.out


SRCS  := $(shell find $(SRCDIR) -name "*.cpp")
SOBJS := $(SRCS:$(SRCDIR)/%.cpp=$(SOBJDIR)/%.o)
SDEPS := $(SRCS:$(SRCDIR)/%.cpp=$(SDEPDIR)/%.d)
STREE := $(sort $(patsubst %/,%,$(dir $(SOBJS))))

TESTS := $(shell find $(TESTDIR) -name "*.cpp")
TOBJS := $(TESTS:$(TESTDIR)/%.cpp=$(TOBJDIR)/%.o)
TDEPS := $(TESTS:$(TESTDIR)/%.cpp=$(TDEPDIR)/%.d)
TTREE := $(sort $(patsubst %/,%,$(dir $(TOBJS))))

SCPPFLAGS  = -MMD -MP -MF $(@:$(SOBJDIR)/%.o=$(SDEPDIR)/%.d)
TCPPFLAGS  = -MMD -MP -MF $(@:$(TOBJDIR)/%.o=$(TDEPDIR)/%.d)

#################################################################
#                         MAIN RULES                            #
#################################################################

all: CXXFLAGS += $(BCXXFLAGS) -D __main__
test: CXXFLAGS += $(BCXXFLAGS) -D __test__
graphics: CXXFLAGS += $(BCXXFLAGS) -D __main__ -D __graphics__ -I/usr/X11/include -I/usr/local/include
graphics: LINKERFLAGS += -L/usr/local/lib64 -lGG -lGL -lGLU -lXt -lX11 -lXext

.PHONY: all test clean graphics

all: $(ALIB) $(SLIB) $(BINDIR)/$(MAINEXEC)    ##@exec Compile the main exec and build libraries.

sharedlib: $(SLIB)                            ##@library Create shared nocs library.

staticlib: $(ALIB)                            ##@library Create static nocs library.

graphics: $(BINDIR)/$(MAINEXEC)               ##@exec Create graphic nocs exec.

main: $(BINDIR)/$(MAINEXEC)                   ##@run Run main nocs exec.
	$(BINDIR)/$(MAINEXEC)

test: $(BINDIR)/$(TESTEXEC)                   ##@run Run test nocs exec.
	$(BINDIR)/$(TESTEXEC)


#################################################################
#                         NOCS RULES                            #
#################################################################

.SECONDEXPANSION:
$(SOBJDIR)/%.o: $(SRCDIR)/%.cpp | $$(@D)
	@printf "%-80s " "generating obj for $<"
	@$(CXX) $(SCPPFLAGS) $(CXXFLAGS) -o $@ -c $<
	@printf "[done]\n"

$(TOBJDIR)/%.o: $(TESTDIR)/%.cpp | $$(@D)
	@printf "%-80s " "generating obj for $<"
	@$(CXX) $(TCPPFLAGS) $(CXXFLAGS) -o $@ -c $<
	@printf "[done]\n"

$(ALIB): $(SOBJS)
	@printf "%-80s " "generating $(ALIB) ..."
	@$(AR) $(ARFLAGS) $@ $^
	@printf "[done]\n"

$(SLIB): $(SOBJS)
	@printf "%-80s " "generating $(SLIB) ..."
	@$(CXX) $(SCPPFLAGS) $(CXXFLAGS) -shared $^ -o $@ $(LINKERFLAGS)
	@printf "[done]\n"

$(BINDIR)/$(TESTEXEC): $(SOBJS) $(TOBJS) $(BINDIR)
	@printf "%-80s " "Compiling $(TESTEXEC) example ..."
	@$(CXX) -o $(BINDIR)/$(TESTEXEC) $(SOBJS) $(TOBJS)
	@printf "[done]\n"

$(BINDIR)/$(MAINEXEC): $(SOBJS) $(BINDIR)
	@printf "%-80s " "Compiling $(MAINEXEC) exec ..."
	@$(CXX) -o $(BINDIR)/$(MAINEXEC) $(SOBJS) $(BLINKERFLAGS) $(LINKERFLAGS)
	@printf "[done]\n"
ifeq "$(MAKECMDGOALS)" ""
-include $(SDEPS)
-include $(TDEPS)
endif

#################################################################
#                         UTILS RULES                           #
#################################################################

# Add the following 'help' target to your Makefile
# And add help text after each target name starting with '\#\#'
# A category can be added with @category
HELP_FUN = \
	%help; \
	while(<>) { push @{$$help{$$2 // 'options'}}, [$$1, $$3] if /^([a-zA-Z\-]+)\s*:.*\#\#(?:@([a-zA-Z\-]+))?\s(.*)$$/ }; \
	print "\t\t\t$(LBLUE)Nocs Makefile$(RESET)\n"; \
	print "usage: ${PURPLE}make${RESET} ${GREEN}<target>${RESET}\n\n"; \
	for (sort keys %help) { \
	print "${WHITE}$$_:${RESET}\n"; \
	for (@{$$help{$$_}}) { \
	$$sep = " " x (32 - length $$_->[0]); \
	print "  ${PURPLE}$$_->[0]${RESET}$$sep${GREEN}$$_->[1]${RESET}\n"; \
	}; \
	print "\n"; }
.PHONY: clean

clean:                               ##@utils Clean all files.
	@printf "%-80s " "Cleaning all files..."
	@$(RM) -r $(OBJDIR) $(DEPDIR) $(BINDIR) $(ALIB) $(SLIB)
	@printf "[done]\n"

$(BINDIR):													 ##@utils Create output directory.
	@printf "%-80s " "Creating output (exec) directory ..."
	@mkdir -p $(BINDIR)
	@printf "[done]\n"

$(STREE): %:
	@printf "%-80s " "Creating obj directory ..."
	@mkdir -p $@
	@printf "[done]\n"
	@printf "%-80s " "Creating dependencies directory ..."
	@mkdir -p $(@:$(SOBJDIR)%=$(SDEPDIR)%)
	@printf "[done]\n"

$(TTREE): %:
	@printf "%-80s " "Creating obj directory ..."
	@mkdir -p $@
	@printf "[done]\n"
	@printf "%-80s " "Creating dependencies directory ..."
	@mkdir -p $(@:$(TOBJDIR)%=$(TDEPDIR)%)
	@printf "[done]\n"

help:                                ##@utils Show this help message.
	@perl -e '$(HELP_FUN)' $(MAKEFILE_LIST)

