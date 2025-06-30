#include "lib/common.h"

void *mutex_write_log_file(void *args)
{
    thread_args_t *log_file_path = (thread_args_t *)args;

    pthread_mutex_log(log_file_path->log_file_mutex);

    FILE *fp = fopen(log_file_path->log_path, "a");

    if (fp)
    {
        // fprintf(fp,...);
        fclose(fp);
    }
    // TODO : refactoring on the thread_args_t, with the correct argument to write on log file

    pthread_mutex_unlock(log_file_path->log_file_mutex);

    free(log_file_path);

    return NULL;
}

int main(int argc, char const *argv[])
{
    if (argc < 1)
    {
        TEST_ERROR;
    }
    int port = atoi(argv[1]);

    pthread_mutex_t log_file_mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_destroy(&log_file_mutex);
    
    return 0;
}
