/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:23:09 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/21 15:34:05 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	len_until_sc(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	helper(char **tmp, char **result, char **tmp2, t_game *game)
{
	free(*tmp);
	*tmp = NULL;
	concat_string(result, tmp2, " ", game);
}

char	*norm_line(t_game *game, char *str)
{
	int		i;
	char	*result;
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		skip_spaces(str, &i);
		tmp = ft_substr(str, i, len_until_sc(str + i, ' '));
		if (!tmp)
			return (free(result), NULL);
		concat_string(&result, &tmp2, tmp, game);
		if (is_dir(game, tmp) || is_fc(game, tmp))
			helper(&tmp, &result, &tmp2, game);
		i += len_until_sc(str + i, ' ');
		skip_spaces(str, &i);
		if (tmp)
			free(tmp);
	}
	return (result);
}

void	concat_string(char **result, char **tmp2, char *tmp, t_game *game)
{
	*tmp2 = ft_strdup(*result);
	free(*result);
	if (!*tmp2)
	{
		if (ft_strcmp(tmp, " "))
			free(tmp);
		ft_error("Malloc fail!", game);
	}
	*result = ft_strjoin(*tmp2, tmp);
	free(*tmp2);
	if (!*result)
	{
		if (ft_strcmp(tmp, " "))
			free(tmp);
		ft_error("Malloc fail!", game);
	}
}

//delete empty lines
void	norm_map(t_game *game)
{
	int		i;
	int		j;
	char	**new_map;

	i = 0;
	j = 0;
	new_map = malloc(sizeof(char *) * (game->rows + 1));
	if (!new_map)
		ft_error("Norm map failed!", game);
	while (game->map[i])
	{
		if (!is_empty(game->map[i]))
		{
			new_map[j] = ft_strdup(game->map[i]);
			if (!new_map[j])
				free_norm_map(game, new_map);
			j++;
		}
		i++;
	}
	new_map[j] = NULL;
	free_map(game->map);
	game->map = new_map;
	game->rows = j;
}
