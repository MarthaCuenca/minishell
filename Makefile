#header

NAME := minishell
LIB := libft
VERBOSE ?= 1
export VERBOSE

LIB_PATH := $(LIB)/$(LIB).a
SRC_PATH := src
OBJ_PATH := obj

HEAD := include/minishell.h \
	include/env.h

SRCS := src/main.c \
		src/env_v3.c \
		src/lexer.c
#src/env_cp_array.c

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
