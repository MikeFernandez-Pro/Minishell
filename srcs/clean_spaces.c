/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:42:27 by user42            #+#    #+#             */
/*   Updated: 2020/09/09 10:38:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_travel_spaces(char *str, int *i)
{
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	(*i)--;
}

int		ft_start(char *str)
{
	int	i;

	i = 0;
	while (((i > 0 && ft_isbacks(str, i - 1) == 0 && str[i] == ' ')
				|| (i == 0 && str[i] == ' ')) && str[i])
		i++;
	return (i);
}

int		ft_end(char *str)
{
	int k;

	k = ft_strlen(str) - 1;
	while (k > 0 && ft_isbacks(str, k - 1) == 0 && str[k] == ' ')
		k--;
	return (k);
}

char	*ft_clean_spaces(char *str)
{
	int		i;
	int		j;
	char	*cpy;

	if (!(cpy = ft_calloc(sizeof(char), (ft_strlen(str) + 1))))
		return (0);
	i = ft_start(str);
	j = 0;
	while (i <= ft_end(str))
	{
		if ((i > 0 && str[i] == ' ' && ft_isbacks(str, i - 1) == 0))
			ft_travel_spaces(str, &i);
		else if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, i - 1) == 0)
				|| (i == 0 && str[i] == SIMPQ))
			ft_cpy_in_squotes(str, cpy, &i, &j);
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
				|| (i == 0 && str[i] == DOUBQ))
			ft_cpy_in_dbquotes(str, cpy, &i, &j);
		cpy[j++] = str[i++];
	}
	cpy[j] = '\0';
	return (cpy);
}
