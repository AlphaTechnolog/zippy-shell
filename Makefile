# Compiler
CC      := clang
LIBS	:= -lcjson
CFLAGS  := -Wall -Werror -pedantic -I/usr/include/cjson

# Directories
SRCDIR  := src
OBJDIR  := obj
INCDIR  := include
BINDIR  := bin

# Files
SRC     := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c)
OBJ     := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
INC     := -I $(INCDIR)

# Main target
TARGET  := $(BINDIR)/zippy

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Create directories if they don't exist
$(OBJDIR) $(INCDIR) $(BINDIR):
	@mkdir -pv $@

# Object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(INCDIR)
	@mkdir -pv $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Target
$(TARGET): $(BINDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBS)

# Clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Run directly from make
run: $(TARGET)
	@echo "------------------------"
	./$(TARGET) $(filter-out $@,$(MAKECMDGOALS))

%:
	@:
