#include "fabrica.h"

#include "almacen.h"
#include "banca.h"
#include "generico.h"
#include "visor.h"
#include "operador.h"

Fabrica* Fabrica::s_pInstance = 0;
Fabrica::Fabrica()
{
    //ctor
    m_Ukids = 0;
}

Fabrica::~Fabrica()
{
    //dtor
}

Cliente* Fabrica::fabricar(char* buffer, int len, int socket)
{
    Cliente *c;

    char *pch;
    pch = strtok (buffer," ,.-/\r\n");

    if(strcmp(pch,"nick") == 0)
    {
        c = new Generico();
        pch = strtok (NULL," ,.-/\r\n");
        c->setName(pch);
        c->setId(m_Ukids);
        m_Ukids++;
    }
    else if(strcmp(pch,"banca") == 0)
    {
        c = new Banca();
        pch = strtok (NULL," ,.-/\r\n");
        c->setName(pch);
        pch = strtok (NULL," ,.-/\r\n");
        c->setId(atoi(pch));
    }
    else if(strcmp(pch,"operador") == 0)
    {
        c = new Operador();
        pch = strtok (NULL," ,.-/\r\n");
        c->setName(pch);
        pch = strtok (NULL," ,.-/\r\n");
        c->setId(atoi(pch));
    }
    else
    {
        c = NULL;
    }

/*    switch(buffer[0])
    {
        case '1':
            c = new Banca();
        break;
        case '2':
            c = new Generico();
        break;
        case '3':
            c = new Visor();
        break;
        case '4':
            c = new Operador();
        break;
        default:
            c = NULL;
        break;
    }
*/
    if(c != NULL)
    {
        c->setSocket(socket);
    }

    return c;

}
