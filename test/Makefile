# My tests

LIB = minishell.a
SRC_MINISHELL := $(filter-out %main.c, $(addprefix ../, $(shell $(MAKE) -s -C ../ export_src)))
HEAD_MINISHELL := $(addprefix ../, $(shell $(MAKE) -s -C ../ export_head))
OBJ_MINISHELL := $(SRC_MINISHELL:.c=.o)

SRC_TEST := $(wildcard src/*)
EXE_TEST := $(patsubst src/%.c, bin/%, $(SRC_TEST))

CC := cc
CFLAGS := -Wall -Wextra -Werror -O2 -I../include -I../libft

# ===========================================================

# Creation of binaries

all: $(EXE_TEST)

bin/%: src/%.c $(LIB)
	@mkdir -p bin
	$(CC) $(CFLAGS) $< $(LIB) -o $@

# Creation of library
$(LIB): $(OBJ_MINISHELL) Makefile
	ar rcs $(LIB) $(OBJ_MINISHELL)

$(OBJ_MINISHELL): | make_parent

make_parent:
	@$(MAKE) -s -C ..

# Clean
clean:
	rm -f $(EXE_TEST)
	rm -fd bin

fclean:
	$(MAKE) -s clean
	rm -f $(LIB)

test: all
	@echo "== Running tests =="
	@for exe in $(EXE_TEST); do \
		echo "Running $$exe..."; \
		./$$exe; \
		status=$$?; \
		if [ $$status -ne 0 ]; then \
			echo "Test $$exe FAILED with status $$status"; \
			exit $$status; \
		fi; \
	done
	@echo "✅ All tests passed."



.PHONY: make_parent test
