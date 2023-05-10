/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:30:08 by adnane            #+#    #+#             */
/*   Updated: 2023/05/10 16:48:57 by adnane           ###   ########.fr       */
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

int	is_valid_int(char *str)
{
	int			i;
	long long	num;

	i = 0;
	while (str[i])
	{
		if (i > 10)
			return (0);
		i++;
	}
	num = atoi(str);
	if (num < 0 || num > INT_MAX)
		return (0);
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	is_num(char **argv)
{
	int	i;
	int	j;
	int	x;

	i = 1;
	x = 4;
	if (argv[5])
		x++;
	while (i <= x)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
