/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:54:40 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/28 18:07:00 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "minishell.h"
#include "test_utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

static int check_quotes(t_list *tokens)
{
	t_token *tmp;

	if (!tokens)
		return (0);
	tmp = (t_token *)tokens->content;
	while (tmp)
	{
		if (ft_strchr(tmp->token, '\'') && tmp->quote_type == SIMPLE_QUOTE)
			return (0);
		else if (ft_strchr(tmp->token, '\"') && tmp->quote_type == DOUBLE_QUOTE)
			return (0);
		tmp = (t_token *)tokens->next->content;
	}
	return (1);
}
static int	compare_n_token(t_list *tokens, char *cmmd)
{
	int	i;
	int	j;

	i = count_token(cmmd);
	j = ft_lstsize(tokens);
	if (i != j)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		test_result;
	char	verbose;
	char	*get_cmmd;
	t_list	*check;

	(void)argc;
	fd = open("../utils/lexer_cmmd.txt", O_RDONLY);
	verbose = argv[1][0];
	get_cmmd = "";
	while (get_cmmd)
	{
		if (get_cmmd && get_cmmd[0] != '\0')
			free(get_cmmd);
		get_cmmd = get_next_line(fd);
		check = lexer(get_cmmd);
		test_result = compare_n_token(check, get_cmmd);
		eval_result(test_result, verbose, "lexer: ¿Cuántos tokens hay?");
		test_result = check_quotes(check);
		eval_result(test_result, verbose, "lexer: Comillas cerradas y abiertas correctamente");
		ft_lstclear(&check, del_t_token);
	}
	return (0);
}
