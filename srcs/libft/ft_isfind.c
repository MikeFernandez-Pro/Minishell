/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfind.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:00:24 by cbertola          #+#    #+#             */
/*   Updated: 2020/07/23 17:13:52 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isfind(char *str, char stop)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == stop)
			return (i);
		i++;
	}
	return (-1);
}
