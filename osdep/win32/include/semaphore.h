#ifndef MP_WRAP_SEMAPHORE_H_
#define MP_WRAP_SEMAPHORE_H_

#include <sys/types.h>
#include <pthread.h>

#define SEM_VALUE_MAX 100

typedef struct {
    pthread_mutex_t lock;
    pthread_cond_t wakeup;
    unsigned int value;
} sem_t;

#define sem_init m_sem_init
int sem_init(sem_t *sem, int pshared, unsigned int value);
#define sem_wait m_sem_wait
int sem_wait(sem_t *sem);
#define sem_trywait m_sem_trywait
int sem_trywait(sem_t *sem);
#define sem_timedwait m_sem_timedwait
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
#define sem_post m_sem_post
int sem_post(sem_t *sem);
#define sem_destroy m_sem_destroy
int sem_destroy(sem_t *sem);

#endif
