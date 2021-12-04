#include "philo_bonus.h"

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit (1);
}

int	ft_atoi(const char *str)
{
	long int	num;
	int			i;
	int			np;

	np = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		||str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			np = -1;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		if (num * 10 + (str[i] + '0') < num && np > 0)
			return (-1);
		else if (num * 10 + (str[i] + '0') < num && np < 0)
			return (0);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(np * num));
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	arg_checker(int argc, char **argv)
{
	int	i;

	argc -= 1;
	while (argc)
	{
		i = 0;
		while (argv[argc][i])
		{
			if (!ft_isdigit(argv[argc][i]))
				return (1);
			i++;
		}
		if (ft_atoi(argv[argc]) < 1)
			return (1);
		argc--;
	}
	return (0);
}
