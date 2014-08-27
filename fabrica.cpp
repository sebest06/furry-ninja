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
    if(pch != NULL)
    {
        if(strcmp(pch,"nick") == 0)
        {
            char* arg1;
            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return NULL;}
            arg1 = pch;

            c = new Generico();
            //pch = strtok (NULL," ,.-/\r\n");
            c->setName(arg1);
            c->setId(m_Ukids);
            m_Ukids++;

        }
        else if(strcmp(pch,"banca") == 0)
        {
            char* arg1;
            int arg2;

            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return NULL;}
            arg1 = pch;
            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return NULL;}
            arg2 = atoi(pch);

            c = new Banca();
            //pch = strtok (NULL," ,.-/\r\n");
            c->setName(arg1);
            //pch = strtok (NULL," ,.-/\r\n");
            c->setId(arg2);
        }
        else if(strcmp(pch,"operador") == 0)
        {
            char* arg1;
            int arg2;

            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return NULL;}
            arg1 = pch;
            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return NULL;}
            arg2 = atoi(pch);

            c = new Operador();
            //pch = strtok (NULL," ,.-/\r\n");
            c->setName(arg1);
            //pch = strtok (NULL," ,.-/\r\n");
            c->setId(arg2);
        }
        else
        {
            c = NULL;
        }
    }
    else
    {
        c = NULL;
    }

    if(c != NULL)
    {
        c->setSocket(socket);
    }

    return c;

}
