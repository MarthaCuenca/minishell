//42header

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

/*** *** *** *** *** *** *** *** *** ENV *** *** *** *** *** *** *** *** ***/
t_list	*env_dup(char **env);
void	del_char_ptr(void *content);

/*** *** *** *** *** *** *** *** * LEXER * *** *** *** *** *** *** *** *** ***/

typedef enum e_start_end
{
	START = 0,
	END = 1,
}	t_start_end;

typedef enum e_quote
{
	NO_QUOTE = 0,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
	SIMPLE_QUOTE_IN,
	DOUBLE_QUOTE_IN,
	MIXED_QUOTE
}	t_quote;

typedef enum e_token_type
{
	WORD = 0,
	EXP,
	PIPE,
	DIR_IN,
	DIR_OUT,
	APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*token;
	t_quote			quote_type;
	t_token_type	type;
}	t_token;

t_list	*lexer(char *cmmd);
int	count_token(char *cmmd);
t_list	*save_token(char *cmmd);
t_list	*split_one_token(t_list	**token_list);
void	del_t_token(void *token_nd);
void	print_tokens(t_list *tokens, t_bool all, int n);
void	is_quote(char *cmmd, int *quote_state, int *end, int *i);
void	*new_token(t_list **head, char *cmmd, int start, int end);

/*** *** *** *** *** *** *** *** *PARSER * *** *** *** *** *** *** *** *** ***/

typedef struct	t_cmmd
{
	char 	*cmmd;
	char	**args;
	void	*input;
	void	*output;
}

t_bool	parser(t_list *lex);
#endif
