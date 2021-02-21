/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:21:20 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/14 13:50:48 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_exit(t_cmds *cmd, t_gbl *gbl)
{
	unsigned long long	ret;
	int					i;

	i = 0;
	if (cmd->args == NULL)
		free_exit_back_int(gbl->semi, gbl, NULL, 0);
	if (cmd->args->str)
	{
		if (cmd->args->str[i] == '+' || cmd->args->str[i] == '-')
			i++;
		ret = ft_atoi_long(cmd->args->str + i);
		if (!(ft_strisdigit(cmd->args->str + i)) || (ret > MAXLONG &&
		ft_strcmp(cmd->args->str, "-9223372036854775808") != 0))
			free_exit_back_int(gbl->semi, gbl, ARG_NUM, 2);
		else if (cmd->nb_args > 1)
			exit_back2(gbl, ARGUMENTS);
		else if (cmd->args->str[0] == '-')
			free_exit_back_int(gbl->semi, gbl, NULL, (ret % 256 * -1));
		else
			free_exit_back_int(gbl->semi, gbl, NULL, (ret % 256));
	}
	return (1);
}
