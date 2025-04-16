# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lglfw -lGL -lm
TARGET = main
SRCDIR = src
INCDIR = include
OBJDIR = obj
TESTDIR = tests
TESTOBJDIR = $(OBJDIR)/tests

# Source, object, and test files
SOURCES = $(wildcard $(SRCDIR)/*.c $(SRCDIR)/glad/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
TESTSOURCES = $(wildcard $(TESTDIR)/*.c)
TESTTARGETS = $(patsubst $(TESTDIR)/%.c,%,$(TESTSOURCES))

# Default target
.PHONY: all
all: $(TARGET)

# Link object files to create main executable
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Pattern rule for main object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern rule for test object files
$(TESTOBJDIR)/%.o: $(TESTDIR)/%.c | $(TESTOBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if they don't exist
$(OBJDIR):
	mkdir -p $(OBJDIR) $(OBJDIR)/glad

$(TESTOBJDIR):
	mkdir -p $(TESTOBJDIR)

# Test targets (e.g., make test_math)
.PHONY: $(TESTTARGETS)
$(TESTTARGETS): %: $(TESTOBJDIR)/%.o $(OBJDIR)/math_utils.o
	$(CC) -o $@ $^ -lm
	./$@

# Clean up
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET) $(TESTTARGETS)

# Automatic dependency tracking for main sources
-include $(OBJECTS:.o=.d)

# Generate dependency files for main sources
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -M -MT $@ $< > $(OBJDIR)/$*.d
	$(CC) $(CFLAGS) -c $< -o $@

# Automatic dependency tracking for test sources
-include $(TESTSOURCES:.c=.d)

# Generate dependency files for test sources
$(TESTOBJDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) -M -MT $@ $< > $(TESTOBJDIR)/$*.d
	$(CC) $(CFLAGS) -c $< -o $@