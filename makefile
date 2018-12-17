#
# TODO: Move `libmongoclient.a` to /usr/local/lib so this can work on production servers
#

CC := g++ -std=c++14 # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := bin/angru

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall
LIBPQ := -lpqxx -lpq
LIB := -pthread -lboost_log -lboost_log_setup -lboost_regex
LIB += -lboost_thread -lboost_filesystem -lboost_system -lboost_date_time
LIB += -lpistache -lssl -lcrypto
INC := -Iinclude
#BADL := -BOOST_ALL_NO_LIB
BADL :=  -DBOOST_LOG_DYN_LINK
INCPQ := -I /usr/local/include/pqxx/
LIBPQPATH := -L /usr/local/lib/

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $(INCPQ) $(LIBPQPATH) $^ $(BADL) $(LIBPQ) -o $(TARGET) $(LIB)"; $(CC) $(INCPQ) $(LIBPQPATH) $^ $(BADL) $(LIBPQ) -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) $(BADL) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) $(BADL) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) $(OBJECTS) $(TARGET)"; $(RM) $(OBJECTS) $(TARGET)

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
