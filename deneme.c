#include <pthread.h>
#include <stdio.h>

// deadlock
//./philo 2 200 40 70
// tek philo 5. arguman verince sonsuz bekleme

int				counter = 0;

pthread_mutex_t	counter_mutex;

void	*increment_counter(void *arg)
{
	for (int i = 0; i < 100000000; ++i)
	{
		// pthread_mutex_lock(&counter_mutex);
		counter++;
		// pthread_mutex_unlock(&counter_mutex);
	}
	return (NULL);
}

int	main(void)
{

	pthread_mutex_init(&counter_mutex, NULL);
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, increment_counter, NULL);
	pthread_create(&thread2, NULL, increment_counter, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Counter değeri: %d\n", counter);
	pthread_mutex_destroy(&counter_mutex);
	return (0);
}
