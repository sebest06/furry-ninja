#include "banca.h"
#include "almacen.h"
#include "servidor.h"
#include "sesion.h"

const std::string Banca::s_type = "BANCA";

Banca::Banca()
{
    MiLegislador = new Legislador();
}

Banca::~Banca()
{

}

void Banca::procesarDatos(char* buffer, int len)
{

    std::memcpy(MiLegislador->loadDatos(), buffer , sizeof(estadoBanca));

    printf("Identificacion: %d, Sillon: %d, Microfono: %d, PidePalabra: %d, Voto: %d\n",\
            MiLegislador->getBioId(),MiLegislador->getSillon(),MiLegislador->getMicrofono(),\
           MiLegislador->getPidePalabra(),MiLegislador->getVoto()\
           );

    printf("Mi ID de conexion es: %d\n",getId());
    LaSesion::Instance()->setDatosBanca(*MiLegislador,getId());

    //Ahora tendria que empilarlo en un almacen
}
