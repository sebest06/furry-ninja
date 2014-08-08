#include "servidor.h"

Servidor* Servidor::s_pInstance = 0;
Servidor::Servidor()
{
  //For setsock opt (REUSEADDR)
  int yes = 1;
  serverSock = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serverAddr, 0, sizeof(sockaddr_in));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(PORT);

  //Avoid bind error if the socket was not close()'d last time;
  setsockopt(serverSock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));

  if(bind(serverSock, (struct sockaddr *) &serverAddr, sizeof(sockaddr_in)) < 0)
    std::cerr << "Failed to bind";

  listen(serverSock, 5);
}

Servidor::~Servidor()
{

}

int Servidor::acceptSocket()
{
    int socket;
    socklen_t cliSize = sizeof(sockaddr_in);
    socket = accept(serverSock, (struct sockaddr *) &clientAddr, &cliSize);
    return socket;
}

int Servidor::sendData(int fd, const char* buffer, int len, int flags)
{
    return send(fd, buffer, len, flags);
}

int Servidor::recvData(int fd, char* buffer, int len, int flags)
{
    return recv(fd,buffer,len,flags);
}

