#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 30666

class Servidor
{
    public:
        static Servidor* Instance()
        {
            if(s_pInstance == 0)
            {
                s_pInstance = new Servidor();
                return s_pInstance;
            }
            return s_pInstance;
        }
        void start(){};
        int getServerSock(){return serverSock;}
        int acceptSocket();

        int sendData(int fd, const char* buffer,int len,int flags);
        int recvData(int fd, char* buffer, int len, int flags);
        virtual ~Servidor();
    protected:
    private:
        Servidor();
        static Servidor* s_pInstance;
        int serverSock;
        struct sockaddr_in serverAddr;
        struct sockaddr_in clientAddr;

};

typedef Servidor TheServidor;

#endif // SERVIDOR_H
