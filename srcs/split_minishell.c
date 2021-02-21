/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 11:52:35 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/14 11:11:19 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				split_semi(t_gbl *gbl)
{
	int		i;
	char	*str2;
	char	*str3;

	i = 0;
	if (!gbl->line)
		return (0);
	str2 = ft_clean_spaces(gbl->line);
	ft_verif_commands(str2, gbl);
	while (str2[i])
	{
		if (str2[i] == ';' || (str2[i] == ' ' && str2[i + 1] == ';'))
		{
			free_exit2(gbl, ERROR_SYNTAX);
			return (0);
		}
		str3 = ft_substr(str2 + i, 0,
		ft_strlen_str_quotes_backs(str2 + i, ";"));
		lstadd_back_semi(gbl, str3);
		i += ft_strlen_str_quotes_backs(str2 + i, ";");
		if (str2[i] == ';')
			i++;
	}
	free(str2);
	return (1);
}

t_pipes			*split_pipes(t_gbl *gbl, t_semi *semi)
{
	t_pipes		*pipes;
	char		*str2;
	char		*str;

	str = semi->str;
	if (!str)
		return (NULL);
	pipes = NULL;
	while (*str)
	{
		str2 = ft_substr(str, 0, ft_strlen_str_quotes_backs(str, "|"));
		lstadd_back_pipes(gbl, &pipes, str2);
		str += ft_strlen_str_quotes_backs(str, "|");
		if (*str == '|')
			str++;
		free(str2);
	}
	return (pipes);
}

t_args			*split_args(char *str, t_env *env)
{
	t_args		*args;
	char		*str2;

	if (!str || *str == '\0')
		return (NULL);
	args = NULL;
	while (*str)
	{
		str2 = ft_substr(str, 0, ft_strlen_str_quotes_backs(str, " "));
		lstadd_back_args(&args, str2, env);
		str += ft_strlen_str_quotes_backs(str, " ");
		if (*str == ' ')
			str++;
		free(str2);
	}
	return (args);
}

void			cmds_args(t_cmds *cmd, char *str, t_env *env)
{
	while (*str == ' ')
		str++;
	cmd->str = ft_substr(str, 0, ft_strlen_str_quotes_backs(str, " "));
	str += ft_strlen_str_quotes_backs(str, " ");
	if (*str == ' ')
		str++;
	cmd->args = split_args(str, env);
}
