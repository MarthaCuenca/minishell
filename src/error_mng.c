/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:25:01 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/19 14:05:43 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_bool	starter_err(int argc, char **envp)
{
	if (argc != 1)
		return (printf("Error: only 1 argument.\n"), TRUE);
	if (!envp)
		return (printf("Error: environment was not founded.\n"), TRUE);
	return (FALSE);
}

void	malloc_err(void)
{
	printf("Error: malloc faied.\n");
}

void	arg_err(void)
{
	printf("Error: expected arguments are missing.\n");
}
