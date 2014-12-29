#ifndef MP_WRAP_PTHREAD_H_
#define MP_WRAP_PTHREAD_H_

#include <windows.h>

#include <sys/types.h>

// Note: all pthread functions are mangled to make static linking easier.

#define pthread_once_t INIT_ONCE
#define PTHREAD_ONCE_INIT INIT_ONCE_STATIC_INIT

#define pthread_once m_pthread_once
int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));

typedef struct {
    volatile LONG requires_init;
    CRITICAL_SECTION cs;
} pthread_mutex_t;

#define PTHREAD_MUTEX_INITIALIZER {1}

#define pthread_mutexattr_t int
#define pthread_mutexattr_destroy(attr) (void)0
#define pthread_mutexattr_init(attr) (*(attr) = 0)
#define pthread_mutexattr_settype(attr, type) (void)0
// CRITICAL_SECTION is always recursive
#define PTHREAD_MUTEX_RECURSIVE 0

#define pthread_mutex_destroy m_pthread_mutex_destroy
int pthread_mutex_destroy(pthread_mutex_t *mutex);
#define pthread_mutex_init m_pthread_mutex_init
int pthread_mutex_init(pthread_mutex_t *restrict mutex,
                       const pthread_mutexattr_t *restrict attr);

#define pthread_mutex_lock m_pthread_mutex_lock
int pthread_mutex_lock(pthread_mutex_t *mutex);
#define pthread_mutex_unlock m_pthread_mutex_unlock
int pthread_mutex_unlock(pthread_mutex_t *mutex);

#define pthread_cond_t CONDITION_VARIABLE

#define PTHREAD_COND_INITIALIZER CONDITION_VARIABLE_INIT

#define pthread_condattr_t int

#define pthread_cond_destroy(c) (void)0

#define pthread_cond_init(cond, attr) InitializeConditionVariable(cond)
#define pthread_cond_broadcast(cond) WakeAllConditionVariable(cond)
#define pthread_cond_signal(cond) WakeConditionVariable(cond)

#define pthread_cond_timedwait m_pthread_cond_timedwait
int pthread_cond_timedwait(pthread_cond_t *restrict cond,
                           pthread_mutex_t *restrict mutex,
                           const struct timespec *restrict abstime);
#define pthread_cond_wait m_pthread_cond_wait
int pthread_cond_wait(pthread_cond_t *restrict cond,
                      pthread_mutex_t *restrict mutex);

// Unusual, but allowed by POSIX.
typedef struct {
    DWORD id;
    struct m_thread_info *info;
} pthread_t;

#define pthread_equal(a, b) ((a).id == (b).id)

#define pthread_self m_pthread_self
pthread_t pthread_self(void);
#define pthread_exit m_pthread_exit
void pthread_exit(void *retval);
#define pthread_join m_pthread_join
int pthread_join(pthread_t thread, void **retval);
#define pthread_detach m_pthread_detach
int pthread_detach(pthread_t thread);

#define pthread_attr_t int

#define pthread_create m_pthread_create
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);

#endif
