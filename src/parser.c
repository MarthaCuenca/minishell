/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:19:06 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/03 19:09:05 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* errores de SINTAXIS en cmmds, flags, args, pipes y redicciones
 * condiciones de colocacion de los tokens.
 * ver se me meten un input, ver si suelto un output*/

/*excutor: 
 command + (opcional)flag/option 
 + arg(str/file(delimitador)/path) (estructura AST)*/

/*PIPE:
 * * no ser el 1ro
 * * estar entre WORDs
 * * no ir 2 PIPEs seguidos*/
static t_bool	is_x_symbol(int x, int *symbols, int len)
{
	int	i;

	if (!symbols)
		return (FALSE);
	i = 0;
	//while (symbols[i] && x != symbols[i])
	while (i < len && x != symbols[i])
		i++;
	if (x == symbols[i])
		return (TRUE);
	return (FALSE);
}

t_bool	is_double_word_after_ineq_symbol(t_list *lex, int *symbols)
{
	int		tk_ty[3];
	t_bool	is_dir;
	t_list	*tmp;

	tmp = lex;
	while (tmp)
	{
		tk_ty[CURR] = ((t_token *)tmp->content)->type;
		is_dir = is_x_symbol(tk_ty[CURR], symbols, 4);
		if (is_dir)
		{
			//if (((t_token *)tmp->next->content)->type)
			tk_ty[NEXT] = ((t_token *)tmp->next->content)->type;
			if (tk_ty[NEXT] != WORD)
				return (TRUE);
			else if (tk_ty[NEXT] == WORD && tmp->next->next 
				&& ((t_token *)tmp->next->next->content)->type == WORD)
				return (TRUE);
		}
		tmp = tmp->next;
	}
	return (FALSE);
}
/*t_bool	is_double_word_after_ineq_symbol(t_list *lex, int *symbols)
{
	int		tk_ty[2];
	t_list	*tmp;

	tmp = lex;
	while (tmp->next)
	{
		tk_ty[CURR] = ((t_token *)tmp->content)->type;
		tk_ty[NEXT] = ((t_token *)tmp->next->content)->type;
		if (is_x_symbol(tk_ty[CURR], symbols, 4) && tk_ty[NEXT] == WORD)
			if (tmp->next->next
				&& ((t_token *)tmp->next->next->content)->type == WORD)
				return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}*/

t_bool	is_ineq_symbol_at_end(t_list *lex, int *symbols)
{
	int	last_nd;

	last_nd = ((t_token *)ft_lstlast(lex)->content)->type;
	if (is_x_symbol(last_nd, symbols, 4))// OJO aqui, que ha invertido el t_bool
		return (TRUE);
	return (FALSE);
}

//despues de >,<,>>,<< solo puede haber 1 WORD
t_bool	inequality_symbols_syntax(t_list *lex)
{
	int		symbols[4];
	t_list	*tmp;

	if (!lex)
		return (FALSE);
	symbols[0] = DIR_IN;
	symbols[1] = DIR_OUT;
	symbols[2] = APPEND;
	symbols[3] = HEREDOC;
	if (!lex)
		return (FALSE);
	tmp = lex;
	if (is_ineq_symbol_at_end(lex, symbols)) //< hola, > adios; siempre va con el simbolo de la iezquierda
		return (FALSE);
	if (is_double_word_after_ineq_symbol(lex, symbols))
		return (FALSE);
	return (TRUE);
}

t_bool	is_pipe_misplaced(t_list *lex)
{
	int		tk_ty[3];
	t_list	*tmp;

	tmp = lex;
	while (tmp->next)
	{
		tk_ty[CURR] = ((t_token *)tmp->content)->type;
		tk_ty[NEXT] = ((t_token *)tmp->next->content)->type;
		if (tk_ty[CURR] == PIPE)
			if (tk_ty[PREV] != WORD || tk_ty[NEXT] != WORD)
				return (TRUE);
		tk_ty[PREV] = tk_ty[CURR];
		tmp = tmp->next;
	}
	return (FALSE);
}

t_bool	is_pipe_at_start_or_end(t_list *lex)
{
	int	first_nd;
	int	last_nd;

	if (!lex)
		return (TRUE);
	first_nd = ((t_token *)lex->content)->type;
	last_nd = ((t_token *)ft_lstlast(lex)->content)->type;
	if (first_nd == PIPE)
		return (TRUE);
	else if (last_nd == PIPE)
		return (TRUE);
	return (FALSE);
}

t_bool	pipe_syntax(t_list *lex)
{
	if (!lex)
		return (FALSE);
	if (is_pipe_at_start_or_end(lex))
		return (FALSE);
	if (is_pipe_misplaced(lex))
		return (FALSE);
	return (TRUE);
}

//y esto casos ";, &, \ "?
t_bool	syntax(t_list *lex)
{
	if (!lex)
		return (FALSE);
	if (!pipe_syntax(lex))
		return (FALSE);
	if (!inequality_symbols_syntax(lex))
		return (FALSE);
	return (TRUE);
}

t_list	*parser(t_list **lex)
{
	t_list	*pars;

	if (!*lex)
		return (NULL);
	pars = NULL;
	if (!syntax(*lex))
		return (NULL);
	/*pars = save_cmmd(lex);
	if (!pars)
		return (NULL);*///ESTO en esta version no se hizo porque cambiamos la struct t_cmmd
	print_tokens(lex, TRUE, 0);//
	return (pars);
}
//expand(lex);
//hacer el expander antes, porque $HOLA puede ser HOLA=ls ._.,luego de la syntax
/*cmmd_list = save_cmmd(lex);
//No siempre el primer token o despues de pipe  es un comando
if (!cmmd_list)
	return (NULL);
return (cmmd_list);*/
