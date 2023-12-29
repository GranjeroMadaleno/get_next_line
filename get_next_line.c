/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andefern <andefern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:10:44 by andefern          #+#    #+#             */
/*   Updated: 2023/12/29 12:57:52 by andefern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_readfd(char *str, int fd)
{
	char	*buffer;
	int		i;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	i = 1;
	while (ft_schr(str, '\n') == NULL && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		str = ft_sjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*ft_static(char	*str)
{
	char	*fresh;
	size_t	j;
	size_t	k;

	k = 0;
	while (str[k] != '\n' && str[k] != '\0')
		k++;
	if (ft_len(str) == k)
	{
		free(str);
		return (NULL);
	}
	fresh = (char *)malloc((ft_len(str) - k + 1) * sizeof(char));
	if (fresh == NULL)
		return (NULL);
	j = 0;
	while (str[k++])
	{
		fresh[j] = str[k];
		j++;
	}
	fresh[j] = '\0';
	free(str);
	return (fresh);
}

char	*newline(char *temp)
{
	char	*row;
	size_t	k;
	size_t	j;

	k = 0;
	if (temp[0] == '\0')
		return (NULL);
	while (temp[k] != '\n' && temp[k] != '\0')
		k++;
	if (temp[k] == '\n')
		k++;
	row = (char *)malloc(sizeof(char) * k + 1);
	if (row == NULL)
		return (NULL);
	j = 0;
	while (j < k)
	{
		row[j] = temp[j];
		j++;
	}
	row[j] = '\0';
	return (row);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_readfd(str, fd);
	if (str == NULL)
		return (NULL);
	buffer = newline(str);
	str = ft_static(str);
	return (buffer);
}

/* int	main(void)
{
	int	fd;
	char	*str;

	fd = open("txt.txt", O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	printf("%s\n", str);
	close(fd);
} */
