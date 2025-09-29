###############################################################################
################################## MAKEFILE ###################################
###############################################################################

# 递归通配函数（纯 make） ————---------------------------------------------------
rwildcard = $(foreach d,$(wildcard $1*), $(call rwildcard,$d/,$2)) \
            $(filter $(subst *,%,$2), $(wildcard $1$2))
# 递归通配函数（纯 make） ————---------------------------------------------------

# gitbash mingw64 -------------------------------------------------------------
MD := mkdir -p
RM := rm -rf
# gitbash mingw64 -------------------------------------------------------------

# 编译器与选项 -----------------------------------------------------------------
CC := gcc
CFLAGS := -Wall -Wextra -g
LFLAGS :=
# 编译器与选项 -----------------------------------------------------------------

# 源代码、头文件目录、输出目录 ---------------------------------------------------
SRC_DIRS := .
INCLUDE_DIRS := include common/include
OUTPUT := output
# 源代码、头文件目录、输出目录 ---------------------------------------------------

# 搜索所有 .c 源文件（遍历多个源目录）
SRC_C := $(foreach d, $(SRC_DIRS), $(call rwildcard, $(d)/, *.c))

# 搜索所有 .h 头文件（遍历多个 include 目录）
SRC_H := $(foreach d, $(INCLUDE_DIRS), $(call rwildcard, $(d)/, *.h))

# 对象文件路径：把源目录结构镜像到 OUTPUT 下
# 如 src/foo/bar.c -> output/src/foo/bar.o
OBJS := $(patsubst %.c, $(OUTPUT)/%.o, $(patsubst %/%.c, %/%.c, $(SRC_C)))

# 可执行文件路径
OUTPUTMAIN := $(OUTPUT)/main.exe

.PHONY: all clean show run

all: $(OUTPUT) $(OUTPUTMAIN)
	@echo "Build complete: $(OUTPUTMAIN)"

# 确保 output 根目录存在
$(OUTPUT):
	$(MD) $(OUTPUT)

# 链接可执行文件
$(OUTPUTMAIN): $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

# 编译规则：把 output/…/.o 从相应的源 .c 文件生成
# 因为你有多个源目录，所以匹配模式要宽泛一点
# 假设你的源结构始终包含目录名（如 src/... 或 common/src/…）
$(OUTPUT)/%.o: %.c $(SRC_H) | $(OUTPUT)
	@echo "Compiling $< -> $@"
	@$(MD) $(dir $@)
	$(CC) $(CFLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -c $< -o $@

# run 目标：编译然后执行
run: all
	@echo "Running $(OUTPUTMAIN)..."
	@$(OUTPUTMAIN)

# 调试：显示列表
show:
	@echo "Makefile Debug Info:"
	@echo OS: $(SHELL)
	@echo "CC = $(CC)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "LFLAGS= $(LFLAGS)"
	@echo "SRC_DIRS = $(SRC_DIRS)"
	@echo "INCLUDE_DIRS = $(INCLUDE_DIRS)"
	@echo "OUTPUT = $(OUTPUT)"
	@echo "SRC_C = $(SRC_C)"
	@echo "SRC_H = $(SRC_H)"
	@echo "OBJS  = $(OBJS)"

clean:
	@echo "Cleaning..."
	$(RM) $(OUTPUT)
