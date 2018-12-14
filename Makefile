OS := ($(shell uname))
SRCDIR := src
TESTDIR := test

OBJDIR := obj
DEPDIR := dep
BINDIR := bin

SOBJDIR := obj/src
SDEPDIR := dep/src
TOBJDIR := obj/test
TDEPDIR := dep/test

TESTEXEC := test.out
MAINEXEC := main.out

SRCS := $(shell find $(SRCDIR) -name "*.cpp")
SOBJS := $(SRCS:$(SRCDIR)/%.cpp=$(SOBJDIR)/%.o)
SDEPS := $(SRCS:$(SRCDIR)/%.cpp=$(SDEPDIR)/%.d)
STREE := $(patsubst %/,%,$(dir $(SOBJS)))

TESTS := $(shell find $(TESTDIR) -name "*.cpp")
TOBJS := $(TESTS:$(TESTDIR)/%.cpp=$(TOBJDIR)/%.o)
TDEPS := $(TESTS:$(TESTDIR)/%.cpp=$(TDEPDIR)/%.d)
TTREE := $(patsubst %/,%,$(dir $(TOBJS)))

SCPPFLAGS  = -MMD -MP -MF $(@:$(SOBJDIR)/%.o=$(SDEPDIR)/%.d)
TCPPFLAGS  = -MMD -MP -MF $(@:$(TOBJDIR)/%.o=$(TDEPDIR)/%.d)

ifeq ($(OS),Darwin)
	BCXXFLAGS = -I$(SRCDIR) -I$(TESTDIR) -O3 -std=c++1z -stdlib=libstdc++
	BLINKERFLAGS = -stdlib=libstdc++
	CXXFLAGS = -D __apple__
else
	BCXXFLAGS = -I$(SRCDIR) -I$(TESTDIR) -O3 -std=c++1z -fPIC
endif

all: CXXFLAGS += $(BCXXFLAGS) -D __main__
test: CXXFLAGS += $(BCXXFLAGS) -D __test__
graphics: CXXFLAGS += $(BCXXFLAGS) -D __main__ -D __graphics__ -I/usr/X11/include -I$(PASSPARTOUT_PATH)/include
graphics: LINKERFLAGS = -L/usr/X11/lib -L$(PASSPARTOUT_PATH)/lib -lXt -lX11 -lXext -lGG -lGL

.PHONY: all test clean graphics

all: $(BINDIR)/$(MAINEXEC)

graphics: $(BINDIR)/$(MAINEXEC)

test: $(BINDIR)/$(TESTEXEC)
	$(BINDIR)/$(TESTEXEC)

clean:
	$(RM) -r $(OBJDIR) $(DEPDIR) $(BINDIR)

.SECONDEXPANSION:
$(SOBJDIR)/%.o: $(SRCDIR)/%.cpp | $$(@D)
	$(CXX) $(SCPPFLAGS) $(CXXFLAGS) -o $@ -c $<

$(TOBJDIR)/%.o: $(TESTDIR)/%.cpp | $$(@D)
	$(CXX) $(TCPPFLAGS) $(CXXFLAGS) -o $@ -c $<

$(BINDIR):
	mkdir -p $(BINDIR)

$(STREE): %:
	mkdir -p $@
	mkdir -p $(@:$(SOBJDIR)%=$(SDEPDIR)%)

$(TTREE): %:
	mkdir -p $@
	mkdir -p $(@:$(TOBJDIR)%=$(TDEPDIR)%)

$(BINDIR)/$(TESTEXEC): $(SOBJS) $(TOBJS) $(BINDIR)
	$(CXX) -o $(BINDIR)/$(TESTEXEC) $(SOBJS) $(TOBJS)

$(BINDIR)/$(MAINEXEC): $(SOBJS) $(BINDIR)
	$(CXX) $(BLINKERFLAGS) $(LINKERFLAGS) -o $(BINDIR)/$(MAINEXEC) $(SOBJS)
ifeq "$(MAKECMDGOALS)" ""
-include $(SDEPS)
-include $(TDEPS)
endif
