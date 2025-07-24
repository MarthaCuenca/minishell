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
	DOUBLE_QUOTE
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
void	del_t_token(void *token_nd);
//void	lexer(char *cmmd);

#endif
