/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:04:43 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/16 14:47:06 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_some_philo_die(t_filo_list *philos, struct timeval current_time)
{
	//struct timeval	current_time;

	//gettimeofday(&current_time, NULL);
	if (philos->info->some_die != 1)
		printf("%d %d died\n", current_time.tv_usec - philos->info->time.tv_usec, philos->number_current_philo);
	philos->info->some_die = 1;
	pthread_mutex_unlock(philos->left_forks);
	pthread_mutex_unlock(philos->right_forks);
}

void	*pholi_life(void *vargs)
{
	t_filo_list		*philos;
	static int		j = 0;
	int				i = 0;
	struct timeval	current_time;
	//pthread_mutex_t	take_both_fork;

	philos = (t_filo_list *)vargs;
	gettimeofday(&current_time, NULL);
	if (j++ == 0)
	{
		pthread_mutex_init(&philos->info->take_both_fork, NULL);
		philos->info->time = current_time;
	}
	philos->time_of_last_meal = current_time;
	i = 0;
	philos->number_of_meal = 0;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		if (philos->info->some_die != 1 && current_time.tv_usec - philos->time_of_last_meal.tv_usec > philos->info->time_to_die)
		{
			printf("1:%d\n", philos->number_current_philo);
			ft_some_philo_die(philos, current_time);
			return (NULL);
		}
		if (philos->info->some_die == 1)
		{
			printf("-1:%d\n", philos->number_current_philo);
			return (NULL);
		}
		pthread_mutex_lock(&philos->info->take_both_fork);
		//printf("take_both_fork - %p\n", &philos->info->take_both_fork);
		//printf("%d - take_both_fork:%d\n", philos->number_current_philo, pthread_mutex_lock(&philos->info->take_both_fork));
		//printf("%d - left:%d\n", philos->number_current_philo, pthread_mutex_lock(philos->left_forks));
		//printf("%d - right:%d\n", philos->number_current_philo, pthread_mutex_lock(philos->right_forks));
		pthread_mutex_lock(philos->left_forks);
		pthread_mutex_lock(philos->right_forks);
		gettimeofday(&current_time, NULL);
		if (philos->info->some_die != 1)
			printf("%d %d has taken a fork\n", current_time.tv_usec - philos->info->time.tv_usec, philos->number_current_philo);
//		pthread_mutex_lock(philos->left_forks);
//		pthread_mutex_lock(philos->right_forks);
		pthread_mutex_unlock(&philos->info->take_both_fork);
		gettimeofday(&current_time, NULL);
		pthread_mutex_unlock(philos->left_forks);
		pthread_mutex_unlock(philos->right_forks);
		if (philos->info->some_die == 1)
		{
			printf("-2:%d\n", philos->number_current_philo);
			return (NULL);
		}
		if (philos->info->some_die != 1)
		{
			printf("%d %d is eating\n", current_time.tv_usec - philos->info->time.tv_usec, philos->number_current_philo);
			usleep(philos->info->time_to_eat);
		}
		gettimeofday(&current_time, NULL);
		philos->time_of_last_meal = current_time;
		philos->number_of_meal +=1;
		printf("philos->info->num_times_each_philo_must_eat:%d\n", philos->info->num_times_each_philo_must_eat);
		printf("%d philos->number_of_meal:%d\n", philos->number_current_philo, philos->number_of_meal);
		if (philos->info->num_times_each_philo_must_eat > 0 && philos->number_of_meal >= philos->info->num_times_each_philo_must_eat)
		{
			printf("---\n");
			break ;
		}

		gettimeofday(&current_time, NULL);
		if (philos->info->some_die != 1 && current_time.tv_usec - philos->time_of_last_meal.tv_usec > philos->info->time_to_die)
		{
			printf("3:%d\n", philos->number_current_philo);
			ft_some_philo_die(philos, current_time);
			return (NULL);
		}
		if (philos->info->some_die == 1)
		{
			printf("-3:%d\n", philos->number_current_philo);
			return (NULL);
		}
		if (philos->info->some_die != 1)
		{
			printf("%d %d is sleeping\n", current_time.tv_usec - philos->info->time.tv_usec, philos->number_current_philo);
			usleep(philos->info->time_to_sleep);
		}

		gettimeofday(&current_time, NULL);
		if (philos->info->some_die != 1 && current_time.tv_usec - philos->time_of_last_meal.tv_usec > philos->info->time_to_die)
		{
			printf("4:%d\n", philos->number_current_philo);
			ft_some_philo_die(philos, current_time);
			return (NULL);
		}
		if (philos->info->some_die == 1)
		{
			printf("-4:%d\n", philos->number_current_philo);
			return (NULL);
		}
		if (philos->info->some_die != 1)
			printf("%d %d is thinking\n", current_time.tv_usec - philos->info->time.tv_usec, philos->number_current_philo);
	}
	return NULL;
}

t_list	*ft_initialize(int argc, char **argv)
{
	t_list	*arg;

	arg = (t_list *)malloc(sizeof(t_list *) * 1);
	if (NULL == arg)
		exit (1); //// удалить нахер
	arg->number_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->num_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		arg->num_times_each_philo_must_eat = -1;
//	printf("number_philo:%d\n", arg->number_philo);
//	printf("time_to_die:%d\n", arg->time_to_die);
//	printf("time_to_eat:%d\n", arg->time_to_eat);
//	printf("time_to_sleep:%d\n", arg->time_to_sleep);
	printf("                             num_times_each_philo_must_eat:%d\n", arg->num_times_each_philo_must_eat);
	printf("                             number_philo:%d\n", arg->number_philo);
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
	struct timeval	current_time;
	struct timeval	current_time_2;
	int				i;

	if (ft_arg_check(argc) == 1)
		return (1);
	arg = ft_initialize(argc, argv);
	gettimeofday(&current_time_2, NULL);
	//printf("2                             num_times_each_philo_must_eat:%d\n", arg->num_times_each_philo_must_eat);
	forks = create_forks(arg->number_philo);
	printf("2                             num_times_each_philo_must_eat:%d\n", arg->num_times_each_philo_must_eat);
	philos = create_philos(arg, forks);
	saver = philos;
	for (i = 0; i < arg->number_philo; i++)
	{
		//printf("Before Thread\n");
		pthread_create(saver->filo, NULL, pholi_life, saver);
		saver = saver->next;
		//usleep(50);
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
