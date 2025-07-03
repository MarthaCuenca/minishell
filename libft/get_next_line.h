/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:30:41 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/28 13:11:31 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_static
{
	ssize_t	pos0;
	ssize_t	pos1;
	ssize_t	bytes_loaded;
	char	buffer[BUFFER_SIZE + 1];
}	t_static;

// Main function
char	*get_next_line(int fd);

// Helper functions
char	*gnl_strjoin_free(char *str1, char *str2, unsigned int num_free);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
size_t	gnl_strlen(const char *str);

#endif
