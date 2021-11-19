/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:43:45 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/19 16:36:53 by eveiled          ###   ########.fr       */
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

void	ft_observer(t_filo_list *philos)
{
	t_filo_list		*saver;
	int				time_to_die;

	saver = philos;
	time_to_die = saver->info->time_to_die;
	//printf("time_to_die:%d\n", time_to_die);
	while (1)
	{
		saver = philos;
		while (saver)
		{
			if (time_to_die < ft_timestamp() - saver->time_of_last_meal)
			{
				ft_some_philo_die(saver);
			}
			saver = saver->next;
		}
	}
}
