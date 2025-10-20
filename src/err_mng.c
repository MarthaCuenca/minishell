/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_mng.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:25:01 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/20 18:20:01 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	malloc_err(void)//mirar aqui y abajo, porque aun hay archivos que los usan
{
	printf("Error: malloc falied.\n");
}

/*void	arg_err(void)
{
	printf("Error: expected arguments are missing.\n");
}*/

void	syntax_err(int err, char *str, char c)
{
	if (err == 1)
		printf("Error: syntax error near unexpected token:`%c'\n", c);
	if (err == 2)
		printf("Error: syntax error near unexpected token:`%s'\n", str);
	else if (err == 3)
		ft_putstr_fd("Error: quotations marks are not closed\n", 2);
}

void	bi_err_mng(int err, char *cmmd, char *not_found)
{
	if (err == 1)
		printf("Error: %s: too many arguments\n", cmmd);
	else if (err == 2)
		printf("Error: %s: %s not set\n", cmmd, not_found);
	else if (err == 3)
		printf("Error: %s: %s: No such file or directory\n", cmmd, not_found);
	else if (err == 4)
		printf("Error: %s: %s: Permission denied\n", cmmd, not_found);
}
