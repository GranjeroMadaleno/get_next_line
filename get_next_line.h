/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andefern <andefern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:29:46 by andefern          #+#    #+#             */
/*   Updated: 2023/12/26 17:31:20 by andefern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 11
# endif

int		ft_len(const char *k);
void	*ft_mcpy(void *dst, const void *src, size_t n);
char	*ft_dup(const char *s);
char	*ft_schr(const char *s, int c);
char	*ft_sjoin(char const *s1, char const *s2);
char	*bucket(char *luftbuffer);
char	*bruce(int fd, char *luftbuffer, int *read_bytes);
char	*get_next_line(int fd);

#endif
