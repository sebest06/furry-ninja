#include "legislador.h"

Legislador::Legislador()
{
    //ctor
    diputado.bioID = 0;
    diputado.microfono = 0;
    diputado.pidePalabra = 0;
    diputado.sillon = 0;
    diputado.voto = 0;
    isConnected = 0;
}

Legislador::~Legislador()
{
    //dtor
    isConnected = 0;
}
