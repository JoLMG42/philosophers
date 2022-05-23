/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:16:33 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/05 16:10:22 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*cpys1;
	unsigned char	*cpys2;

	cpys1 = (unsigned char *)s1;
	cpys2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n && *cpys1 && *cpys2 && *cpys1 == *cpys2)
	{
		cpys1++;
		cpys2++;
		i++;
	}
	if (i < n)
		return (*cpys1 - *cpys2);
	return (0);
}
