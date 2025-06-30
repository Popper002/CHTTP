#include "lib/common.h"

int open_connection(int port)
{
    if(port < 0 )
    {
        TEST_ERROR; 
        return -1; 
    }
    int opt = 1; 
    struct sockaddr_in address;
    ssize_t valread;
    socklen_t addrlen = sizeof(address);
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_fd < 0 )
    {
        TEST_ERROR; 
        return errno; 
    }
    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        TEST_ERROR;
        close(sock_fd);
        return errno;
    }
#ifdef SO_REUSEPORT
    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
    {
        TEST_ERROR;
        close(sock_fd);
        return errno;
    }
#endif
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(port);

    if(bind(sock_fd, (struct sockaddr*)&address, sizeof(address)) < 0 )
    {
        TEST_ERROR;
        close(sock_fd);
        return errno;
    }
    if(listen(sock_fd, 3 ) <0)
    {
        TEST_ERROR;
        close(sock_fd);
        return errno; 
    }

    printf("Server listening on port %d\n", port);

    while (1)
    {
        int new_Socket_fd;
        addrlen = sizeof(address);
        new_Socket_fd = accept(sock_fd, (struct sockaddr*)&address, &addrlen);
        if(new_Socket_fd < 0)
        {
            TEST_ERROR;
            continue; // Non chiudere il server, passa alla prossima connessione
        }

        char buffer[1024]={0}; 
        valread = read(new_Socket_fd, buffer, 1024-1);
        printf("RECEIVED ON PORT %d\n%s\nEND MSG\n", port, buffer);
        send(new_Socket_fd, "OK", strlen("OK"),0);

        close(new_Socket_fd);
    }

    close(sock_fd); 
    return 0; 
}     
void walcome()
{
printf(
" __    __    __      __                       ______                                                           \n"
"/  |  /  |  /  |    /  |                     /      \\                                                          \n"
"$$ |  $$ | _$$ |_  _$$ |_     ______        /$$$$$$  |  ______    ______   __     __  ______    ______         \n"
"$$ |__$$ |/ $$   |/ $$   |   /      \\       $$ \\__$$/  /      \\  /      \\ /  \\   /  |/      \\  /      \\        \n"
"$$    $$ |$$$$$$/ $$$$$$/   /$$$$$$  |      $$      \\ /$$$$$$  |/$$$$$$  |$$  \\ /$$//$$$$$$  |/$$$$$$  |       \n"
"$$$$$$$$ |  $$ | __ $$ | __ $$ |  $$ |       $$$$$$  |$$    $$ |$$ |  $$/  $$  /$$/ $$    $$ |$$ |  $$/        \n"
"$$ |  $$ |  $$ |/  |$$ |/  |$$ |__$$ |      /  \\__$$ |$$$$$$$$/ $$ |        $$ $$/  $$$$$$$$/ $$ |             \n"
"$$ |  $$ |  $$  $$/ $$  $$/ $$    $$/       $$    $$/ $$       |$$ |         $$$/   $$       |$$ |             \n"
"$$/   $$/    $$$$/   $$$$/  $$$$$$$/         $$$$$$/   $$$$$$$/ $$/           $/     $$$$$$$/ $$/              \n"
"                            $$ |                                                                               \n"
"                            $$ |                                                                               \n"
"                            $$/                                                                                \n"
"           ______      _______                                                     ______    ______    ______  \n"
"         _/      \\_   /       \\                                                   /      \\  /      \\  /      \\ \n"
"        / $$$$$$   \\  $$$$$$$  | ______    ______    ______    ______    ______  /$$$$$$  |/$$$$$$  |/$$$$$$  |\n"
"       /$$$ ___$$$  \\ $$ |__$$ |/      \\  /      \\  /      \\  /      \\  /      \\ $$$  \\$$ |$$$  \\$$ |$$____$$ |\n"
"      /$$/ /     $$  |$$    $$//$$$$$$  |/$$$$$$  |/$$$$$$  |/$$$$$$  |/$$$$$$  |$$$$  $$ |$$$$  $$ | /    $$/ \n"
"      $$ |/$$$$$ |$$ |$$$$$$$/ $$ |  $$ |$$ |  $$ |$$ |  $$ |$$    $$ |$$ |  $$/ $$ $$ $$ |$$ $$ $$ |/$$$$$$/  \n"
"      $$ |$$  $$ |$$ |$$ |     $$ \\__$$ |$$ |__$$ |$$ |__$$ |$$$$$$$$/ $$ |      $$ \\$$$$ |$$ \\$$$$ |$$ |_____ \n"
"      $$ |$$  $$  $$/ $$ |     $$    $$/ $$    $$/ $$    $$/ $$       |$$ |      $$   $$$/ $$   $$$/ $$       |\n"
"      $$  \\$$$$$$$$/  $$/       $$$$$$/  $$$$$$$/  $$$$$$$/   $$$$$$$/ $$/        $$$$$$/   $$$$$$/  $$$$$$$$/ \n"
"       $$   \\__/   |                     $$ |      $$ |                                                        \n"
"        $$$    $$$/                      $$ |      $$ |                                                        \n"
"          $$$$$$/                        $$/       $$/                                                         \n"
);
}
void *mutex_write_log_file(void *args)
{
    thread_args_t *log_file_path = (thread_args_t *)args;

    pthread_mutex_lock(log_file_path->log_file_mutex);

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
    walcome();
    int port = atoi(argv[1]);
    int res; 
    pthread_mutex_t log_file_mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_destroy(&log_file_mutex);
    
    res = open_connection(port); 


    return 0;
}
