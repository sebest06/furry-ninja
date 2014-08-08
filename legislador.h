#ifndef LEGISLADOR_H
#define LEGISLADOR_H

#define ProtocoloSize 2
enum OpcionVoto{
    Abstenido = 0,
    Positivo = 0b0001,
    Negativo = 0b0010
};

enum Controles{
    votacion = 1,
    bloquearSillon = 4,
    bloquearId = 8,
    bloquearTodo = 12,
    borrarPedidoPalabra = 16
};

struct estadoBanca{
    unsigned char bioID:8;
    unsigned char sillon:1;
    unsigned char pidePalabra:1;
    unsigned char microfono:1;
    unsigned char voto:2;
    unsigned char reservado:3;
};


class Legislador
{
    public:
        Legislador();
        virtual ~Legislador();
        void setBioId(int id){diputado.bioID = id;}
        void setSillon(bool sillon){diputado.sillon = sillon;}
        void setPidePalabra(bool pp){diputado.pidePalabra = pp;}
        void setMicrofono(bool mic){diputado.microfono = mic;}
        void setVoto(OpcionVoto voto){diputado.voto = voto;}

        int getBioId(void){return diputado.bioID;}
        bool getSillon(void){return diputado.sillon;}
        bool getPidePalabra(void){return diputado.pidePalabra;}
        bool getMicrofono(void){return diputado.microfono;}
        unsigned char getVoto(void){return diputado.voto;}

        void saveDatos(estadoBanca unDiputado){diputado = unDiputado;}
        estadoBanca* loadDatos(void){return &diputado;}
        void setConnect(bool connect){isConnected = connect;}
        bool getConnect(){return isConnected;}

    protected:
    private:
//        void isConnected(bool connect);
        estadoBanca diputado;
        bool isConnected;
};

#endif // LEGISLADOR_H
