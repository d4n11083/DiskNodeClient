//
// Created by Josue Chaves on 11/25/18.
//

#ifndef DISKNODE_TECMFS_H
#define DISKNODE_TECMFS_H

#include "TECMFSNODECliente.h"
#include "PUGIXML/pugixml.hpp"
#include "JSON/json.hpp"

using json = nlohmann::json;

class TECMFS {
private:
    TECMFSNODE *nodeCliente = nullptr;

    std::string ip = "";
    std::string pathDisco = "";
    int port = 0;
    int id = 0;

public:
    TECMFS( int id);
    ~TECMFS();

    void esperaPeticion(  );

    void manejoSolicitud( int solicitud );
    void recibirVideo();

    bool enviarDatos(std::string data);
    std::string recibeDatos(int size);





};


#endif //DISKNODE_TECMFS_H
