#include "philo_bonus.h"

static void	logic(t_data *data)
{
	data->i = -1;
	while (++data->i < data->ph_count)
	{
		data->philo_p[data->i] = fork();
		if (data->philo_p[data->i] == -1)
			ft_error("Pid err\n");
		if (!data->philo_p[data->i])
			lifetime(data);
	}
	data->i = -1;
	while (++data->i < data->ph_count)
	{
		waitpid(-1, &(data->status), 0);
		if (data->status != 0)
		{
			data->j = -1;
			while (++data->j < data->ph_count)
				kill(data->philo_p[data->j], SIGKILL);
		}
		data->i++;// see do it if delete this str!!
	}
}

static void	data_init(t_data *data, int argc, char **argv)
{
	data->philo_p = NULL;
	data->ph_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->eat_count = -1;
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	data->start = get_time();
	sem_unlink("fork");
	sem_unlink("print");
	data->fork_s = sem_open("fork", O_CREAT, S_IRWXG, data->ph_count);
	data->print_s = sem_open("print", O_CREAT, S_IRWXG, 1);
	if (data->fork_s == SEM_FAILED || data->print_s == SEM_FAILED)
		ft_error("SEM_FAILED err\n");
	data->philo_p = (pid_t *)malloc(sizeof(pid_t) * data->ph_count);
	if (!(data->ph_count))
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
	logic(data);
	sem_unlink("fork");
	sem_unlink("print");
	sem_close(data->fork_s);
	sem_close(data->print_s);
	if (data->philo_p)
		free(data->philo_p);
	if (data)
		free(data);
	return (0);
}
