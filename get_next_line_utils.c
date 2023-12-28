/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andefern <andefern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:18:09 by andefern          #+#    #+#             */
/*   Updated: 2023/12/28 13:54:47 by andefern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_len(const char *k)
{
	int	i;

	i = 0;
	if (!k)
		return (0);
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

	dest = malloc(sizeof(char) * (ft_len(s) + 1));
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
