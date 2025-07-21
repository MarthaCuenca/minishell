//42header

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define TRUE 1

# define FALSE 0

/*** *** *** *** *** *** *** *** *** ENV *** *** *** *** *** *** *** *** ***/
t_list	*env_dup(char **env);
void	del_content(void *content);

/*** *** *** *** *** *** *** *** * LEXER * *** *** *** *** *** *** *** *** ***/

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
	DIR_OUT
}	t_token_type;

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	t_quote			quote_type;
	void			*next;
}	t_token;

t_token	*lexer(char *cmmd);
//void	lexer(char *cmmd);

#endif
