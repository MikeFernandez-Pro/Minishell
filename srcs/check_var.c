/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 22:59:44 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/06 10:03:29 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_str_alpha(char *str, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if ((!ft_isalpha(str[i]) || ft_isalnum(str[i])) && str[i] != '_')
			return (0);
	}
	return (1);
}

int		check_str_digitspace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] < 48 || str[i] > 57) && str[i] != 32)
			return (0);
	}
	return (1);
}
