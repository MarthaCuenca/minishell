//42header

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define TRUE 1

# define FALSE 0

/*** *** *** *** *** *** *** *** *** ENV *** *** *** *** *** *** *** *** ***/
t_list	*env_dup(char **env);
void	del_content(void *content);

#endif
