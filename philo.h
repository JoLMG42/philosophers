/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:41:39 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/01 19:50:51 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
#include <sys/time.h>

typedef struct s_work
{
	unsigned long long time2;
	int	right_fork;
	int	left_fork;
	unsigned long long last_eat;
	int	nbr_of_eat;
	int	eating;
	struct s_global	*globalback;
	pthread_mutex_t	eat;
}	t_work;

typedef struct s_global
{
	unsigned long long time;
	int	philo;
	int	tdeath;
	int	teat;
	int	tsleep;
	int	each_time_eat;
	t_work	*philo_work;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
}	t_global;

int	ft_atoi(const char *str);
char	*ft_itoa(int n);


#endif
