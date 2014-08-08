#include "almacen.h"

Almacen* Almacen::s_pInstance = 0;

std::vector<Cliente*> Almacen::clientes;

Almacen::Almacen()
{
    //ctor
}

Almacen::~Almacen()
{
    //dtor
}
