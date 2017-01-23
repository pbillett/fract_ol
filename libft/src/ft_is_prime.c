/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 19:19:04 by pbillett          #+#    #+#             */
/*   Updated: 2016/10/18 19:22:55 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_is_prime(int n)
{
	int		i;

	i = 2;
	while (i < n)
	{
		if ((n % i) == 0)
			return (0);
		i++;
	}
	return (1);
}