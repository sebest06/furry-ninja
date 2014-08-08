#include "operador.h"
#include "legislador.h"
#include "almacen.h"
#include "servidor.h"
#include "sesion.h"


const std::string Operador::s_type = "OPERADOR";

Operador::Operador()
{

}

Operador::~Operador()
{

}

void Operador::procesarDatos(char* buffer, int len)
{
    char *pch;
    pch = strtok (buffer," ,.-/\r\n");

    if(strcmp(pch,"abrirVotacion") == 0)
    {
        LaSesion::Instance()->setAbrirVotacion(true);
    }
    else if(strcmp(pch,"cerrarVotacion") == 0)
    {
        LaSesion::Instance()->setAbrirVotacion(false);
    }
    else if(strcmp(pch,"bloquearSillon") == 0)
    {
        char bloquear = atoi(strtok (NULL," ,.-/\r\n"));
        LaSesion::Instance()->setBloquearSillon(bloquear,atoi(strtok (NULL," ,.-/\r\n")));
    }
    else if(strcmp(pch,"bloquearId") == 0)
    {
        //Enviar a todas las bancas cerrar votacion
        char bloquear = atoi(strtok (NULL," ,.-/\r\n"));
        LaSesion::Instance()->setBloquearId(bloquear,atoi(strtok (NULL," ,.-/\r\n")));
    }
    else if(strcmp(pch,"bloquearTodo") == 0)
    {
        //Enviar a todas las bancas cerrar votacion
        char bloquear = atoi(strtok (NULL," ,.-/\r\n"));
        LaSesion::Instance()->setBloquearTodo(bloquear,atoi(strtok (NULL," ,.-/\r\n")));
    }
    else if(strcmp(pch,"borrarPedidoPalabra") == 0)
    {
        //Enviar a todas las bancas cerrar votacion
        LaSesion::Instance()->setBorrarPedidoPalabra(atoi(strtok (NULL," ,.-/\r\n")));
    }
    else if(strcmp(pch,"infoBanca") == 0)
    {
        int banca = atoi(strtok (NULL," ,.-/\r\n"));
        LaSesion::Instance()->getBancaInfo(banca,getId());
    }
    else if(strcmp(pch,"quorum") == 0)
    {
        LaSesion::Instance()->getQuorum(getId());
    }
    else if(strcmp(pch,"votosPositivos") == 0)
    {
        LaSesion::Instance()->getVotantesPositivos(getId());
    }
    else if(strcmp(pch,"votosNegativos") == 0)
    {
        LaSesion::Instance()->getVotantesNegativos(getId());
    }
    else if(strcmp(pch,"votosAbstenidos") == 0)
    {
        LaSesion::Instance()->getVotantesAbtenidos(getId());
    }

}
