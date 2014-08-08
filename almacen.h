#ifndef ALMACEN_H
#define ALMACEN_H

#include <vector>
#include "cliente.h"

class Almacen
{
    public:
        static Almacen* Instance()
        {
            if(s_pInstance == 0)
            {
                s_pInstance = new Almacen();
                return s_pInstance;
            }
            return s_pInstance;
        }

        virtual ~Almacen();
        static std::vector<Cliente*> clientes;
    protected:
    private:
        Almacen();
        static Almacen* s_pInstance;


};
typedef Almacen ElAlmacen;

#endif // ALMACEN_H
