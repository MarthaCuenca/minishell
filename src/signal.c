#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <readline/readline.h>

volatile sig_atomic_t	g_signal = 0;

static void	handler_prompt(int signo)
{
	if (signo == SIGINT)
	{
		g_signal = signo;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signal_prompt(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	g_signal = 0;
	sa_int.sa_handler = handler_prompt;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
	
}

static void	handler_parent(int signo)
{
	g_signal = signo;
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
	}
}

void	setup_signal_parent(void)
{
	struct sigaction	sa;

	g_signal = 0;
	sa.sa_handler = handler_parent;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	handler_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		g_signal = signo;
		ft_putstr_fd("\n", 1);
	}
}

void	setup_signal_heredoc(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	g_signal = 0;
	sa_int.sa_handler = handler_heredoc;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

int	update_heredoc(t_env *env, t_list *lst_cmmd)
{
	if (g_signal == SIGINT)
	{
		env->r = 128 + g_signal;
		close_heredocs(lst_cmmd);
		return (0);
	}
	return (1);
}

void	update_r(t_env *env)
{
	if (g_signal == SIGINT || g_signal == SIGQUIT)
		env->r = 128 + g_signal;
}
