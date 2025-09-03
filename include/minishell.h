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
void	quote_mng(char *cmmd, int *quote_state, int *end, int *i);
void	*new_token(t_list **head, char *cmmd, int start, int end);
t_bool	is_special_dollar(char *str, int len);
t_bool	is_c_symbol(char c, char *symbols);

/*** *** *** *** *** *** *** *** *PARSER * *** *** *** *** *** *** *** *** ***/
/*typedef struct s_redir
{
	char			*file;
	t_token_type	type;
}	t_redir;

typedef struct	s_cmmd
{
	char	**cmmd;
	char	***args;
	t_redir	*infile;
	t_redir	*outfile;
	char	**env;
	int		r;
}	t_cmmd;*/


/*typedef struct	s_env
{
	t_list	*env;
	int		r;
}	t_env;

typedef struct s_redir
{
	char			*file;
	t_token_type	type;
	int				fd_heredoc;
	t_redir			*next;
}	t_redir;

typedef struct	s_cmmd
{
	char	**cmmd;
	t_redir	*dir;
	t_env	*env;
	int		r;
}	t_cmmd;*/

typedef enum s_pr_crr_nx
{
	PREV = 0,
	CURR,
	NEXT,
}	t_pr_crr_nx;

t_list	*parser(t_list **lex);
t_list	*save_cmmd(t_list **lex);

/*** *** *** *** *** *** *** *** EXPANDER* *** *** *** *** *** *** *** *** ***/

t_bool expander(t_list **lex, t_list *env, t_cmmd *return_value);
void	ft_free_2p(char **array);
void	print_array_2p(char **array);
void	del_t_cmmd(void *cmmd_nd);

#endif
