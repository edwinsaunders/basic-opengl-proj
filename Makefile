# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lglfw -lGL
TARGET = main
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Source and object files
SOURCES = $(wildcard $(SRCDIR)/*.c $(SRCDIR)/glad/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Default target
.PHONY: all
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Pattern rule for object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Automatic dependency tracking
-include $(OBJECTS:.o=.d)

# Generate dependency files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -M -MT $@ $< > $(OBJDIR)/$*.d
	$(CC) $(CFLAGS) -c $< -o $@
