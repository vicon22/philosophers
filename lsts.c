/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:45:37 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/15 17:54:08 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_filo_list	*ftLstnewFilo(int number_current_philo, t_list *info)
{
	t_filo_list	*new;

	new = (t_filo_list *)malloc(sizeof(t_filo_list));
	if (NULL == new)
		return (NULL);
	new->number_current_philo = number_current_philo;
	new->filo = (pthread_t *)malloc(sizeof(pthread_t));
//	printf("=====\n");
//	printf("new->number_philo:%d\n", new->number_current_philo);
//	printf("new->filo:%p\n", new->filo);
//	printf("=====\n");
	if (NULL == new->filo)
	{
		free(new);
		return (NULL);
	}
	new->info = info;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_filo_list **lst, t_filo_list *new)
{
	t_filo_list	*saver;

	saver = *lst;
	if (saver)
	{
		while ((saver)->next)
			saver = (saver)->next;
		(saver)->next = new;
	}
	else
	{
		*lst = new;
	}
}
