#ifndef CLIENTE_H
#define CLIENTE_H
#include <string>


class Cliente
{
    public:
        Cliente(){};
        virtual int getSocket()=0;
        virtual void setSocket(int socket)=0;
        virtual void setName(std::string name)=0;
        virtual std::string getName(void)=0;
        virtual void procesarDatos(char* datos, int len)=0;
        virtual void setId(int id)=0;
        virtual int getId(void)=0;
        virtual std::string getStateID() const = 0;
        virtual ~Cliente(){};
    protected:
    private:
};

#endif // CLIENTE_H
