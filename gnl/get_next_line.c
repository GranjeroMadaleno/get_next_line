/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andefern <andefern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:10:44 by andefern          #+#    #+#             */
/*   Updated: 2023/12/22 12:33:49 by andefern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

int	ft_len(const char *k)
{
	int	i;

	i = 0;
	while (k[i])
		i++;
	return (i);
}

void	*ft_mcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n--)
	{
		*d++ = *s++;
	}
	return (dst);
}

char	*ft_dup(const char *s)
{
	char	*dest;

	dest = malloc((ft_len(s) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_mcpy(dest, s, ft_len(s));
	dest[ft_len(s)] = '\0';
	return (dest);
}

char	*ft_schr(const char *s, int c)
{
	while (*s != '\0' && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_sjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	i = 0;
	j = 0;
	len = ft_len(s1) + ft_len(s2);
	str = malloc(sizeof (char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*bruce(int fd, char *luftbuffer)
{
	char	*reading;
	char	*temp;
	char	*save;
	size_t	read_bytes;

	save = ft_dup(luftbuffer);
	free(luftbuffer);
	reading = malloc(sizeof(char) * BUFFER_SIZE + 1);
	reading[BUFFER_SIZE] = '\0';
	read_bytes = read(fd, reading, BUFFER_SIZE);
	if (read_bytes <= 0)
		return (NULL);
	temp = ft_sjoin(save, reading);
	free(save);
	free(reading);
	return (temp);

}

char	*get_next_line(int fd)
{
	char		*luftbuffer;
	char		*puke;
	static char	*rest;

	luftbuffer = malloc(sizeof(char));
	luftbuffer[0] = '\0';
	while (!ft_schr(luftbuffer, '\n') && luftbuffer != NULL)
		luftbuffer = bruce(fd, luftbuffer);
	puke = bucket(luftbuffer);
	rest = ft_dup(ft_schr(luftbuffer, '\n') + 1);
	return (puke);
}

int	main(void)
{
	int	fd;

	fd = open("txt.txt", O_RDONLY);

	printf("out:\n%s", get_next_line(fd));
	return (0);
}
