#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	ft_time(t_data *data)
{
	struct timeval	cur_tv;

	gettimeofday(&cur_tv, NULL);
	return ((cur_tv.tv_sec * 1000 + cur_tv.tv_usec / 1000)
		- data->start);
}

void	ft_print(t_data *data, int num, char *s)
{
	pthread_mutex_lock(&data->print_m);
	printf("%ld %d %s\n", get_time() - data->start,
		num, s);
	pthread_mutex_unlock(&data->print_m);
}

void	ft_delay(int ms)
{
	long	time;

	time = get_time();
	while (get_time() - time < (long)ms)
		usleep(100);
}
