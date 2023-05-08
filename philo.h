/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:00:39 by adnane            #+#    #+#             */
/*   Updated: 2023/05/08 13:59:09 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher_info
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*shared_mutex;
	int				id;
	long long		last_meal;
	int				ate;
	struct s_thread	*thread_info;
}	t_philosopher_info;

typedef struct s_thread
{
	int					num_philo;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	pthread_t			*philosophers;
	pthread_mutex_t		*forks;
	pthread_mutex_t		shared_print;
	long long			very_start;
	t_philosopher_info	*info;
}	t_thread;

void		*philosopher(void *arg);
long long	get_time(void);
long long	get_period(long long start_time);
void		print_message(long long very_start, int id,
				const char *message, pthread_mutex_t *shared_mutex);

#endif