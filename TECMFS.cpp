//
// Created by Josue Chaves on 11/25/18.
//

#include "TECMFS.h"


TECMFS::TECMFS( int id) {

    this->id = id;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("/Users/d4n11083/Documents/CLion_Projects/DiskNode/configuracion/configuracion.xml");
    pugi::xml_node root = doc.document_element();

    this->ip        = root.child(("Node" + std::to_string(id)).c_str()).attribute("ip").value();
    this->pathDisco = root.child(("Node" + std::to_string(id)).c_str()).attribute("path").value();
    this->port      = root.child(("Node" + std::to_string(id)).c_str()).attribute("port").as_int();

    this->nodeCliente = new TECMFSNODE(sockaddr_in(), id, this->ip, this->port);

    std::cout << "TECMFS: " << "DiskNode" + std::to_string(id) << " creado." << std::endl;
}

TECMFS::~TECMFS() {
    nodeCliente->detener();
    std::cout << "DisckNode Desconectado " << std::endl;
}


void TECMFS::esperaPeticion() {
    nodeCliente->iniciar();

    char* buffer = (char *) calloc(1, 1024);
    char* bufferEnvio = (char *) calloc(1, 1024);
    int Solicitud = 0;

    while(1){

        memset(buffer,0,1024);
        memset(bufferEnvio,0,1024);

        json solicitudCliente = json::parse( nodeCliente->recibeDatos(15) ); //Le llega la solicitud del Cliente
        Solicitud = solicitudCliente["Solicitud"];

//        strcpy(bufferEnvio,"**Procesando Solicitud**\n");
//        nodeCliente->enviarDatos(bufferEnvio);

        memset(buffer,0,1024);
        memset(bufferEnvio,0,1024);


        if( Solicitud == 99 ){
            nodeCliente->detener();
            break;
        }

        manejoSolicitud( Solicitud );
        std::cout << "Ya se manejó la solicitud" << std::endl;


    }
}


void TECMFS::recibirVideo() {



}


void TECMFS::manejoSolicitud(int solicitud) {
    std::cout << "**Solicitud: "<< solicitud << "**" << std::endl;
    switch ( solicitud ){
        case 1: {
            nodeCliente->recibirVideo(this->pathDisco);
            break;
        }

        case 2:{
            nodeCliente->subirVideo(this->pathDisco);
            break;
        }
    }

}


