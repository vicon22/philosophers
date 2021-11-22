/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:04:43 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/22 20:02:50 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_some_philo_die(t_filo_list *philos)
{
	if (philos->info->some_die != 1)
	{
		pthread_mutex_lock(&philos->info->print);
		printf("\x1b[31m" "%d %d died" "\x1b[0m" "\n",
			ft_timestamp() - philos->info->time, philos->number_current_philo);
	}
	philos->info->some_die = 1;
}

void	ft_start_algoritm(t_filo_list *philos)
{
	int				i;
	t_filo_list		*saver;
	int				number_philo;

	i = 0;
	saver = philos;
	number_philo = philos->info->number_philo;
	while (i < number_philo)
	{
		if (i % 2 == 0)
			pthread_create(saver->filo, NULL, pholi_life, saver);
		usleep(50);
		saver = saver->next;
		i++;
	}
	i = 0;
	saver = philos;
	while (i < number_philo)
	{
		if (i % 2 == 1)
			pthread_create(saver->filo, NULL, pholi_life, saver);
		usleep(50);
		saver = saver->next;
		i++;
	}
}

void	ft_check_forks(t_filo_list *philos)
{
	while (philos)
	{
		printf("number:%d\n", philos->number_current_philo);
		printf("left:%p\n", philos->left_forks);
		printf("right:%p\n", philos->right_forks);
		philos = philos->next;
	}
}

int	main(int argc, char **argv)
{
	t_list			*arg;
	t_filo_list		*philos;
	pthread_mutex_t	**forks;
	int				i;

	if (ft_arg_check(argc) == 1)
		return (1);
	arg = ft_initialize(argc, argv);
	if (NULL == arg)
		return (1);
	forks = create_forks(arg->number_philo);
	philos = create_philos(arg, forks);
	ft_start_algoritm(philos);
	while (1)
	{
		i = ft_observer(philos);
		if (i == 1)
			return (ft_destroy(philos));
		if (i == 2)
			return (ft_join(philos));
	}
	return (0);
}
