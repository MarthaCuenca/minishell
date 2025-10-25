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
		src/env_shlvl.c\
		src/lexer.c \
		src/del_function.c \
		src/save_token.c \
		src/split_one_token.c \
		src/parser.c \
		src/parser_pipe.c \
		src/parser_inequality_symbols.c  \
		src/save_cmmd.c \
		src/expander.c \
		src/quote_removal.c \
		src/quote_removal_mng.c \
		src/excecutor.c \
		src/cmmd.c \
		src/cmmd_transform_namepath.c \
		src/cmmd_utils.c \
		src/cmmd_utils_error.c \
		src/heredoc.c \
		src/heredoc_utils.c \
		src/list_to_array.c \
		src/err_mng.c \
		src/cmmd_builtin.c \
		src/builtin_echo.c \
		src/builtin_cd.c \
		src/builtin_export.c \
		src/builtin_unset.c \
		src/builtin_pwd.c \
		src/builtin_env.c \
		src/builtin_exit.c \
		src/bi_cd_path.c \
		src/bi_cd_up_path.c \
		src/bi_export_print.c \
		src/utils.c \
		src/ft_utils.c \
		src/signal.c \
		src/signal_updater.c

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

$(LIB_PATH): $(LIB_SRCS) $(LIB)/Makefile
	$(MAKE) -C $(LIB)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(CFLAGS_I) -c -o $@ $<

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

clean:
	rm -rf $(OBJ_PATH)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

export_src:
	@echo $(SRCS)

export_head:
	@echo $(HEAD)

-include $(DEPS)

.PHONY: all clean fclean re export_src export_head
