/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:18:40 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/16 16:10:28 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stddef.h>
# include <sys/types.h>
# include <signal.h>

extern volatile sig_atomic_t	g_signal;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_state
{
	ST_OK = 0,
	ST_ERR_MALLOC = -1,
	ST_ERR_FD = -2,
	ST_ERR = -4,
}	t_state;

/*** *** *** *** *** *** *** *** *** ENV *** *** *** *** *** *** *** *** ***/

typedef struct s_env
{
	t_list	*vars;
	int		r;
}	t_env;

t_list	*env_dup(char **env);
char	**env_to_array(t_env *mini_env);

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

typedef enum e_redir_type
{
	DIR_IN = 0,
	DIR_OUT,
	APPEND,
	HEREDOC
}	t_redir_type;

typedef enum e_token_type
{
	WORD = 0,
	EXP,
	PIPE,
	REDIR
}	t_token_type;

typedef struct s_token
{
	char			*token;
	t_quote			quote_type;
	t_token_type	type;
}	t_token;

t_list	*lexer(char *cmmd);
t_list	*save_token(char *cmmd);
void	quote_mng(char *cmmd, int *quote_state, int *end, int *i);
void	*new_token(t_list **head, char *cmmd, int start, int end);
t_list	*split_one_token(t_list	**token_list);
t_quote	token_quo_type(char *str);
t_bool	is_special_dollar(char *str, int len);

/*** *** *** *** *** *** *** *** *PARSER * *** *** *** *** *** *** *** *** ***/

typedef struct s_redir
{
	char			*file;
	t_redir_type	type;
	int				fd_heredoc;
}	t_redir;

typedef struct s_cmmd
{
	char	**cmmd;
	t_redir	*redir; //merge: redir
}	t_cmmd;

typedef enum s_pr_crr_nx
{
	PREV = 0,
	CURR,
	NEXT,
}	t_pr_crr_nx;

t_list	*parser(t_list **lex);
t_list	*save_cmmd(t_list **lex);

/*** *** *** *** *** *** *** *** EXPANDER* *** *** *** *** *** *** *** *** ***/

t_bool	expander(t_env *mini_env, t_list **pars);
t_bool	quote_removal(t_list **pars);
t_list	*check_env_var(char *str, int in_len, t_list *env);
char	*get_env_value(t_list *match, int var_len);;
//int		varname_len_in_str(char *start);
int		env_key_len(char *str, int c);
t_bool	exp_mng(t_env *env, char **str);
char 	*obtain_env_var_value(t_env *env, char *dollar);

/*** *** *** *** *** *** *** *** EXCECUTOR *** *** *** *** *** *** *** *** ***/

typedef struct s_pipe_data
{
	int	pid;
	int	last_pid;
	int	pipefd[2];
	int	fd_prev;
	int	count;
}	t_pipe_data;

void	clean_mng(t_env *mini_env, char **cmmd, t_list **lex, t_list **pars);
int		excecutor(t_list *lst_cmmd, t_env *tenv);

// CMMD
int		manage_infile(t_cmmd *cmmd, t_env *env);
int		manage_outfile(t_cmmd *cmmd, t_env *env);
int		exec_cmmd(t_list *lst_cmmd, t_env *env);
int		is_builtin(char *str);
void	choose_builtin(t_cmmd *cmmd, t_env *env);
int		exec_if_1builtin(t_list *lst_cmmd, t_env *env);
int		pipe_e(int pipefd[2], t_env *env);
void	execve_e(t_cmmd *cmmd, t_env *env);
int		fork_e(pid_t pid, t_env *env);
int		count_files(t_redir *redir, int type);
int		process_exit_status(t_pipe_data *pipe_data);
// Init
t_list	*init_lst_cmmd(char **argv);
void	free_cmmd_node(void *ptr);
int		correct_cmmd_namepath(t_list *lst_cmmd, t_env *env);
int		create_heredocs(t_list *lst_cmmd, t_env *env);
void	close_heredocs(t_list *lst_cmmd);
char	*create_filename(char *str_name, int counter, t_env *env);

// Utils
void	print_lst_cmmd(t_list *lst_cmmd);
int		get_error(t_env *env, t_state state, char *msg);
char	*get_error_chr(t_env *env, t_state state, char *msg);
int		builtin_echo(t_cmmd *nd);
int		builtin_cd(t_env *mini_env, char **cmmd);
int		builtin_pwd(t_env *mini_env);
int		builtin_export(t_env *mini_env, char **cmmd);
int		builtin_unset(t_env *mini_env, char **cmmd);
int		builtin_env(t_env *mini_env);
void	builtin_exit(t_env *mini_env, t_list **pars, t_cmmd *nd);

// Signals
void	setup_signal_prompt(void);
void	setup_signal_heredoc(void);
void	setup_signal_standard(void (*fsigint)(int), void (*fsigquit)(int));
int		update_heredoc(t_env *env, t_list *lst_cmmd);
void	update_r(t_env *env);
/*** *** *** *** *** *** *** *** * UTILS * *** *** *** *** *** *** *** *** ***/

void	del_char_ptr(void *str);
void	del_t_token(void *token_nd);
void	del_t_cmmd(void *cmmd_nd);
void	del_t_env(void *mini_env);
void	del_t_redir(void *dir_array);
void	print_tokens(t_list *tokens, t_bool all, int n);//
void	print_cmmds(t_list *cmmds, t_bool all, int n);//
void	print_array_2p(char **array);
t_bool	starter_err(int argc, char **envp);
void	malloc_err(void);
void	arg_err(void);
void	export_bi_err(char *str);
int		count_token(char *cmmd);
t_bool	is_c_symbol(char c, char *symbols);

#endif
