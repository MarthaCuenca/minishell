#header

NAME := minishell
LIB := libft

LIB_PATH := $(LIB)/$(LIB).a
SRC_PATH := src
OBJ_PATH := obj

HEAD := include/minishell.h

SRCS := src/main.c \

OBJS := $(SRCS:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
DEPS := $(OBJS:.o=.d)

CC := cc
CFLAGS := -Wall -Werror -Wextra -g -MMD -MP
CFLAGS_I := -Iinclude -I$(LIB)

LIB_SRCS := $(addprefix $(LIB)/, $(shell $(MAKE) -s -C $(LIB) export_srcs))


# =========================================================================

all: $(LIB_PATH) $(NAME)

$(NAME): $(OBJS) Makefile
	$(CC) $(OBJS) $(LIB_PATH) $(MLX_PATH) $(CFLAGS_I) $(CFLAGS_L) -o $(NAME)

$(LIB_PATH): $(LIB_SRCS)
	$(MAKE) -C $(LIB)
	$(MAKE) re

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(CFLAGS_I) -c -o $@ $<

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

clean:
	rm -f $(OBJS) $(DEPS)
	rm -fd $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX)


re: fclean all

export_src:
	@echo $(SRCS)

export_head:
	@echo $(HEAD)

-include $(DEPS)

.PHONY: all clean fclean re
