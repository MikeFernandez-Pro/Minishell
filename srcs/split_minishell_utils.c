/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 11:52:35 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/08 09:17:38 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_strlen_str_quotes(char *s, char *str)
{
	int i;
	int j;

	i = 0;
	while (s && s[i])
	{
		j = 0;
		while (s[i] && str[j])
		{
			if (s[i] == str[j++] && ft_in_quotes(s, i) == 0)
				return (i);
		}
		i++;
	}
	return (i);
}

int			ft_strlen_str_quotes_backs(char *s, char *str)
{
	int i;
	int j;

	i = 0;
	while (s && s[i])
	{
		j = 0;
		while (s[i] && str[j])
		{
			if ((s[i] == str[j] && ft_in_quotes(s, i) == 0 && i == 0) ||
					(s[i] == str[j] && ft_in_quotes(s, i) == 0 && i > 0
					&& ft_isbacks(s, i - 1) == 0))
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

char		*clean_redir(char *str, char c)
{
	int i;
	int j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c && !ft_isbacks(str, i - 1))
		{
			if (str[i + 1] == c)
			{
				j = str[i + 2] == ' ' ? 3 : 2;
				str = ft_subfromstr_free(str, i,
						ft_strlen_str_quotes_backs(str + i + j, " ") + j);
			}
			else
			{
				j = str[i + 1] == ' ' ? 2 : 1;
				str = ft_subfromstr_free(str, i,
						ft_strlen_str_quotes_backs(str + i + j, " ") + j);
			}
			i = 0;
		}
	}
	return (str);
}

void		ft_change_args(t_cmds *cmd, t_gbl *gbl)
{
	t_args	*first_arg;
	char	*cpy;
	t_args	*args;

	cpy = NULL;
	args = cmd->args;
	if (cmd->str)
	{
		cpy = cmd->str;
		cmd->str = ft_envcpy(cpy, gbl);
	}
	first_arg = args;
	while (args)
	{
		cpy = args->str;
		args->str = ft_envcpy(cpy, gbl);
		args = args->next;
	}
	args = first_arg;
}
