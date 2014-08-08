#ifndef OPERADOR_H
#define OPERADOR_H
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "cliente.h"


class Operador : public Cliente
{
    public:
        Operador();
        virtual ~Operador();
        virtual int getSocket(){return m_socket;}
        virtual void setSocket(int socket){m_socket = socket;}
        virtual void setName(std::string name){m_name = name;}
        virtual std::string getName(void){return m_name;}
        virtual void procesarDatos(char* datos, int len);
        virtual void setId(int id){m_id = id;}
        virtual int getId(void){return m_id;}
        virtual std::string getStateID() const {return s_type;}

    protected:
    private:
        static const std::string s_type;
        std::string m_name;
        int m_id;
        bool m_registrada;
        int m_banca;
        int m_socket;
};

#endif // OPERADOR_H
