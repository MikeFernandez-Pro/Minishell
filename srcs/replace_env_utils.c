/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 13:44:51 by user42            #+#    #+#             */
/*   Updated: 2020/09/07 18:46:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_envlen(char *str, t_env *env, int *cpt)
{
	t_env	*env_cpy;
	int		i;

	env_cpy = env;
	i = ft_find_size_arg(str);
	i = (ft_isdigit(str[i]) == 1) ? i + 1 : i;
	while (env_cpy)
	{
		if (ft_strncmp(str, env_cpy->var, i) == 0
		&& ft_strncmp(env_cpy->var, str, ft_strlen(env_cpy->var) - 1) == 0)
		{
			*cpt = *cpt + ft_strlen(env_cpy->valeur);
			return (i);
		}
		env_cpy = env_cpy->next;
	}
	return (i);
}

void	ft_simpq_len(char *str, int *i, int *len)
{
	(*i)++;
	while (ft_isquote(str, *i) != 1 && str[*i])
	{
		(*len)++;
		(*i)++;
	}
}

void	ft_doubleq_len(char *str, t_env *env, int *i, int *len)
{
	(*i)++;
	while (ft_isquote(str, *i) != 2 && str[*i])
	{
		if (*i > 0 && str[*i] == BACKS && ft_isbacks(str, (*i) - 1) == 1)
			(*i)++;
		if (str[*i] == '$' && ft_isbacks(str, (*i) - 1) == 0)
			(*i) += ft_envlen(&str[(*i) + 1], env, len);
		else
			(*len)++;
		(*i)++;
	}
}

int		ft_envcpylen(char *str, t_env *env)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if ((i > 0 && str[i] == SIMPQ && ft_isbacks(str, (i) - 1) == 0)
				|| (i == 0 && str[i] == SIMPQ))
			ft_simpq_len(str, &i, &len);
		else if ((i > 0 && str[i] == DOUBQ && ft_isbacks(str, i - 1) == 0)
				|| (i == 0 && str[i] == DOUBQ))
			ft_doubleq_len(str, env, &i, &len);
		else if ((i == 0 && str[i] == '$') || (i > 0 && str[i] == '$'
					&& ft_isbacks(str, i - 1) == 0))
			i += ft_envlen(&str[i + 1], env, &len);
		else if (str[i] == BACKS && ft_isbacks(str, i) == 0)
			len++;
		else if (str[i] != BACKS)
			len++;
	}
	return (len);
}
