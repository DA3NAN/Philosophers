/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:00:39 by adnane            #+#    #+#             */
/*   Updated: 2023/03/27 17:22:12 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct {
    int id;
    pthread_mutex_t* left_fork;
    pthread_mutex_t* right_fork;
    pthread_mutex_t* shared_mutex;
    int time_to_die;
    int time_to_sleep;
    int time_to_eat;
} philosopher_info;

#endif