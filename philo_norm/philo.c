#include "philo.h"

static void	mutex_destroy(t_data *data)
{
	pthread_mutex_destroy(&data->lock_m);
	pthread_mutex_destroy(&data->print_m);
	data->i = -1;
	while (++data->i < data->ph_count)
		pthread_mutex_destroy(&data->fork_m[data->i]);
}

static void	mutex_init(t_data *data)
{
	pthread_t	delay;

	if (pthread_mutex_init(&data->lock_m, NULL) != 0)
		ft_error("mutex_err\n");
	if (pthread_mutex_init(&data->print_m, NULL) != 0)
		ft_error("mutex_err\n");
	data->i = 0;
	while (data->i < data->ph_count)
		if (pthread_mutex_init(&data->fork_m[data->i++], NULL) != 0)
			ft_error("mutex_err\n");
	data->i = 0;
	while (data->i < data->ph_count)
	{
		pthread_mutex_lock(&data->lock_m);
		if (pthread_create(&data->philo[data->i],
				NULL, lifetime, (void *)data) != 0)
			ft_error("thread_error\n");
		pthread_detach(data->philo[data->i]);
		pthread_mutex_lock(&data->lock_m);
		data->i++;
		pthread_mutex_unlock(&data->lock_m);
	}
	pthread_create(&delay, NULL, waiter, (void *)data);
	pthread_join(delay, NULL);
	mutex_destroy(data);
}

static void	data_init(t_data *data, int argc, char **argv)
{
	data->fork_m = NULL;
	data->philo = NULL;
	data->lifetime = NULL;
	data->ph_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->eat_count = -1;
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	data->start = get_time();
	data->philo = (pthread_t *)malloc(sizeof(pthread_t)
			* data->ph_count);
	data->fork_m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->ph_count);
	data->lifetime = (int *)malloc(sizeof(int) * data->ph_count);
	if (!data->philo || !data->fork_m || !data->lifetime)
		ft_error("malloc_err\n");
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6 || arg_checker(argc, argv))
		ft_error("bad arguments\n");
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_error("malloc_err\n");
	data_init(data, argc, argv);
	mutex_init(data);
	if (data->philo)
		free(data->philo);
	if (data->fork_m)
		free(data->fork_m);
	if (data->lifetime)
		free(data->lifetime);
	if (data)
		free(data);
	return (0);
}
