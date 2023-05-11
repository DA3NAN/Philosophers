/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:30:08 by adnane            #+#    #+#             */
/*   Updated: 2023/05/11 17:01:02 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_period(long long start_time)
{
	struct timeval	tmp;
	long long		curr_time;

	gettimeofday(&tmp, NULL);
	curr_time = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	return (curr_time - start_time);
}

void	print_message(long long very_start, int id,
			const char *message, pthread_mutex_t *shared_mutex)
{
	pthread_mutex_lock(shared_mutex);
	printf("|%lld| Philosopher %d %s\n", get_period(very_start), id, message);
	pthread_mutex_unlock(shared_mutex);
}
