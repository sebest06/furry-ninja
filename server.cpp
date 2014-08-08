#include "server.h"
#include "servidor.h"
#include "almacen.h"
#include "fabrica.h"
#include <string>


using namespace std;

Server::Server()
{
  //Initialize static mutex from MyThread
    MyThread::InitMutex();
}

/*
	AcceptAndDispatch();

	Main loop:
		Blocks at accept(), until a new connection arrives.
		When it happens, create a new thread to handle the new client.
*/
void Server::AcceptAndDispatch() {

    int c;
    MyThread *t;

    while(1) {

      t = new MyThread();
      c = TheServidor::Instance()->acceptSocket();

      if(c < 0) {
        cerr << "Error on accept";
      }
      else {
        t->Create((void *) Server::HandleClient, &c);
      }
    }
}

void *Server::HandleClient(void *args) {

    Cliente *c;
    int thisSocket = *(int *) args;

    char buffer[256-25];
    int index;
    int n;

    memset(buffer, 0, sizeof buffer);
    n = TheServidor::Instance()->recvData(thisSocket, buffer, sizeof buffer, 0);
    c = LaFabrica::Instance()->fabricar(buffer,n,thisSocket);

    if(c == NULL)
    {
        close(thisSocket);
        return NULL;
    }

    cout << "Adding client with id: " << c->getId() << endl;

    MyThread::LockMutex("Critical Area");
    ElAlmacen::Instance()->clientes.push_back(c);
    MyThread::UnlockMutex("Critical Area");

    while(1) {
        memset(buffer, 0, sizeof buffer);
        n = TheServidor::Instance()->recvData(thisSocket, buffer, sizeof buffer, 0);
        //Client disconnected?
        if(n == 0) {
          cout << "Client diconnected" << endl;
          close(thisSocket);

          //Remove client in Static clients <vector> (Critical section!)
          MyThread::LockMutex("Borrando de lista");

            index = Server::FindSocketClient(thisSocket);

            cout << "Erasing user whose name id is: " << ElAlmacen::Instance()->clientes[index]->getId() << endl;

            ElAlmacen::Instance()->clientes.erase(ElAlmacen::Instance()->clientes.begin() + index);

          MyThread::UnlockMutex("Borrando de lista");

          break;
        }
        else if(n < 0) {
          cerr << "Error while receiving message from client: " << c->getName() << endl;
        }
        else {
            MyThread::LockMutex((const char *) c->getName().c_str());
            c->procesarDatos(buffer,n);
            MyThread::UnlockMutex((const char *) c->getName().c_str());
        }
    }

    //End thread
    return NULL;
}
/*
  Should be called when vector<Client> clients is locked!
*/
int Server::FindSocketClient(int socket)
{
    for(size_t i=0; i<ElAlmacen::Instance()->clientes.size(); i++)
    {
        if((ElAlmacen::Instance()->clientes[i]->getSocket()) == socket) return (int) i;
    }

    cerr << "Client id not found." << endl;
    return -1;
}
