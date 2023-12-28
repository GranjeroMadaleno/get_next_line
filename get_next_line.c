/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andefern <andefern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:10:44 by andefern          #+#    #+#             */
/*   Updated: 2023/12/28 14:02:27 by andefern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.c"
#include "get_next_line.h"

	//bucket tiene que encontrar donde está \n
	//tiene que reservar un string de tamaño desde 0 hasta \n + 1
	//crear un malloc de este tamaño y guardar el contenido del string

/**
 * @brief 
 * 
 * @param luftbuffer 
 * @return char* 
 */

char	*bucket(char *luftbuffer)
{
	char	*bile;
	int		k;

	k = 0;
	if (luftbuffer == NULL)
		return (NULL);
	while (luftbuffer[k] != '\0' && luftbuffer[k] != '\n')
		k++;
	bile = malloc(sizeof(char) * (k + 1));
	k = 0;
	while (luftbuffer[k] != '\0' && luftbuffer[k] != '\n')
	{
		bile[k] = luftbuffer[k];
		k++;
	}
	bile[k] = luftbuffer[k];
	bile[k] = '\0';
	return (bile);
}

/**
 * @brief 
 * 
 * @param fd 
 * @param luftbuffer 
 * @param read_bytes 
 * @return char* 
 */

char	*bruce(int fd, char *luftbuffer, int *read_bytes)
{
	char	*reading;
	char	*temp;
	char	*save;

	save = ft_dup(luftbuffer);
	reading = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	*read_bytes = read(fd, reading, BUFFER_SIZE);
	reading[*read_bytes] = '\0';
	if (*read_bytes <= 0 && luftbuffer[0] == '\0')
		return (free(save), free(reading), NULL);
	free(luftbuffer);
	temp = ft_sjoin(save, reading);
	free(save);
	free(reading);
	return (temp);
}

/**
 * @brief Get the next line object
 * 
 * @param fd 
 * @return char* 
 */

char	*get_next_line(int fd)
{
	char		*luftbuffer;
	char		*puke;
	static char	*rest = NULL;
	int			read_bytes;
	char		*MIKA_TEMPORAL;

	MIKA_TEMPORAL = NULL;
	if (rest && ft_schr(rest, '\n') != NULL)
	{
		puke = bucket(rest);
		MIKA_TEMPORAL = ft_dup(ft_schr(rest, '\n') + 1);
		free(rest);
		rest = ft_dup(MIKA_TEMPORAL);
		free(MIKA_TEMPORAL);
		return (puke);
	}
	else if (rest == NULL)
	{
		luftbuffer = malloc(1);
		luftbuffer[0] = '\0';
	}
	else
		luftbuffer = ft_dup(rest);
	read_bytes = 1;
	while (read_bytes > 0 && luftbuffer && !ft_schr(luftbuffer, '\n'))
		luftbuffer = bruce(fd, luftbuffer, &read_bytes);
	puke = bucket(luftbuffer);
	if (ft_schr(luftbuffer, '\n') != NULL)
	{
		if (rest)
			free(rest);
		rest = ft_dup(ft_schr(luftbuffer, '\n') + 1);
	}
	else
	{
		rest = NULL;
	}
	free(luftbuffer);
	return (puke);
}

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("txt.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	while (str)
	{
		printf("out:%s", str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	//system("leaks GNL");
	return (0);
}
