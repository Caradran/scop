#include <OpenCL/opencl.h>
#include "../../libft/include/libft.h"
#include "../../Include/get_next_line.h"
#include <stdlib.h>

static char	*concat(char **src)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	i = 0;
	while (src[j])
	{
		i += ft_strlen(src[j]) + 1;
		j++;
	}
	dest = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (i < j)
	{
		dest = ft_strcat(dest, src[i]);
		dest = ft_strcat(dest, "\n");
		free(src[i]);
		i++;
	}
	free(src);
	return (dest);
}

char	*readshad(char *source, int *i)
{
	char	**kernel_source;
	int		fd;
	char	*line;
	int		j;

	j = 1;
	if ((fd = open(source, O_RDONLY)) > 0)
		while (get_next_line(fd, &line) == 1 && j++)
			free(line);
	else
		ft_putendl("Echec de lecture : 1");
	close(fd);
	if (!(kernel_source = ft_memalloc(sizeof(char *) * (j + 1))))
		return (NULL);
	*i = 0;
	if ((fd = open(source, O_RDONLY)) > 0)
		while (get_next_line(fd, &kernel_source[*i]) == 1)
			(*i)++;
	else
		ft_putendl("Echec de lecture : 2");
	ft_memdel((void**)&kernel_source[*i]);
	close(fd);
	free(line);
	line = concat(kernel_source);
	return (line);
}
