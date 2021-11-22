/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 20:01:40 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/22 20:16:11 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_list	*ft_initialize(int argc, char **argv)
{
	t_list	*arg;

	arg = (t_list *)malloc(sizeof(t_list) * 1);
	if (NULL == arg)
		return (NULL);
	arg->number_philo = ft_atoi(argv[1]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->time_to_die = ft_atoi(argv[2]);
	if (argc == 6)
		arg->num_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		arg->num_times_each_philo_must_eat = -1;
	return (arg);
}

static void	logic(t_filo_list *current, t_list *arg, pthread_mutex_t **forks,
			int i)
{
	if (i == 1)
	{
		if (arg->number_philo > 1)
			current->left_forks = forks[i];
		else
			current->left_forks = forks[0];
		current->right_forks = forks[0];
	}
	else if (i == arg->number_philo)
	{
		current->left_forks = forks[0];
		current->right_forks = forks[i - 1];
	}
	else
	{
		current->left_forks = forks[i];
		current->right_forks = forks[i - 1];
	}
}

t_filo_list	*create_philos(t_list *arg, pthread_mutex_t	**forks)
{
	t_filo_list		*philos;
	t_filo_list		*current;
	int				i;

	i = 1;
	philos = NULL;
	while (i <= arg->number_philo)
	{
		current = ft_lstnew_filo(i, arg);
		logic(current, arg, forks, i);
		ft_lstadd_back(&philos, current);
		i++;
		pthread_mutex_init(&current->die_eat, NULL);
	}
	pthread_mutex_init(&philos->info->take_both_fork, NULL);
	pthread_mutex_init(&philos->info->print, NULL);
	return (philos);
}

pthread_mutex_t	**create_forks(int number_philo)
{
	pthread_mutex_t	**mutex_s;
	int				i;

	i = 0;
	mutex_s = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *)
			* number_philo);
	while (i < number_philo)
	{
		mutex_s[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(mutex_s[i], NULL);
		i++;
	}
	return (mutex_s);
}
