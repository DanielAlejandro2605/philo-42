About the project:

(1).    Each philosopher must be a thread:
    
    When we create a thread, it executes a function.
    Thus, we can create a function in which we implement the routine of a single the routine of a single philosopher. 

    By routine, I mean eating and sleeping while avoiding dying.

(2).    Thread's variables and functions:

    int	main(int argc, char *argv[])
    {
        /*Store information about the thread*/
        pthread_t	thread_1;

        /*To initialize a thread, we call the function pthread_create*/
        pthread_create(&thread_1, NULL, &ft_philo_routine, NULL);
        
        /*
        Arguments:
        (1) Is the pointer to the variable which stores
        about the thread.
        (2) Attributes for the thread, we san set NULL for default values
        (3) Pointer to the function to be executed
        (4) Arguments to the function to the executed
        */
        return (0);
    }

Remember that these function will return an int in case of error, so it must be
protected. 

(3).    Functions for the project:

    (1) usleep: int usleep(useconds_t usec);

    The usleep() function suspends execution of the calling thread for (at least) usec microseconds.  The sleep may be lengthened slightly by any system activity or by the time spent processing the call or by the granularity of system timers

(4).    Difference between processes and threads

    (1) We can have multiple threads inside a process.
        We cannot have multiple processes in a thread.
    (2) When we make a fork for creating a new process, we can say that we duplicate
        all the variables from one process to another.
        So, we can modify the duplicates individually and they will not be affected.
    (3) Using threads, all the variables are the same and all threads can access to all
        variables, that means that THEY HAVE A COMMON SET OF VARIBLES AND ADDRESS SPACE. 
    (4) All the threads use the same files handlers, all the files handlers are duplicated
        for each process.

(5).    Race Conditions

    Imagine that in the function executed by the threads, we modify the value of one variable (e.g get a = 0 to a = 2000000 making incremetation(a++) in a loop).
    All the threads we are going to perform this operation in parallel.

    The issues comes when the computer decides to stop the execution of a thread for some reason and when it restart, the value readed for making incremetation have been changed for another thread:

    For perform incremetation:

        Normally comportement:
                                 t1    t2
        read value from memory | 10 |  11
        make the incremetation | 11 |  12
        rewrite the memory     | 11 |  12

    ----- CPU decides to stop t2 until some point ---------

                                 t1    t2
        read value from memory | 25 |  25
        make the incremetation | 26 |        < --------- STOP EXACTLY HERE
        rewrite the memory     | 26 |  

    The result when it restart will be something like that : 

    
                                 t1    t2
        read value from memory | 30 |  25
        make the incremetation | 31 |  30    < --------- RESTART AT THIS POINT
        rewrite the memory     | 31 |  26


(6) Mutex

    Mutex are solution to this program, they are a way to lock the access to the
    variables:

    Example: 

    int meals;
    pthread_mutex_t mutex;

    void	*ft_philo_routine()
    {
        printf("Test the philo routine\n");
        for (int i = 0; i < 1000000; i++){
            pthread_mutex_lock(&mutex);
            meals++;
            pthread_mutex_unlock(&mutex);
        }
        printf("Waiting something\n");
        return ((void *)0);
    }

    int	main(int argc, char *argv[])
    {
        t_env	env;
        
        (void)argc;
        ft_init(&env, argv);
        pthread_t thread_1, thread_2;
        meals = 0;
        pthread_mutex_init(&mutex, NULL);
        if (pthread_create(&thread_1, NULL, &ft_philo_routine, NULL))
            return (1);
        if(pthread_create(&thread_2, NULL, &ft_philo_routine, NULL))
            return (1);
        if(pthread_join(thread_1, NULL))
            return (1);
        if(pthread_join(thread_2, NULL))
            return (1);
        printf("Meals : %d\n", meals);
        pthread_mutex_destroy(&mutex);
        return (0);
    }

(7) How to create multiples threads using loop

    int meals;
    pthread_mutex_t mutex;

    void	*ft_philo_routine()
    {
        for (int i = 0; i < 1000000; i++){
            pthread_mutex_lock(&mutex);
            meals++;
            pthread_mutex_unlock(&mutex);
        }
        return ((void *)0);
    }

    int	main(int argc, char *argv[])
    {
        t_env	env;
        
        (void)argc;
        ft_init(&env, argv);
        pthread_t th[4];
        meals = 0;
        pthread_mutex_init(&mutex, NULL);
        for(int i = 0; i < 4; i++)
        {
            if (pthread_create(th + i, NULL, &ft_philo_routine, NULL))
            return (1);
            printf("Thread number %d starts\n", i);
        }
        for(int i = 0; i < 4; i++)
        {
            if(pthread_join(th[i], NULL))
                return (1);
            printf("Thread number %d finish\n", i);
        }
        printf("Meals : %d\n", meals);
        pthread_mutex_destroy(&mutex);
        return (0);
    }

