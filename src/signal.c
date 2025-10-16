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

void	setup_signal_standard(void (*fsigint)(int), void (*fsigquit)(int))
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	g_signal = 0;
	sa1.sa_handler = fsigint;
	sa1.sa_flags = 0;
	sigemptyset(&sa1.sa_mask);
	sa2.sa_handler = fsigquit;
	sa2.sa_flags = 0;
	sigemptyset(&sa2.sa_mask);
	sigaction(SIGINT, &sa1, NULL);
	sigaction(SIGQUIT, &sa2, NULL);
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
