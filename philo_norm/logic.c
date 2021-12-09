#include "philo.h"

static void	eating(t_data *data, int num)
{
	int	left_f;
	int	rigth_f;

	left_f = num - 1;
	if (num == 1)
		rigth_f = data->ph_count - 1;
	else
		rigth_f = num - 2;
	pthread_mutex_lock(&data->fork_m[rigth_f]);
	ft_print(data, num, "has taken a rigth fork");
	pthread_mutex_lock(&data->fork_m[left_f]);
	ft_print(data, num, "has taken a left fork");
	data->lifetime[num - 1] = ft_time(data);
	ft_print(data, num, "is eating");
	ft_delay(data->time_to_eat);
	pthread_mutex_unlock(&data->fork_m[left_f]);
	pthread_mutex_unlock(&data->fork_m[rigth_f]);
}

static int	ft_stick(t_data *data)
{
	long	time;
	int		i;

	i = -1;
	time = ft_time(data) - 2;
	while (++i < data->ph_count)
	{
		if (data->lifetime[i] != -1)
		{
			if ((data->lifetime[i] + data->time_to_die) < time)
			{
				pthread_mutex_lock(&data->print_m);
				printf("%ld %d %s", get_time() - data->start, i + 1, "died\n");
				return (0);
			}
		}
	}
	return (1);
}

void	*waiter(void *in_data)
{
	t_data	*data;
	int		not_dead;

	data = (t_data *)in_data;
	not_dead = 1;
	while (not_dead)
	{
		not_dead = ft_stick(data);
		if (data->i <= 0 && data->eat_count > 0 && not_dead)
			not_dead = 0;
	}
	ft_delay(4);
	return (NULL);
}

void	*lifetime(void *in_data)
{
	t_data	*data;
	int		num;
	int		temp_eat;

	data = (t_data *)in_data;
	temp_eat = data->eat_count;
	num = data->i + 1;
	pthread_mutex_unlock(&data->lock_m);
	data->lifetime[num - 1] = ft_time(data);
	if (num % 2)
		ft_delay(data->time_to_eat / 2);
	while (temp_eat)
	{
		eating(data, num);
		ft_print(data, num, "is sleeping");
		ft_delay(data->time_to_sleep);
		ft_print(data, num, "is thinking");
		temp_eat--;
	}
	if (temp_eat == 0)
	{
		data->i--;
		data->lifetime[num - 1] = -1;
	}
	return (NULL);
}
