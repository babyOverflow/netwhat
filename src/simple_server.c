#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT_NUM 80
#define BUFFER_SIZE 64

int	main(void)
{
	struct sockaddr_in server_addr;

	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	memset((void *)&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT_NUM);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(server_fd, (void *)&server_addr, sizeof(server_addr))  == -1)
	{
		perror("fail to open socket!");
		exit(1);
	}
	if (listen(server_fd, 5) == -1)
	{
		perror("fail to listen!");
		exit(1);
	}

	char *listen_addr = inet_ntoa(server_addr.sin_addr);
	printf("listen %s:%d\n", listen_addr, ntohs( server_addr.sin_port));

	
	while (1)
	{
		struct sockaddr_in peer_addr;
		socklen_t	peer_addr_len = sizeof(peer_addr);
		int client_fd;
		if ((client_fd = accept(server_fd, (void *)&peer_addr, &peer_addr_len)) == -1)
		{
			perror("fail to accept");
			exit(1);
		}
		char buf[BUFFER_SIZE];
		int buf_len ;
		printf("from : %s:%d\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
		while ((buf_len = recv(client_fd, buf, BUFFER_SIZE - 1, 0)) > 0)
		{
			buf[buf_len] = '\0';
			printf("%s", buf);
		}
		close(client_fd);
	}
	return 0;
}