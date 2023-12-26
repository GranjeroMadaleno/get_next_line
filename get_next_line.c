/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andefern <andefern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:10:44 by andefern          #+#    #+#             */
/*   Updated: 2023/12/26 13:52:54 by andefern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


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
	if (s == NULL)
		return (NULL);
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

	//bucket tiene que encontrar donde está \n
	//tiene que reservar un string de tamaño desde 0 hasta \n + 1
	//crear un malloc de este tamaño y guardar el contenido del string
char	*bucket(char *luftbuffer)
{
	char	*bile;
	int		k;

	k = 0;
	if (luftbuffer == NULL)
		return (NULL);
	while (luftbuffer[k] != '\0' && luftbuffer[k] != '\n')
		k++;
	bile = malloc(sizeof(char) * k + 1);
	k = 0;
	while (luftbuffer[k] != '\0' && luftbuffer[k] != '\n')
	{
		bile[k] = luftbuffer[k];
		k++;
	}
	bile[k] = luftbuffer[k];
	k++;
	bile[k] = '\0';
	return (bile);
}

char	*bruce(int fd, char *luftbuffer, int *read_bytes)
{
	char	*reading;
	char	*temp;
	char	*save;

	save = ft_dup(luftbuffer);
	reading = malloc(sizeof(char) * BUFFER_SIZE + 1);
	reading[BUFFER_SIZE] = '\0';
	*read_bytes = read(fd, reading, BUFFER_SIZE);
	reading[*read_bytes] = '\0';
	if (*read_bytes <= 0 && luftbuffer[0] == '\0')
		return (NULL);
	free(luftbuffer);
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
	int			read_bytes;

	if (rest == NULL || rest[0] == '\0')
	{
		luftbuffer = malloc(sizeof(char));
		luftbuffer[0] = '\0';
	}
	else if (rest != NULL && ft_schr(rest, '\n') != NULL)
	{
		puke = bucket(rest);
		rest = ft_dup(ft_schr(rest, '\n') + 1);
		return (puke);
	}
	else
		luftbuffer = ft_dup(rest);
	read_bytes = 1;
	while (read_bytes > 0 && luftbuffer && !ft_schr(luftbuffer, '\n'))
		luftbuffer = bruce(fd, luftbuffer, &read_bytes);
	puke = bucket(luftbuffer);
	if (ft_schr(luftbuffer, '\n') != NULL)
		rest = ft_dup(ft_schr(luftbuffer, '\n') + 1);
	else
		rest = NULL;
	return (puke);
}

/*
int	main(void)
{
	int		fd;
	char	*str;

	fd = open("txt.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	while (str)
	{
		printf("out:\n%s", str);
		free(str);
		str = get_next_line(fd);
	}
	return (0);
}
*/