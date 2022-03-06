/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:36:32 by ralena            #+#    #+#             */
/*   Updated: 2022/01/23 16:46:22 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define ERROR_NUM_ARG 101
# define ERROR_ARG 102
# define ERROR_NUM_PHILO 103

typedef struct s_philo
{
	pthread_t		thread;
	int				num_philo;
	int				eat_time;
	int				left_fork;
	int				right_fork;
	unsigned long	last_eat_time;
	struct s_state	*data;
}					t_philo;

typedef struct s_state
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_must_eat;
	int				eat_philo;
	int				died;
	unsigned long	time_start;
	t_philo			*philo;
	pthread_mutex_t	*fork;
}					t_state;

//philosophers.c
int				main(int argc, char **argv);

//parsing_and_initialization.c
int				parse_arguments_to_state(int argc, char **argv, t_state *state);
int				init_state(t_state *state);
void			init_philo(t_state *state, int i);

//philosophers_lifecycle.c
void			*threads_life_support(t_philo *philo);
int				threads_life_support_additional(t_philo *philo);
void			threads_join(t_state *state);
int				threads_tracking(t_state *state);
void			start_threads(t_state *state);

//utils.c
int				print_philosopher_state(int flag, t_philo *philo);
int				print_parameters(unsigned long time_to_output,
					int num, char *str);
int				ft_atoi(char *nptr);
int				error(int error_type);
unsigned long	timer(void);

#endif
