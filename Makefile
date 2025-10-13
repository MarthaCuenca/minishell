#header

NAME := minishell
LIB := libft
VERBOSE ?= 1
export VERBOSE

LIB_PATH := $(LIB)/$(LIB).a
SRC_PATH := src
OBJ_PATH := obj

HEAD := include/minishell.h \

SRCS := src/main.c \
		src/env.c \
		src/lexer.c \
		src/del_function.c \
		src/save_token.c \
		src/split_one_token.c \
		src/parser.c \
		src/save_cmmd.c \
		src/expander.c \
		src/quote_removal.c \
		src/excecutor.c \
		src/cmmd.c \
		src/cmmd_transform_namepath.c \
		src/cmmd_utils.c \
		src/heredoc.c \
		src/list_to_array.c \
		src/error_mng.c \
		src/cmmd_builtin.c \
		src/builtin_echo.c \
		src/builtin_cd.c \
		src/builtin_export.c \
		src/builtin_unset.c \
		src/builtin_pwd.c \
		src/builtin_env.c \
		src/builtin_exit.c \
		src/utils.c \
		src/print_util.c \
		src/signal.c

OBJS := $(SRCS:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
DEPS := $(OBJS:.o=.d)

CC := cc
CFLAGS := -Wall -Werror -Wextra -g -MMD -MP
CFLAGS_I := -Iinclude -I $(LIB)

LIB_SRCS := $(addprefix $(LIB)/, $(shell $(MAKE) -s -C $(LIB) export_srcs))


# =========================================================================

all: $(LIB_PATH) $(NAME)

$(NAME): $(LIB_PATH) $(OBJS) Makefile
	$(CC) $(CFLAGS) $(CFLAGS_I) $(OBJS) $(LIB_PATH) -o $(NAME) -lreadline

$(LIB_PATH): $(LIB_SRCS)
	$(MAKE) -C $(LIB)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(CFLAGS_I) -c -o $@ $<

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

export_src:
	@echo $(SRCS)

export_head:
	@echo $(HEAD)

test:
	$(MAKE) -C test test

-include $(DEPS)

.PHONY: all clean fclean re export_src export_head test
