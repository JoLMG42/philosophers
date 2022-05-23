/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:03:50 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/22 19:33:58 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_check_eat(t_manage *manage)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	if (manage->global_back->each_time_eat != -42)
	{
		while (i < manage->global_back->n_philo)
		{
			if (manage->global_back->each_time_eat
				&& manage[i].nbr_of_eat >= manage->global_back->each_time_eat)
			{
				c += manage[i].nbr_of_eat;
			}
			i++;
		}
		if (c > manage->global_back->each_time_eat)
		{
			sem_wait(manage->write);
			exit(1);
		}
	}
}

void	ft_check_death(t_manage *manage, unsigned long long t, int i)
{
	unsigned long long	time_start;

	time_start = ft_get_time();
	while (time_start + t >= ft_get_time())
	{
		usleep(1000);
		if ((ft_get_time() >= (unsigned long long)manage->global_back->tdeath
				+ manage[i].last_eat))
		{
			sem_wait(manage->write);
			printf("%llu %d died\n", ft_get_time()
				- manage->global_back->time, i);
			exit (1);
		}
	}
}

void	ft_usleep(t_manage *manage, unsigned long long t)
{
	unsigned long long	time_start;

	(void)manage;
	time_start = ft_get_time();
	while (time_start + t >= ft_get_time())
		usleep(1000);
}
