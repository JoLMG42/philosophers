/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:55:02 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/18 17:14:44 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

t_manage	*ft_init_struct_2(t_global *global)
{
	t_manage	*manage;
	int			i;

	i = 0;
	manage = malloc(sizeof(t_manage) * (global->n_philo + 1));
	while (i < global->n_philo)
	{
		manage[i].philo_place = i + 1;
		manage[i].eating = 0;
		manage[i].nbr_of_eat = 0;
		manage[i].global_back = global;
		i++;
	}
	manage->nb_fork = global->n_philo;
	return (manage);
}

void	ft_init_struct(t_global *global, char **av, int ac)
{
	global->n_philo = ft_atoi(av[1]);
	global->tdeath = ft_atoi(av[2]);
	global->teat = ft_atoi(av[3]);
	global->tsleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		global->each_time_eat = ft_atoi(av[5]);
	}
	else
		global->each_time_eat = -42;
	global->work = ft_init_struct_2(global);
}

void	ft_init_thread(t_global *global)
{
	int	i;
	int	value;

	value = 0;
	global->time = ft_get_time();
	i = 1;
	while (i <= global->n_philo)
	{
		global->work[i].last_eat = ft_get_time();
		global->work[i].frk = fork();
		if (global->work[i].frk == 0)
			ft_routine(global->work, i);
		i++;
	}
	waitpid(-1, &value, 0);
	if (WEXITSTATUS(value) == 1)
	{
		i = 1;
		while (i <= global->n_philo)
		{
			kill(global->work[i].frk, 2);
			i++;
		}
	}
}
