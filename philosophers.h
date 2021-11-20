/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:13:20 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/20 14:19:48 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <time.h>

typedef struct s_list
{
	int	number_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_times_each_philo_must_eat;
	int	time;
	int				some_die;
	pthread_mutex_t	take_both_fork;
	pthread_mutex_t	print;
}	t_list;

typedef struct f_list
{
	int				number_current_philo;
	pthread_mutex_t	*left_forks;
	pthread_mutex_t	*right_forks;
	pthread_t		*filo;
	t_list			*info;
	struct f_list	*next;
	int				time_of_last_meal;
	int				number_of_meal;
}	t_filo_list;

void	*pholi_life(void *vargp);
t_filo_list	*ftLstnewFilo(int number_current_philo, t_list *info);
void		ft_lstadd_back(t_filo_list **lst, t_filo_list *new);
int	ft_timestamp(void);
int	ft_observer(t_filo_list *philos);
void	ft_some_philo_die(t_filo_list *philos);
void	ft_destroy(t_filo_list	*philos);
void	ft_sleep(int milliseconds);

int	ft_atoi(const char *str);
#endif
