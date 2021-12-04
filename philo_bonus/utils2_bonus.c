#include "philo_bonus.h"

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
	sem_wait(data->print_s);
	printf("%ld %d %s\n", get_time() - data->start,
		num, s);
	sem_post(data->print_s);
}

void	ft_delay(int ms)
{
	long	time;

	time = get_time();
	while (get_time() - time < (long)ms)
		usleep(100);
}
