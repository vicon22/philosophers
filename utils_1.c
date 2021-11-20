/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:43:45 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/20 17:55:40 by eveiled          ###   ########.fr       */
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
	static	int		j = 0;

	saver = philos;
	time_to_die = saver->info->time_to_die;
	//printf("time_to_die:%d\n", time_to_die);
	n_t_e_p_m_e = philos->info->num_times_each_philo_must_eat;
	while (saver)
	{
		if (time_to_die < ft_timestamp() - saver->time_of_last_meal && philos->number_of_meal != n_t_e_p_m_e)
		{
//			printf("---\n");
//			printf("saver->info->time_to_die:%d\n", saver->info->time_to_die);
//			printf("saver->time_of_last_meal:%d\n", ft_timestamp() - saver->time_of_last_meal);
//			printf("saver->number_current_philo:%d\n", saver->number_current_philo);
//			pthread_mutex_lock(&philos->info->print);
//			pthread_mutex_unlock(&philos->info->print);
			ft_some_philo_die(saver);
			return (1);
		}
		if (philos->number_of_meal == philos->info->num_times_each_philo_must_eat)
		{
			//printf("===\n");
			j++;
			return (1);
		}
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
