#include "../../Include/scop.h"

double			ft_atof(const char *str)
{
	int			i;
	int			x;
	double		sign;
	double		res;

	i = 0;
	x = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	sign = (str[i] == '-' ? -1 : 1);
	i += ((str[i] == '-' || str[i] == '+') ? 1 : 0);
	while (str[i] && IS_WHITESPACE(str[i]))
		i++;
	while (str[i] && str[i] != '.' && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	i += ((str[i] == '.') ? 1 : 0);
	while (str[i + x] && (str[i + x] >= '0' && str[i + x] <= '9'))
		res = res * 10 + (str[i + x++] - '0');
	while (x-- > 0)
		res /= 10;
	return (res * sign);
}

int		ft_ralloc(char **str, int size)
{
	char *res;

	if (!(res = ft_strdup(*str)))
		return (0);
	ft_memdel((void**)str);
	if (!(*str = ft_strnew(ft_strlen(res) + size)))
		return (0);
	*str = ft_strcpy(*str, res);
	ft_memdel((void **)&res);
	return (1);
}

int		count_words(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i && line[i])
	{
		while (IS_WHITESPACE(line[i]))
			i++;
		if (line[i])
		{
			j++;
			while (line[i] && !IS_WHITESPACE(line[i]))
				i++;
		}
	}
	return (j);
}

int max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int max_4(int a, int b, int c, int d)
{
	return (max(max(a, b), max(c, d)));
}