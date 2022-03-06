/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:36:29 by ralena            #+#    #+#             */
/*   Updated: 2022/01/23 16:43:53 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_state	state;
	int		tracking;

	if (argc != 5 && argc != 6)
		return (error(ERROR_NUM_ARG));
	if (parse_arguments_to_state(argc, argv, &state) == 1)
		return (1);
	if (init_state(&state) == 1)
		return (1);
	state.time_start = timer();
	start_threads(&state);
	tracking = threads_tracking(&state);
	threads_join(&state);
	free(state.fork);
	free(state.philo);
	return (tracking);
}
