#include <unistd.h>  
#include <errno.h>  
#include <stdlib.h>  
#include <fcntl.h>  
#include <limits.h>  
#include <sys/types.h>  
#include <stdio.h>  
#include <string.h>  
#include <pthread.h>
#include <poll.h>

#include <sys/socket.h>
#include <sys/un.h>

#define pollcnt  1

char *fifo_name = "my_fifo";  

int create_sock(const char* name, int type, mode_t perm, uid_t uid, gid_t gid)
{
	struct sockaddr_un addr;
	int fd, ret=-1;

	fd = socket(PF_UNIX, type, 0);	

	if(fd < 0){
		printf("Failed to open socket %s:%s\n", name, strerror(errno));
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", name);

	if(access(addr.sun_path, F_OK) == 0){
		ret = unlink(addr.sun_path);
		if(ret < 0){
			close(fd);
			return -1;
		}
	}

	ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret != 0){
		printf("Failed to bind socket %s:%s\n",name, strerror(errno));
		close(fd);
		unlink(addr.sun_path);
		return -1;
	}

	chown(addr.sun_path, uid, gid);
	chmod(addr.sun_path, perm);

	return fd;
}

void handle_sock(int fd)
{
	int s;
	char buf[PIPE_BUF];
	struct sockaddr_un addr;
	socklen_t addr_size = sizeof(addr);

	printf("%s %d\n", __FUNCTION__, __LINE__);
	
	if((s = accept(fd, (struct sockaddr*)&addr, &addr_size)) < 0)
		return;
	read(s, buf, PIPE_BUF);
	printf("read:%s\n", buf); 
	close(s);
}

static void*  read_thread_pipe(void* data)
{
	int fd_r = -1;
	int timeout = 5000;
	char buf[PIPE_BUF + 1];	
	struct pollfd poll_fd[pollcnt];
	struct sockaddr_un addr;
	char buffer[PIPE_BUF + 1];  
	int ret;
	
#if 0
	if(access(fifo_name, F_OK) == -1)
	{
		mkfifo(fifo_name, 0777);
	}
	
	printf("Process %d opening FIFO O_RDONLY\n", getpid());  
	fd_r = open(fifo_name, O_RDONLY);
	printf("Process %d result %d\n", getpid(), fd_r);  
#endif
//	fd_r = create_sock(fifo_name, SOCK_STREAM, 0666, 0 , 0);
	fd_r = socket(PF_UNIX, SOCK_STREAM, 0);
	if(fd_r < 0){
		printf("Failed create sock %s:%s\n", fifo_name,strerror(errno));
		return NULL;
	}
	
	memset(&addr, 0, sizeof(addr) );
	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", fifo_name);
	ret = connect(fd_r, (struct sockaddr*)&addr, sizeof(addr)); 
	if(ret < 0){
		printf("Failed connect sock %s:%s\n", fifo_name, strerror(errno));
		return NULL;
	}
	do{
		fgets(buffer, sizeof buffer, stdin);
		printf("write:%s\n", buffer);

//		write(pipe_fd, buffer, PIPE_BUF);  
		write(fd_r, buffer, PIPE_BUF);  
	}while(1);

#if 0
	poll_fd[0].fd = fd_r;
	poll_fd[0].events = POLLIN;

	do{
		int ret = 0;
		ret = poll(poll_fd, pollcnt, timeout);

		if(ret == 0){
			printf("cmd:%s\n", buf);
			continue;
		}

		if(ret < 0){
			if((errno == EAGAIN) || (errno == EINTR)){
				continue;
			}
			break;
		}
		
		if(poll_fd[0].revents & POLLIN){
			read(poll_fd[0].fd, buf, PIPE_BUF);
			printf("cmd:%s\n", buf);
			continue;
		}
		
		
	}while(1);
#endif
}

int main()  
{  
	int pipe_fd = -1;  
	int sock_fd = -1;
	char buffer[PIPE_BUF + 1];  
	char buf[PIPE_BUF + 1];	
	pthread_t pid;
	struct pollfd poll_fd[pollcnt]; 
	int timeout = 5000;
//read thread

#if 0
	if(access(fifo_name, F_OK) == -1)  
	{  
		//管道文件不存在,创建命名管道  
		if(mkfifo(fifo_name, 0777) != 0)  
		{  
			printf("Could not create fifo %s\n", fifo_name);  
			exit(EXIT_FAILURE);  
		}  
	}  

//以只写阻塞方式打开FIFO文件
	printf("Process %d opening FIFO O_WRONLY\n", getpid());  
	pipe_fd = open(fifo_name, O_WRONLY );  
	printf("Process %d result %d\n", getpid(), pipe_fd);  
#endif
	sock_fd = create_sock(fifo_name, SOCK_STREAM, 0666, 0 , 0);
	if(sock_fd < 0){
		printf("Could not create fifo %s\n", fifo_name);  
		return -1;
	}		
	listen(sock_fd, 4);
	
	pthread_create(&pid, NULL, read_thread_pipe , NULL);
	//write thread
	poll_fd[0].fd = sock_fd;
	poll_fd[0].events = POLLIN;

	do{
		int ret = 0;
		ret = poll(poll_fd, pollcnt, timeout);
	printf("%s %d\n", __FUNCTION__, __LINE__);

		if(ret == 0){
			printf("cmd:%s\n", buf);
			continue;
		}

		if(ret < 0){
			if((errno == EAGAIN) || (errno == EINTR)){
				continue;
			}
	printf("%s %d\n", __FUNCTION__, __LINE__);
			break;
		}
		
		if(poll_fd[0].revents & POLLIN){
			//read(poll_fd[0].fd, buf, PIPE_BUF);
			//printf("poll_fd cmd:%s\n", buf);
			handle_sock(poll_fd[0].fd);
			continue;
		}
		
		
	}while(1);

#if 0
	do{
		fgets(buffer, sizeof buffer, stdin);
		printf("write:%s\n", buffer);

//		write(pipe_fd, buffer, PIPE_BUF);  
		write(sock_fd, buffer, PIPE_BUF);  
	}while(1);

	//	close(pipe_fd);  
#endif
	close(sock_fd);
	printf("Process %d finished\n", getpid());  
	exit(EXIT_SUCCESS);  
} 
