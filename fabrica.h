#ifndef FABRICA_H
#define FABRICA_H
#include "cliente.h"

class Fabrica
{
    public:
        static Fabrica* Instance()
        {
            if(s_pInstance == 0)
            {
                s_pInstance = new Fabrica();
                return s_pInstance;
            }
            return s_pInstance;
        }
        virtual ~Fabrica();

        Cliente* fabricar(char* buffer, int len, int socket);

    protected:
    private:
        Fabrica();
        static Fabrica* s_pInstance;
        long int m_Ukids;

};
typedef Fabrica LaFabrica;
#endif // FABRICA_H
