/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:23:37 by pbillett          #+#    #+#             */
/*   Updated: 2016/01/09 21:40:40 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int			ft_nbrlen(int n)
{
	int				i;

	i = 0;
	if (n == 0)
		i++;
	else if (n < 0)
		i++;
	else
	{
		while (n > 0)
		{
			i++;
			n /= 10;
		}
	}
	return (i);
}

char				*ft_itoa(int n)
{
	char			*str;
	unsigned int	len;
	long			tmp;

	tmp = (long)n;
	str = NULL;
	len = ft_nbrlen(tmp) + (n < 0);
	if (n < 0)
		tmp = (tmp * -1);
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = (tmp % 10) + '0';
		len--;
		tmp = tmp / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
