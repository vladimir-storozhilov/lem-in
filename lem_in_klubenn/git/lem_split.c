#include "lem_in.h"

static int 	calc_spaces(char *line, char c)
{
	int i;

	i = 0;
	while (*line)
	{
		if (*line == c)
			i++;
		line++;
	}
	return (i);
}

static int 	word_len(char *line, char c)
{
	int i;

	i = 0;
	while (line[i] && line[i] != c)
		i++;
	return (i);
}

char	**split(char *line, char c)
{
	int i;
	int j;
	int k;
	char **arr;

	i = 0;
	if (!line || !*line || !c)
		return (NULL);
	j = calc_spaces(line, c);
	if (!(arr = (char **)malloc(sizeof(char *) * (j + 2))))
		return (NULL);
	while (i < j + 1)
	{
		k = word_len(line, c);
		if (!(arr[i] = (char *)malloc(sizeof(char) * (k + 1))))
			return (NULL);
		arr[i] = ft_strncpy(arr[i], line, k);
		arr[i][k] = '\0';
		i++;
		line += k + 1;
	}
	arr[i] = NULL;
	return (arr);
}