/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:12:38 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/06 19:23:54 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_env
{
	struct s_env	*prev;
	char			*var;
	char			*id;
	char			*content;
	int				inx;
	struct s_env	*next;
}	t_env;

t_env	*ft_env_dup(char **env_ori);
void    ft_env_free(t_env **env_lst);

#endif
