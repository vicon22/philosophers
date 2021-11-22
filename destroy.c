/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:07:04 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/22 19:22:17 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_destroy(t_filo_list	*philos)
{
	t_list			*info;

	info = philos->info;
	while (philos)
	{
		pthread_detach(*philos->filo);
		pthread_mutex_destroy(philos->left_forks);
		pthread_mutex_destroy(philos->right_forks);
		pthread_mutex_destroy(&philos->die_eat);
		philos = philos->next;
	}
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->take_both_fork);
	return (0);
}

int	ft_join(t_filo_list	*philos)
{
	t_list			*info;

	info = philos->info;
	while (philos)
	{
		pthread_join(*philos->filo, NULL);
		pthread_mutex_destroy(philos->left_forks);
		pthread_mutex_destroy(philos->right_forks);
		pthread_mutex_destroy(&philos->die_eat);
		philos = philos->next;
	}
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->take_both_fork);
	return (0);
}
