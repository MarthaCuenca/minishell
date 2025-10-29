/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_mng.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:25:01 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/29 19:52:04 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void	malloc_err(void)
{
	printf("Error: malloc falied.\n");
}

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
	else if (err == 5)
		printf("Error: %s: %s: numeric argument required\n", cmmd, not_found);
	else if (err == 6)
		printf ("Error: %s: `%s': not a valid identifier\n", cmmd, not_found);
}

t_state	chdir_err_mng(char *cmmd)
{
	if (errno == EACCES)
		printf ("Error: cd: %s: %s\n", cmmd, strerror(errno));
	else if (errno == EFAULT)
		printf ("Error: cd: %s: %s\n", cmmd, strerror(errno));
	else if (errno == EIO)
		printf ("Error: cd: %s: %s\n", cmmd, strerror(errno));
	else if (errno == ELOOP)
		printf ("Error: cd: %s: %s\n", cmmd, strerror(errno));
	else if (errno == ENAMETOOLONG)
		printf ("Error: cd: %s: %s\n", cmmd, strerror(errno));
	else if (errno == ENOENT)
		printf ("Error: cd: %s: %s\n", cmmd, strerror(errno));
	else if (errno == ENOTDIR)
		printf ("Error: cd: %s:%s\n", cmmd, strerror(errno));
	return (ST_ERR);
}

t_state	getpwd_err_mng(void)
{
	if (errno == ENOMEM)
		return (malloc_err(), ST_ERR_MALLOC);
	return (ST_ERR);
}
