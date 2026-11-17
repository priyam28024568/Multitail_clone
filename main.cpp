#include<iostream>
#include<string>
#include<fcntl.h>
#include<unistd.h>
#include<cstring>
#include<poll.h>
#include<signal.h>
using namespace std;

bool running = true;

void handle_sigint(int sig){
    running = false;
}

int main(int argc, char* argv[]){
    signal(SIGINT, handle_sigint);
    int fd = open(argv[1], O_RDONLY | O_NONBLOCK);
    if(fd < 0){
        cout << "make sure the file exist" << endl;
        return 1;
    }

    off_t currrent_pos = lseek(fd, 0, SEEK_END);
    if(currrent_pos == (off_t) - 1){
        perror("lseek failed");
        close(fd);
        return 1;
    }

    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;

    char buffer[1024];

    while(running){
        int timeout_ms = 250;
        int ret = poll(&pfd, 1, timeout_ms);

        if(ret < 0){
            if(errno == EINTR){
                continue;
            }
            std::perror("poll error");
            break;
        }

        if(ret == 0){
            continue;
        }

        if(pfd.revents & POLLIN){
            ssize_t bytes_read;

            while((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0){
                buffer[bytes_read] = '\0';

                write(STDOUT_FILENO, buffer, bytes_read);

                if(buffer[bytes_read - 1] != '\n'){
                    write(STDOUT_FILENO, "\n", 1);
                }
            }
        }
    }

    close(fd);
    cout << "\n Exiting tail cleanly." << endl;
    return 0;
}
