/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:28:47 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/22 19:43:32 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_death(t_manage *death, int i)
{
	pthread_mutex_unlock(&death[i].nbr_eat);
	pthread_mutex_lock(&death->global_back->philo_a_eat);
	death->global_back->value = 0;
	pthread_mutex_unlock(&death->global_back->philo_a_eat);
	printf("%llu %d %s\n", ft_get_time()
		- death->global_back->time, death->philo_place, "died");
}

static void	ft_finish_eat(t_manage *death)
{
	pthread_mutex_lock(&death->global_back->philo_a_eat);
	death->global_back->value = 0;
	pthread_mutex_unlock(&death->global_back->philo_a_eat);
}

int	ft_while_death(t_manage *death, int i)
{
	pthread_mutex_lock(&death[i].nbr_eat);
	if ((ft_get_time() >= death->global_back->tdeath + death[i].last_eat))
	{
		ft_death(death, i);
		return (0);
	}
	else if (death->global_back->each_time_eat
		&& death[i].nbr_of_eat >= death->global_back->each_time_eat)
	{
		death->global_back->c += death[i].nbr_of_eat;
	}
	pthread_mutex_unlock(&death[i].nbr_eat);
	return (1);
}

void	*ft_check_death(void *work, int value)
{
	t_manage	*death;
	int			i;

	death = (t_manage *)work;
	while (value)
	{
		i = -1;
		death->global_back->c = 0;
		while (++i < death->global_back->n_philo)
		{
			if (!(ft_while_death(death, i)))
				return (NULL);
			pthread_mutex_lock(&death->global_back->philo_a_eat);
			value = death->global_back->value;
			pthread_mutex_unlock(&death->global_back->philo_a_eat);
		}
		if (death->global_back->each_time_eat != -42
			&& death->global_back->c > death->global_back->multi)
		{
			ft_finish_eat(death);
			return (NULL);
		}
	}
	return (NULL);
}

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
