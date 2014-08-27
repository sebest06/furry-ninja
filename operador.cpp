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
    if(pch != NULL)
    {
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
            int arg1;
            int arg2;

            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return;}
            arg1 = atoi(pch);
            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return;}
            arg2 = atoi(pch);
            LaSesion::Instance()->setBloquearSillon(arg1,arg2);
            //char bloquear = atoi(strtok (NULL," ,.-/\r\n"));
            //LaSesion::Instance()->setBloquearSillon(bloquear,atoi(strtok (NULL," ,.-/\r\n")));
        }
        else if(strcmp(pch,"bloquearId") == 0)
        {
            //Enviar a todas las bancas cerrar votacion
            int arg1;
            int arg2;

            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return;}
            arg1 = atoi(pch);
            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return;}
            arg2 = atoi(pch);
            LaSesion::Instance()->setBloquearId(arg1,arg2);
            //char bloquear = atoi(strtok (NULL," ,.-/\r\n"));
            //LaSesion::Instance()->setBloquearId(bloquear,atoi(strtok (NULL," ,.-/\r\n")));
        }
        else if(strcmp(pch,"bloquearTodo") == 0)
        {
            int arg1;
            int arg2;

            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return;}
            arg1 = atoi(pch);
            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return;}
            arg2 = atoi(pch);
            LaSesion::Instance()->setBloquearTodo(arg1,arg2);
            //char bloquear = atoi(strtok (NULL," ,.-/\r\n"));
            //LaSesion::Instance()->setBloquearTodo(bloquear,atoi(strtok (NULL," ,.-/\r\n")));
        }
        else if(strcmp(pch,"borrarPedidoPalabra") == 0)
        {
            int arg1;

            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return;}
            arg1 = atoi(pch);
            LaSesion::Instance()->setBorrarPedidoPalabra(arg1);
            //Enviar a todas las bancas cerrar votacion
            //LaSesion::Instance()->setBorrarPedidoPalabra(atoi(strtok (NULL," ,.-/\r\n")));
        }
        else if(strcmp(pch,"infoBanca") == 0)
        {
            int arg1;

            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return;}
            arg1 = atoi(pch);

            LaSesion::Instance()->getBancaInfo(arg1,getId());
            //int banca = atoi(strtok (NULL," ,.-/\r\n"));
            //LaSesion::Instance()->getBancaInfo(banca,getId());
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
        else if(strcmp(pch,"listaPalabra") == 0)
        {
            LaSesion::Instance()->getListaPalabra(getId());
        }
    }
}
