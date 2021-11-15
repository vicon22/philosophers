/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:04:43 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/15 21:18:11 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_some_philo_die(t_filo_list *philos)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("%d %d died\n", current_time.tv_usec - philos->info->time.tv_usec, philos->number_current_philo);
}

void	*pholi_life(void *vargs)
{
	t_filo_list		*philos;
	static int		j = 0;
	int				i = 0;
	struct timeval	current_time;

	philos = (t_filo_list *)vargs;
	gettimeofday(&current_time, NULL);
	if (j++ == 0)
		philos->info->time = current_time;
	philos->time_of_last_meal = current_time;
	i = 0;
	pthread_mutex_init(&philos->left_forks, NULL);
	pthread_mutex_init(&philos->right_forks, NULL);
	while (i++ < 5)
	{
		gettimeofday(&current_time, NULL);
		if (current_time.tv_usec - philos->time_of_last_meal.tv_usec > philos->info->time_to_die)
			ft_some_philo_die(philos);
		pthread_mutex_lock(&philos->left_forks);
		pthread_mutex_lock(&philos->right_forks);
		printf("%d %d is eating\n", current_time.tv_usec - philos->info->time.tv_usec, philos->number_current_philo);
		usleep(philos->info->time_to_eat);
		pthread_mutex_unlock(&philos->left_forks);
		pthread_mutex_unlock(&philos->right_forks);
		gettimeofday(&current_time, NULL);
		philos->time_of_last_meal = current_time;

		gettimeofday(&current_time, NULL);
		if (current_time.tv_usec - philos->time_of_last_meal.tv_usec > philos->info->time_to_die)
			ft_some_philo_die(philos);
		printf("%d %d is sleeping\n", current_time.tv_usec - philos->info->time.tv_usec, philos->number_current_philo);
		usleep(philos->info->time_to_sleep);

		gettimeofday(&current_time, NULL);
		if (current_time.tv_usec - philos->time_of_last_meal.tv_usec > philos->info->time_to_die)
			ft_some_philo_die(philos);
		printf("%d %d is thinking\n", current_time.tv_usec - philos->info->time.tv_usec, philos->number_current_philo);
	}
	return NULL;
}

t_list	*ft_initialize(int argc, char **argv)
{
	t_list	*arg;

	arg = (t_list *)malloc(sizeof(t_list *) * 1);
	if (NULL == arg)
		exit (1);
	arg->number_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->num_times_each_philo_must_eat = ft_atoi(argv[5]);
//	printf("number_philo:%d\n", arg->number_philo);
//	printf("time_to_die:%d\n", arg->time_to_die);
//	printf("time_to_eat:%d\n", arg->time_to_eat);
//	printf("time_to_sleep:%d\n", arg->time_to_sleep);
//	printf("num_times_each_philo_must_eat:%d\n", arg->num_times_each_philo_must_eat);
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
			current->left_forks = *forks[0];
			current->right_forks = *forks[arg->number_philo - 1];
		}
		else if (i == arg->number_philo)
		{
			current->left_forks = *forks[arg->number_philo - 1];
			current->right_forks = *forks[0];
		}
		else
		{
			current->left_forks = *forks[i - 1];
			current->right_forks = *forks[i - 2];
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

pthread_mutex_t	**create_forks(t_list *arg)
{
	pthread_mutex_t	**mutex_s;
	int				i;

	i = 0;
	mutex_s = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * arg->number_philo);
	while (i < arg->number_philo)
	{
		mutex_s[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
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
	struct timeval	current_time;
	struct timeval	current_time_2;
	int				i;

	if (ft_arg_check(argc) == 1)
		return (1);
	arg = ft_initialize(argc, argv);
	gettimeofday(&current_time_2, NULL);
	forks = create_forks(arg);
	philos = create_philos(arg, forks);
	saver = philos;
	for (i = 0; i < arg->number_philo; i++)
	{
		//printf("Before Thread\n");
		pthread_create(saver->filo, NULL, pholi_life, saver);
		saver = saver->next;
		usleep(50);
	}
	saver = philos;
	for (i = 0; i < arg->number_philo; i++)
	{
		pthread_join(*saver->filo, NULL);
		saver = saver->next;
		//printf("After Thread\n");
	}
	gettimeofday(&current_time, NULL);
	printf("micro seconds : %d\n", current_time.tv_usec - current_time_2.tv_usec);
	return (0);
}
