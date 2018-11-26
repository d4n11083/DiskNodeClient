//
// Created by Josue Chaves on 11/25/18.
//

#ifndef DISKNODE_TECMFSNODE_H
#define DISKNODE_TECMFSNODE_H

#include "JSON/json.hpp"
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <stdio.h>
#include <netdb.h>
#include "JSON/json.hpp"
#include "DEFINITIONS.h"



class TECMFSNODE {
private:
    bool salir;
    int client_socket = -1;
    struct sockaddr_in server_addr;
    socklen_t size;
    std::string DireccionIP = "";
    using json =  nlohmann::json;
    int Puerto = 0;
    int id = 0;

public:

    TECMFSNODE(sockaddr_in server_addr, int IdDiskNode, std::string ip, int puerto);
    ~TECMFSNODE();
    void iniciar();
    void ejecutar();
    void detener();
    void enviarSolicitud(int numSolicitud);

    bool conectar();
    bool enviarDatos(std::string data);
    std::string recibeDatos(int size);

    void subirVideo(std::string Path);
    void recibirVideo(std::string Path);


};


#endif //DISKNODE_TECMFSNODE_H
