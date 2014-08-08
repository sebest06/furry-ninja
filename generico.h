#ifndef GENERICO_H
#define GENERICO_H

#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "cliente.h"

class Generico : public Cliente
{
    public:
        Generico();
        virtual ~Generico();
        virtual int getSocket(){return m_socket;}
        virtual void setSocket(int socket){m_socket = socket;}
        virtual void setName(std::string name){m_name = name;}
        virtual std::string getName(void){return m_name;}
        virtual void procesarDatos(char* buffer, int len);
        virtual void setId(int id){m_id = id;}
        virtual int getId(void){return m_id;}
        virtual std::string getStateID() const {return s_type;}

    protected:
    private:
        void sendToAll(char* message, int len);
        static const std::string s_type;
        std::string m_name;
        int m_id;
        bool m_registrada;
        int m_banca;
        int m_socket;
};

#endif // GENERICO_H
