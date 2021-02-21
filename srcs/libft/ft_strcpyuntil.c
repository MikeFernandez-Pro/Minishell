/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpyuntil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:12:15 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/03 09:41:29 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcpyuntil(const char *src, char *n)
{
	char	*dst;
	int		i;
	int		nb;

	i = -1;
	nb = ft_strlen_str(src, n) + 1;
	if (!(dst = ft_calloc(sizeof(char), nb + 1)))
		return (NULL);
	while (nb-- && src[++i])
		dst[i] = src[i];
	dst[++i] = 0;
	return (dst);
}
