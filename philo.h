/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:00:39 by adnane            #+#    #+#             */
/*   Updated: 2023/05/08 15:56:48 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

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
	long				time_to_die;
	long				time_to_sleep;
	long				time_to_eat;
	pthread_t			*philosophers;
	pthread_mutex_t		*forks;
	pthread_mutex_t		shared_print;
	long long			very_start;
	t_philosopher_info	*info;
}	t_thread;

void		*philosopher(void *arg);
void		pick_up_forks(t_philosopher_info *info);
void		eat(t_philosopher_info *info);
void		put_down_forks(t_philosopher_info *info);
void		sleep_and_think(t_philosopher_info *info);
long long	get_period(long long start_time);
void		set_thread_params(t_thread *thread, char **argv);
void		create_philosopher(t_thread *thread, int i);
void		create_philosophers(t_thread *thread);
void		create_death_checker(t_thread *thread);
void		join_destroy_philosophers(t_thread *thread);
void		*death_checker(void *arg);
int			is_valid_int(long num);
void		print_message(long long very_start, int id,
				const char *message, pthread_mutex_t *shared_mutex);

#endif