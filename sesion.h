#ifndef SESION_H
#define SESION_H
#include <vector>
#include <string>
#include "legislador.h"

class Sesion
{
    public:

        static Sesion* Instance()
        {
            if(s_pInstance == 0)
            {
                s_pInstance = new Sesion();
                return s_pInstance;
            }
            return s_pInstance;
        }
        virtual ~Sesion();
        void setAbrirVotacion(bool abrir);
        void setBloquearSillon(bool bloquear, int banca);
        void setBloquearId(int id, int banca);
        void setBloquearTodo(int id,int banca);
        void setBorrarPedidoPalabra(int banca);
        void setDatosBanca(Legislador MiLegislador, int indice);

        void getBancaInfo(int banca, int op);
        void getQuorum(int op);

        void getVotantesPositivos(int op);
        void getVotantesNegativos(int op);
        void getVotantesAbtenidos(int op);

    protected:
    private:
        void sendToAllBancas(char* message, int len);
        void sendToBanca(char* message, int len, int banca);
        void respondToOp(char* message, int len, int op);
        bool m_votacion;
        Sesion();
        static Sesion* s_pInstance;
        Legislador m_pBancas[51];
        std::vector<Legislador*> m_pOrdenPedidoPalabras;
        std::vector<Legislador*> m_pVotosPositivos;
        std::vector<Legislador*> m_pVotosNegativos;
        std::vector<Legislador*> m_pVotosAbstenido;



};
typedef Sesion LaSesion;

#endif // SESION_H
