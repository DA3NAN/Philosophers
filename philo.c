/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:59:14 by adnane            #+#    #+#             */
/*   Updated: 2023/05/11 17:42:15 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_thread	thread;

	if (parse_arguments(argc, argv))
		return (1);
	thread.num_philo = atoi(argv[1]);
	allocate(&thread);
	create_threads(thread, argv);
	free_all(&thread);
	return (0);
}
