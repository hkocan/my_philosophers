#include <pthread.h>
#include <stdio.h>

// deadlock
//./philo 2 200 40 70
// tek philo 5. arguman verince sonsuz bekleme

// Paylaşılan kaynak
int				counter = 0;

// Mutex tanımı
pthread_mutex_t	counter_mutex;

void	*increment_counter(void *arg)
{
	for (int i = 0; i < 100000000; ++i)
	{
		// Mutex'i kilitle
		// pthread_mutex_lock(&counter_mutex);
		counter++;
		// Mutex'i aç
		// pthread_mutex_unlock(&counter_mutex);
	}
	return (NULL);
}

int	main(void)
{
	// Mutex'i başlat
	pthread_mutex_init(&counter_mutex, NULL);
	// İş parçacıkları tanımı
	pthread_t thread1, thread2;
	// İş parçacıklarını oluştur ve başlat
	pthread_create(&thread1, NULL, increment_counter, NULL);
	pthread_create(&thread2, NULL, increment_counter, NULL);
	// İş parçacıklarının bitmesini bekle
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	// Sonuç
	printf("Counter değeri: %d\n", counter);
	// Mutex'i yok et
	pthread_mutex_destroy(&counter_mutex);
	return (0);
}
