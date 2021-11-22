/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 20:33:05 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/22 23:33:04 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_arg_check(int argc)
{
	if (argc > 6 || argc < 5)
	{
		write(1, "Invalid arguments\n", 18);
		return (1);
	}
	return (0);
}

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

int	main(int argc, char **argv)
{
	t_list			*arg;
	int				id;
	int				i;
	sem_t			*sem;

	if (ft_arg_check(argc) == 1)
		return (1);
	arg = ft_initialize(argc, argv);
	if (NULL == arg)
		return (1);
	id = 1;
	i = 0;
	sem = sem_open(NULL, 1);
	while (id != 0 && i++ < arg->number_philo)
	{
		id = fork();
	}
	if (id != 0)
	{
		sleep(5);
		printf("main\n");
	}
	if (id == 0)
	{
		sem_wait(sem);
		sleep(1);
		printf("philo: %d\n", i);
		sem_post(sem);
		return (0);
	}
	return (0);
}
