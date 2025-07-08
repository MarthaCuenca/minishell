# My tests

LIB = minishell.a
LIBFT = ../libft/libft.a
UTILS = utils/test_utils.c
SRC_MINISHELL := $(filter-out %main.c, $(addprefix ../, $(shell $(MAKE) -s -C ../ export_src)))
HEAD_MINISHELL := $(addprefix ../, $(shell $(MAKE) -s -C ../ export_head))
OBJ_MINISHELL := $(SRC_MINISHELL:.c=.o)

SRC_TEST := $(wildcard src/*)
EXE_TEST := $(patsubst src/%.c, bin/%, $(SRC_TEST))

CC := cc
CFLAGS := -Wall -Wextra -Werror -O2 -I../include -I../libft -Iutils

VERBOSE = 1

# ===========================================================

# Creation of binaries

all: $(EXE_TEST) Makefile

bin/%: src/%.c $(LIB)
	@mkdir -p bin
	$(CC) $(CFLAGS) $< $(UTILS) $(LIB) -o $@

# Creation of library
$(LIB): $(OBJ_MINISHELL) $(LIBFT) Makefile
	cp $(LIBFT) $(LIB)
	ar rcs $(LIB) $(OBJ_MINISHELL)

$(LIBFT):
	$(MAKE) -s -C ../libft

$(OBJ_MINISHELL): | make_parent

make_parent:
	@$(MAKE) -s -C ..

# Clean
clean:
	rm -rf bin

fclean:
	$(MAKE) -s clean
	rm -f $(LIB)

test: all
	@echo "== Running tests =="
	@for exe in $(EXE_TEST); do \
		if [ $(VERBOSE) -ge 1 ]; then \
			echo "    Testing $$exe..."; \
		fi; \
		./$$exe $(VERBOSE); \
		status=$$?; \
		if [ $$status -ne 0 ]; then \
			echo "    ❌ Test $$exe."; \
			exit $$status; \
		elif [ $(VERBOSE) -ge 1 ]; then \
			echo "    ✅ Test $$exe."; \
		fi; \
	done
	@echo "✅ All tests passed."



.PHONY: make_parent test
