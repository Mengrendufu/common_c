###############################################################################
################################## MAKEFILE ###################################
###############################################################################

# recursive match function (pure make) ----------------------------------------
rwildcard = $(foreach d,$(wildcard $1*), $(call rwildcard,$d/,$2)) \
            $(filter $(subst *,%,$2), $(wildcard $1$2))
# recursive match function (pure make) ----------------------------------------

# compiler options ------------------------------------------------------------
CC := gcc
CFLAGS := -Wall -Wextra -g
# compiler options ------------------------------------------------------------

# library paths, link flags
# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like: -L./lib
LFLAGS :=

# source dir, header dir, lib dir, output dir ---------------------------------
SRC_DIRS     := src common/src
INCLUDE_DIRS := include common/include
# libraries like: mylib pthread
LIB	         := lib
OUTPUT       := output
# source dir, header dir, lib dir, output dir ---------------------------------

# shell specific settings -----------------------------------------------------
ifeq (,$(findstring Git,$(SHELL))) # powershell
MD	    := -powershell mkdir -Force
RM      := -powershell Remove-Item -Recurse -Force
else # gitbash
MD	    := mkdir -p
RM      := rm -rf
endif
# shell specific settings -----------------------------------------------------

# for compiler ----------------------------------------------------------------
SOURCES  := $(foreach d, $(SRC_DIRS), $(call rwildcard, $(d)/, *.c))
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
LIBS     := $(addprefix -L, $(LIB))
OBJECTS	 := $(patsubst %.c, $(OUTPUT)/%.o, $(SOURCES))
# for compiler ----------------------------------------------------------------

# executable file -------------------------------------------------------------
MAIN := main.exe
OUTPUTMAIN := $(OUTPUT)/$(MAIN)
# executable file -------------------------------------------------------------

# dependences, after OBJECTS --------------------------------------------------
DEPS := $(OBJECTS:.o=.d)
-include $(DEPS)
# dependences, after OBJECTS --------------------------------------------------

.PHONY: all clean show run

# make it first target #1 -----------------------------------------------------
all: $(OUTPUTMAIN)
	@echo "Build complete: $(OUTPUTMAIN)"
# make it first target #1 -----------------------------------------------------

# make build ------------------------------------------------------------------
# order-only prerequisite #3_1 ------------------------------------------------
$(OUTPUT):
	$(MD) $(OUTPUT)
# order-only prerequisite #3_1 ------------------------------------------------

# .o compiling #3_2 -----------------------------------------------------------
# $(OUTPUT): order-only prerequisite to ensure output dir exists
$(OUTPUT)/%.o: %.c | $(OUTPUT)
	@echo "Compiling $< -> $@"
	@$(MD) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MF $(OUTPUT)/$*.d -MT $@ -c $< -o $@
# .o compiling #3_2 -----------------------------------------------------------

# linking #2 ------------------------------------------------------------------
$(OUTPUTMAIN): $(OBJECTS)
	@echo "Linking $@"
	$(CC) $(OBJECTS) -o $@ $(LFLAGS) $(LIBS)
# linking #2 ------------------------------------------------------------------

run: all
	./$(OUTPUTMAIN)

clean:
	@echo "Cleaning output directory: $(OUTPUT)"
	$(RM) $(OUTPUT)

# DEBUG -----------------------------------------------------------------------
show:
	@echo "Makefile Debug Info:"
	@echo "Shell: $(SHELL)"
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "Includes: $(INCLUDES)"
	@echo "Libs: $(LIBS)"
	@echo "Output Main: $(OUTPUTMAIN)"
# DEBUG -----------------------------------------------------------------------
