#include "philo.h"

void	print_philos(t_data data)
{
	printf("Num of philo: %d\n", data.num_of_philo);
	printf("Time to die: %d\n", data.time_to_die);
	printf("Time to eat: %d\n", data.time_to_eat);
	printf("Time to sleep: %d\n", data.time_to_sleep);
	if (data.max_eat == -1)
		printf("Time must eat: (no limit)\n");
	else
		printf("Time must eat: %d\n", data.max_eat);
}
