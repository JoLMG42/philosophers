/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:32:37 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/02 19:35:02 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct	s_manage
{
	unsigned long long time;
	unsigned long long last_eat;
	int	right_fork;
	int	left_fork;
	int	eating;
	int	philo_place;
	int	nbr_of_eat;
	struct s_global	*global_back;
	pthread_t	philo_thread;
	pthread_mutex_t	eat;
}	t_manage;


typedef struct	s_global
{
	unsigned long long time;
	int	n_philo;
	int	tdeath;
	int	teat;
	int	tsleep;
	int	each_time_eat;
	t_manage	*work;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
}	t_global;

int	ft_atoi(const char *str);
char	*ft_itoa(int n);


#endif
