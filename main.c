/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:04:43 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/20 14:24:40 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_some_philo_die(t_filo_list *philos)
{
	//struct timeval	current_time;

	//gettimeofday(&current_time, NULL);
	if (philos->info->some_die != 1)
	{
		pthread_mutex_lock(&philos->info->print);
		usleep(1000);
		printf("\x1b[31m" "%d %d died" "\x1b[0m" "\n", ft_timestamp() - philos->info->time, philos->number_current_philo);
		//pthread_mutex_unlock(&philos->info->print);
	}
	philos->info->some_die = 1;
	pthread_mutex_unlock(philos->left_forks);
	pthread_mutex_unlock(philos->right_forks);
}

void	*pholi_life(void *vargs)
{
	t_filo_list		*philos;
	static int		j = 0;

	philos = (t_filo_list *)vargs;
	//pthread_detach(*philos->filo);
	if (j++ == 0)
	{
		pthread_mutex_init(&philos->info->take_both_fork, NULL);
		pthread_mutex_init(&philos->info->print, NULL);
		philos->info->time = ft_timestamp();
	}
	philos->time_of_last_meal = ft_timestamp();
	philos->number_of_meal = 0;
	while (philos->number_of_meal != philos->info->num_times_each_philo_must_eat)
	{
		pthread_mutex_lock(&philos->info->take_both_fork);

		pthread_mutex_lock(philos->left_forks);
		pthread_mutex_lock(&philos->info->print);
		printf("\x1b[33m" "%d %d has taken a fork" "\x1b[0m" "\n", ft_timestamp() - philos->info->time, philos->number_current_philo);
		pthread_mutex_unlock(&philos->info->print);

		pthread_mutex_lock(philos->right_forks);
		pthread_mutex_lock(&philos->info->print);
		printf("\x1b[32m" "%d %d has taken a fork" "\x1b[0m" "\n", ft_timestamp() - philos->info->time, philos->number_current_philo);
		pthread_mutex_unlock(&philos->info->print);

		pthread_mutex_unlock(&philos->info->take_both_fork);

		pthread_mutex_lock(&philos->info->print);
		philos->time_of_last_meal = ft_timestamp();
		printf("%d %d is eating\n", ft_timestamp() - philos->info->time, philos->number_current_philo);
		pthread_mutex_unlock(&philos->info->print);

		usleep(philos->info->time_to_eat);
		pthread_mutex_unlock(philos->left_forks);
		pthread_mutex_unlock(philos->right_forks);
		philos->time_of_last_meal = ft_timestamp();
		philos->number_of_meal += 1;
		//printf("philos->info->num_times_each_philo_must_eat:%d\n", philos->info->num_times_each_philo_must_eat);
		//printf("%d philos->number_of_meal:%d\n", philos->number_current_philo, philos->number_of_meal);
//		if (philos->info->num_times_each_philo_must_eat > 0 && philos->number_of_meal >= philos->info->num_times_each_philo_must_eat)
//		{
//			printf("---\n");
//			break ;
//		}

		pthread_mutex_lock(&philos->info->print);
		printf("%d %d is sleeping\n", ft_timestamp() - philos->info->time, philos->number_current_philo);
		pthread_mutex_unlock(&philos->info->print);

		usleep(philos->info->time_to_sleep);

		pthread_mutex_lock(&philos->info->print);
		printf("%d %d is thinking\n", ft_timestamp() - philos->info->time, philos->number_current_philo);
		pthread_mutex_unlock(&philos->info->print);
	}
	return NULL;
}

t_list	*ft_initialize(int argc, char **argv)
{
	t_list	*arg;

	arg = (t_list *)malloc(sizeof(t_list) * 1);
	if (NULL == arg)
		return (NULL);
	arg->number_philo = ft_atoi(argv[1]);
	//arg->time_to_die = ft_atoi(argv[2]) * 1000;
	arg->time_to_eat = ft_atoi(argv[3]) * 1000;
	arg->time_to_sleep = ft_atoi(argv[4]) * 1000;
	arg->time_to_die = ft_atoi(argv[2]);
//	arg->time_to_eat = ft_atoi(argv[3]);
//	arg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->num_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		arg->num_times_each_philo_must_eat = -1;
	return (arg);
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
		current = ftLstnewFilo(i, arg);
		if (i == 1)
		{
			current->left_forks = forks[0];
			current->right_forks = forks[arg->number_philo - 1];
		}
		else if (i == arg->number_philo)
		{
			current->left_forks = forks[arg->number_philo - 1];
			current->right_forks = forks[0];
		}
		else
		{
			current->left_forks = forks[i - 1];
			current->right_forks = forks[i - 2];
		}
		ft_lstadd_back(&philos, current);
		i++;
	}
	return (philos);
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

pthread_mutex_t	**create_forks(int number_philo)
{
	pthread_mutex_t	**mutex_s;
	int				i;

	i = 0;
	mutex_s = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * number_philo);
	while (i < number_philo)
	{
		mutex_s[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		//printf("mutex_s[%d]:%p\n", i, mutex_s[i]);
		pthread_mutex_init(mutex_s[i], NULL);
		i++;
	}
	return (mutex_s);
}

int	main(int argc, char **argv)
{
	t_list			*arg;
	t_filo_list		*philos;
	t_filo_list		*saver;
	pthread_mutex_t	**forks;
	int				i;

	if (ft_arg_check(argc) == 1)
		return (1);
	arg = ft_initialize(argc, argv);
	if (NULL == arg)
		return (1);
	forks = create_forks(arg->number_philo);
	philos = create_philos(arg, forks);
	saver = philos;
	i = 0;
	while (i < arg->number_philo)
	{
		//printf("Before Thread\n");
		pthread_create(saver->filo, NULL, pholi_life, saver);
		saver = saver->next;
		usleep(50);
		i++;
	}
	//printf("---\n");
	saver = philos;
	i = 0;
	while (1)
	{
		if (ft_observer(philos) == 1)
		{
			ft_destroy(philos);
			return (0);
		}
	}
	while (i < arg->number_philo)
	{
		pthread_join(*saver->filo, NULL);
		saver = saver->next;
		//printf("After Thread\n");
		i++;
	}
	return (0);
}
