#include "philo_bonus.h"

static void	one_philo(t_data *data)
{
	ft_delay(data->time_to_die);
	ft_print(data, 1, "died");
	exit (1);
}

static void	eating(t_data *data, int num)
{
	sem_wait(data->fork_s);
	ft_print(data, num, "has taken fork");
	if (data->ph_count == 1)
		one_philo(data);
	sem_wait(data->fork_s);
	ft_print(data, num, "has taken a fork");
	data->lifetime = ft_time(data);
	ft_print(data, num, "is eating");
	ft_delay(data->time_to_eat);
	sem_post(data->fork_s);
	sem_post(data->fork_s);
}

void	*waiter(void *in_data)
{
	t_data	*data;

	data = (t_data *)in_data;
	while (1)
	{
		ft_delay(10);
		if ((data->lifetime + data->time_to_die) <= ft_time(data) - 2)
		{
			sem_wait(data->print_s);
			printf("%ld %d %s", ft_time(data), data->i + 1, "died\n");
			exit (1);
		}
	}
	return (NULL);
}

void	lifetime(t_data *data)
{
	pthread_t	delay;

	if (pthread_create(&delay, NULL, &waiter, (void *)data) != 0)
		ft_error("thread err\n");
	pthread_detach(delay);
	if (data->i % 2)
		ft_delay(data->time_to_eat / 2);
	while (1)
	{
		eating(data, data->i + 1);
		data->eat_count--;
		ft_print(data, data->i + 1, "is sleeping");
		ft_delay(data->time_to_sleep);
		if (!data->eat_count)
			exit (0);
		ft_print(data, data->i + 1, "is thinking");
	}
}
