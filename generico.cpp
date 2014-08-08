#include "generico.h"
#include "banca.h"
#include "almacen.h"
#include "servidor.h"

const std::string Generico::s_type = "GENERICO";

Generico::Generico()
{
    //ctor
}

Generico::~Generico()
{
    //dtor
}

void Generico::procesarDatos(char* buffer, int len)
{
    char message[100];
    snprintf(message, sizeof message, "<%s>: %s", getName().c_str(), buffer);
    std::cout << "Will send to all: " << message << std::endl;
    sendToAll(message,sizeof message);
}

void Generico::sendToAll(char* message, int len)
{
  int n;

    for(size_t i=0; i<ElAlmacen::Instance()->clientes.size(); i++)
    {
        if(ElAlmacen::Instance()->clientes[i]->getStateID() == "GENERICO")
        {
            n = TheServidor::Instance()->sendData(ElAlmacen::Instance()->clientes[i]->getSocket(),message, strlen(message), 0);
            std::cout << n << " bytes sent." << std::endl;
        }
    }

}
