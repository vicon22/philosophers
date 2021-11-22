/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:43:45 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/22 19:57:39 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_timestamp(void)
{
	int				milliseconds;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	milliseconds = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return ((int)milliseconds);
}

int	ft_observer(t_filo_list *philos)
{
	t_filo_list		*saver;
	int				time_to_die;
	int				n_t_e_p_m_e;

	saver = philos;
	time_to_die = saver->info->time_to_die;
	n_t_e_p_m_e = philos->info->num_times_each_philo_must_eat;
	while (saver)
	{
		pthread_mutex_lock(&philos->die_eat);
		if (time_to_die < ft_timestamp() - saver->time_of_last_meal
			&& philos->number_of_meal != n_t_e_p_m_e)
		{
			ft_some_philo_die(saver);
			return (1);
		}
		if (philos->number_of_meal
			== philos->info->num_times_each_philo_must_eat)
		{
			return (2);
		}
		pthread_mutex_unlock(&philos->die_eat);
		saver = saver->next;
	}
	return (0);
}

void	ft_sleep(int milliseconds)
{
	int	start_time;

	start_time = ft_timestamp();
	while (milliseconds > ft_timestamp() - start_time)
	{
		usleep(50);
	}
}

void	ft_printf(char *str, t_filo_list *philos)
{
	pthread_mutex_lock(&philos->info->print);
	printf(str, ft_timestamp() - philos->info->time,
		philos->number_current_philo);
	pthread_mutex_unlock(&philos->info->print);
}

int	ft_arg_check(int argc)
{
	if (argc > 6 || argc < 5)
	{
		write(1, "Invalid arguments\n", 18);
		return (1);
	}
	return (0);
}
