#include "philo.h"

void	print_philos(t_philo philo)
{
	// printf("Philo ID: %d\n", philo.philo_id);
	printf("Num of philo: %d\n", philo.data->num_of_philo);
	printf("Time to die: %d\n", philo.data->time_to_die);
	printf("Time to eat: %d\n", philo.data->time_to_eat);
	printf("Time to sleep: %d\n", philo.data->time_to_sleep);
	if (philo.data->max_eat == -1)
		printf("Time must eat: (no limit)\n");
	else
		printf("Time must eat: %d\n", philo.data->max_eat);
}
