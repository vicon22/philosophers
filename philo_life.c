/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 19:47:26 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/22 19:55:50 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_having_forks(t_filo_list *philos)
{
	pthread_mutex_lock(&philos->info->take_both_fork);
	pthread_mutex_lock(philos->right_forks);
	ft_printf("\x1b[33m" "%d %d has taken a fork" "\x1b[0m" "\n", philos);
	pthread_mutex_lock(philos->left_forks);
	ft_printf("\x1b[32m" "%d %d has taken a fork" "\x1b[0m" "\n", philos);
	pthread_mutex_unlock(&philos->info->take_both_fork);
}

void	ft_eating(t_filo_list *philos)
{
	pthread_mutex_lock(&philos->die_eat);
	ft_printf("%d %d is eating\n", philos);
	ft_sleep(philos->info->time_to_eat);
	pthread_mutex_unlock(philos->left_forks);
	pthread_mutex_unlock(philos->right_forks);
	philos->time_of_last_meal = ft_timestamp();
	philos->number_of_meal += 1;
	pthread_mutex_unlock(&philos->die_eat);
}

void	*pholi_life(void *vargs)
{
	t_filo_list		*philos;
	static int		j = 0;

	philos = (t_filo_list *)vargs;
	if (j++ == 0)
		philos->info->time = ft_timestamp();
	philos->time_of_last_meal = ft_timestamp();
	philos->number_of_meal = 0;
	while (philos->number_of_meal
		!= philos->info->num_times_each_philo_must_eat)
	{
		ft_having_forks(philos);
		ft_eating(philos);
		ft_printf("%d %d is sleeping\n", philos);
		ft_sleep(philos->info->time_to_sleep);
		ft_printf("%d %d is thinking\n", philos);
	}
	return (NULL);
}
