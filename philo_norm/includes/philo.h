#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_mutex_t	*fork_m;
	pthread_mutex_t	print_m;
	pthread_mutex_t	lock_m;
	pthread_t		*philo;
	long			start;
	int				ph_count;
	int				eat_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				i;
	int				*lifetime;
}	t_data;

// utils.c
void	ft_error(char *str);
int		ft_atoi(const char *str);
int		arg_checker(int argc, char **argv);
int		ft_strlen(char *str);
// utils2.c
long	get_time(void);
long	ft_time(t_data *data);
void	ft_print(t_data *data, int num, char *s);
void	ft_delay(int ms);
// logic.c
void	*lifetime(void *in_data);
void	*waiter(void *in_data);

#endif