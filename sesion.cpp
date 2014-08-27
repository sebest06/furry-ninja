#include "servidor.h"
#include "sesion.h"
#include "legislador.h"
#include "almacen.h"

Sesion* Sesion::s_pInstance = 0;
Sesion::Sesion()
{
    //ctor
        m_pVotosPositivos.clear();
        m_pVotosNegativos.clear();
        m_pVotosAbstenido.clear();
        m_pOrdenPedidoPalabras.clear();

        for(unsigned int i=0; i<(sizeof(m_pBancas)/sizeof(m_pBancas[0])); i++)
            {
            m_pBancas[i].setBioId(0);
            m_pBancas[i].setSillon(0);
            m_pBancas[i].setPidePalabra(0);
            m_pBancas[i].setMicrofono(0);
            m_pBancas[i].setVoto(Abstenido);
        }
}

Sesion::~Sesion()
{
    //dtor
}

void Sesion::setAbrirVotacion(bool abrir)
{

    char buff[ProtocoloSize];

    if(abrir == true)
    {
        //Enviar a todas las bancas abrir votacion
        buff[0] = votacion;
        buff[1] = true;
        sendToAllBancas(buff,ProtocoloSize);
    }
    else
    {

        m_pVotosPositivos.clear();
        m_pVotosNegativos.clear();
        m_pVotosAbstenido.clear();

        for(unsigned int i=0; i<(sizeof(m_pBancas)/sizeof(m_pBancas[0])); i++)
        {
            if((m_pBancas[i].getSillon())&&(m_pBancas[i].getBioId()))
            {
                switch(m_pBancas[i].getVoto())
                {
                    case Positivo:
                        m_pVotosPositivos.push_back(&m_pBancas[i]);
                    break;
                    case Negativo:
                        m_pVotosNegativos.push_back(&m_pBancas[i]);
                        break;
                    case Abstenido:
                        m_pVotosAbstenido.push_back(&m_pBancas[i]);
                        break;
                }
            }
        }
        buff[0] = votacion;
        buff[1] = false;
        sendToAllBancas(buff,ProtocoloSize);
    }


}

void Sesion::setBloquearSillon(bool bloquear, int banca)
{
    char buff[ProtocoloSize];
    buff[0] = bloquearSillon;
    buff[1] = bloquear;
    sendToBanca(buff,ProtocoloSize,banca);
}

void Sesion::setBloquearId(int id, int banca)
{
    char buff[ProtocoloSize];
    buff[0] = bloquearId;
    buff[1] = id;
    sendToBanca(buff,ProtocoloSize,banca);
}

void Sesion::setBloquearTodo(int id, int banca)
{
    char buff[ProtocoloSize];
    buff[0] = bloquearTodo;
    buff[1] = id;
    sendToBanca(buff,ProtocoloSize,banca);
}

void Sesion::setBorrarPedidoPalabra(int banca)
{
    char buff[ProtocoloSize];
    buff[0] = borrarPedidoPalabra;
    buff[1] = true;
    sendToBanca(buff,ProtocoloSize,banca);
}

void Sesion::sendToAllBancas(char* message, int len)
{
  int n;

    for(size_t i=0; i<ElAlmacen::Instance()->clientes.size(); i++)
    {
        if(ElAlmacen::Instance()->clientes[i]->getStateID() == "BANCA")
        {
            n = TheServidor::Instance()->sendData(ElAlmacen::Instance()->clientes[i]->getSocket(),message, len, 0);
            std::cout << n << " bytes sent." << std::endl;
        }
    }

}

void Sesion::getBancaInfo(int banca, int op)
{
  char buffer[100];
  int cx;
  cx = snprintf ( buffer, 100, "Sillo: %d, ID: %d, Voto: %d, Mic: %d, PP: %d\n", \
                 m_pBancas[banca].getSillon(), \
                 m_pBancas[banca].getBioId(), \
                 m_pBancas[banca].getVoto(), \
                 m_pBancas[banca].getMicrofono(), \
                 m_pBancas[banca].getPidePalabra());

    respondToOp(buffer,cx,op);

}

void Sesion::getQuorum(int op)
{
    int quorum;
    char salida[10];
    int cx;
    quorum = 0;
    for(unsigned int i=0; i<(sizeof(m_pBancas)/sizeof(m_pBancas[0])); i++)
    {
        if(m_pBancas[i].getSillon())
        {
            quorum++;
        }
    }
    //salida = std::to_string(quorum);
    cx = snprintf(salida,10,"%d\n",quorum);
    respondToOp(salida,cx,op);
}

void Sesion::respondToOp(char* message, int len, int op)
{
  int n;

    for(size_t i=0; i<ElAlmacen::Instance()->clientes.size(); i++)
    {
        if((ElAlmacen::Instance()->clientes[i]->getStateID() == "OPERADOR")&&(ElAlmacen::Instance()->clientes[i]->getId() == op))
        {
            n = TheServidor::Instance()->sendData(ElAlmacen::Instance()->clientes[i]->getSocket(),message, len, 0);
            std::cout << n << " bytes sent." << std::endl;
        }
    }
}

void Sesion::sendToBanca(char* message, int len, int banca)
{
  int n;

    for(size_t i=0; i<ElAlmacen::Instance()->clientes.size(); i++)
    {
        if((ElAlmacen::Instance()->clientes[i]->getStateID() == "BANCA")&&(ElAlmacen::Instance()->clientes[i]->getId() == banca))
        {
            n = TheServidor::Instance()->sendData(ElAlmacen::Instance()->clientes[i]->getSocket(),message, len, 0);
            std::cout << n << " bytes sent." << std::endl;
        }
    }
}

void Sesion::setDatosBanca(Legislador MiLegislador, int indice)
{
    MiLegislador.setConnect(true);  // tengo que pensar que hacer cuando se desconecte alguna banca
    m_pBancas[indice] = MiLegislador;
    manejarPedidoPalabra(indice);
}

void Sesion::manejarPedidoPalabra(int indice)
{
    bool yaEstaAnotado = false;
    if((m_pBancas[indice].getPidePalabra()) && (m_pBancas[indice].getBioId() != 0))
    {
        for(unsigned int i=0; i< m_pOrdenPedidoPalabras.size() ; i++)
        {
            if(m_pOrdenPedidoPalabras[i]->getBioId() == m_pBancas[indice].getBioId())
            {
                yaEstaAnotado = true;
            }
        }
        if(!yaEstaAnotado)
        {
            m_pOrdenPedidoPalabras.push_back(&m_pBancas[indice]);
        }
    }

}


void Sesion::getVotantesPositivos(int op)
{
    char buffer[100];

    for(unsigned int i=0; i< m_pVotosPositivos.size() ; i++)
    {
        buffer[i] = m_pVotosPositivos[i]->getBioId();
        printf("%d,",buffer[i]);
    }
    printf("\n");
    respondToOp(buffer,m_pVotosPositivos.size(),op);

}

void Sesion::getVotantesNegativos(int op)
{
    char buffer[100];

    for(unsigned int i=0; i< m_pVotosNegativos.size() ; i++)
    {
        buffer[i] = m_pVotosNegativos[i]->getBioId();
        printf("%d,",buffer[i]);
    }
    printf("\n");
    respondToOp(buffer,m_pVotosNegativos.size(),op);
}

void Sesion::getVotantesAbtenidos(int op)
{
    char buffer[100];

    for(unsigned int i=0; i< m_pVotosAbstenido.size() ; i++)
    {
        buffer[i] = m_pVotosAbstenido[i]->getBioId();
        printf("%d,",buffer[i]);
    }
    printf("\n");
    respondToOp(buffer,m_pVotosAbstenido.size(),op);
}

void Sesion::getListaPalabra(int op)
{
    char buffer[100];

    for(unsigned int i=0; i< m_pOrdenPedidoPalabras.size() ; i++)
    {
        buffer[i] = m_pOrdenPedidoPalabras[i]->getBioId();
        printf("%d,",(int)buffer[i]);
    }
    printf("\n");
    respondToOp(buffer,m_pOrdenPedidoPalabras.size(),op);
}


