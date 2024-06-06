#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 3

// İş parçacığı fonksiyonu
void	*thread_function(void *arg)
{
	int	id;

	id = *((int *)arg);
	while (1)
	{
		printf("Thread %d: Starting work.\n", id);
		sleep(2); // İş parçacığı 2 saniye bekler
		printf("Thread %d: Finished work.\n", id);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	threads[NUM_THREADS];
	int			thread_ids[NUM_THREADS];

	// İş parçacıklarını oluşturma
	for (int i = 0; i < NUM_THREADS; i++)
	{
		thread_ids[i] = i;
		pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
	}

		printf("How is the thread race going?\n");
	// İş parçacıklarının tamamlanmasını bekleme
	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
	printf("All threads have finished.\n");
	return (0);
}
