//
// Created by Josue Chaves on 11/25/18.
//

#include "TECMFSNODECliente.h"


TECMFSNODE::TECMFSNODE( sockaddr_in server_addr,int id, std::string  ip, int puerto  ) {
    this->server_addr = server_addr;
    this->id = id;
    this->DireccionIP = ip;
    this->Puerto = puerto;
    salir = false;

}

void TECMFSNODE::detener() {
    enviarSolicitud(99);
    salir = true;
    shutdown(client_socket,SHUT_RDWR);
}

void TECMFSNODE::iniciar() {
    client_socket = socket(AF_INET,SOCK_STREAM,0);
    if(conectar()){
        std::cout <<  "Disk Node Conectado al Cliente" << std::endl;
    }else{
        std::cout << "Disk Node no se pudo conectar al Servidor" << std::endl;
    }
}


bool TECMFSNODE::conectar(){
    if(client_socket == -1){
        perror("No se pudo conectar el socket");

    }
    std::cout << "Socket creado \n" << std::endl;

    if( inet_addr(DireccionIP.c_str()) == -1){
        struct hostent *he;
        struct in_addr **addr_list;

        if( (he = gethostbyname(DireccionIP.c_str()) ) == NULL){
            herror("gethostbyname");
            std::cout << "No se pudo arreglar el HostName\n";
            return false;
        }

        addr_list = ( struct in_addr ** ) he->h_addr_list;
        for(int i = 0; addr_list[i] != NULL; i++ ){
            server_addr.sin_addr = *addr_list[i];
            std::cout << DireccionIP<< "Resolved to " << inet_ntoa(*addr_list[i])<<std::endl;
            break;
        }
    }
    else{
        server_addr.sin_addr.s_addr = inet_addr( DireccionIP.c_str() );
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons( PORT );

    if ( connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ){
        perror( "Error: conexion fallida" );
        return 1;
    }

    std::string mensajeConfirmacion = "->Copiado";
    enviarDatos(mensajeConfirmacion);
    std::cout << recibeDatos(50) << std::endl;
    std::cout << "Conexión Realizada\n"<< std::endl;

    return true;
}

bool TECMFSNODE::enviarDatos(std::string data) {
    if(send(client_socket,data.c_str(),strlen(data.c_str() ),0) < 0){
        perror("Error envio de datos fallidos");
        return false;
    }
    std::cout << "Datos enviados: "<< data << std::endl;
    return true;
}

std::string TECMFSNODE::recibeDatos(int size) {
    char buffer[size];
    std::string reply;

    if( recv( client_socket, buffer, size, 0 ) < 0 ){
        //puts("Entrega Fallida");
        std::cout << "Entrega Fallida" << std::endl;
    }
    reply = buffer;
    return reply;
}

void TECMFSNODE::enviarSolicitud(int numSolicitud) {
    //Json con la solicitud uno que es subir un video
    json solicitud;
    solicitud["Solicitud"] = numSolicitud;
    std::string stringEnviar = solicitud.dump();
    char *mensajejsonchar = &stringEnviar[0u];
    enviarDatos(mensajejsonchar); //Envia Json con solicitud
}

