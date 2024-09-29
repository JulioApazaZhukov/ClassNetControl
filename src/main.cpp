#include <iostream>
#include <string>
#include <winsock2.h>
#include "..\lib\include\windivert.h"

#pragma comment(lib, "ws2_32.lib")

#define MAXBUF 0xFFFF  // Tamaño máximo del paquete

// Función para extraer el dominio de un paquete DNS
std::string extractDomainFromDNS(const char* packet, UINT packetLen) {
    if (packetLen < sizeof(WINDIVERT_IPHDR) + sizeof(WINDIVERT_UDPHDR) + 12) {
        return "";  // Paquete demasiado corto para contener un nombre de dominio
    }

    const unsigned char* dnsPacket = (const unsigned char*)(packet + sizeof(WINDIVERT_IPHDR) + sizeof(WINDIVERT_UDPHDR));
    std::string domain;
    int length = dnsPacket[12];

    while (length > 0) {
        if (domain.length() > 0) {
            domain += '.';
        }

        domain.append(reinterpret_cast<const char*>(dnsPacket + 13), length);
        dnsPacket += length + 1;
        length = *dnsPacket;
    }

    return domain;
}

int main() {
    // Abrir el manejador WinDivert para capturar tráfico DNS (UDP en puerto 53)
    HANDLE handle = WinDivertOpen("udp and dst port 53", WINDIVERT_LAYER_NETWORK, 0, 0);
    if (handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Error al abrir el dispositivo WinDivert: " << GetLastError() << std::endl;
        return 1;
    }

    WINDIVERT_ADDRESS addr;   // Estructura para almacenar la dirección del paquete
    char packet[MAXBUF];      // Búfer para almacenar los paquetes interceptados
    UINT packetLen;           // Variable para almacenar el tamaño del paquete

    // Bucle principal para capturar paquetes
    while (true) {
        // Recibir el paquete con la dirección asociada
        if (!WinDivertRecv(handle, packet, sizeof(packet), &packetLen, &addr)) { // Corrección aquí
            std::cerr << "Error al recibir el paquete: " << GetLastError() << std::endl;
            continue;
        }

        // Extraer el dominio de la consulta DNS
        std::string domain = extractDomainFromDNS(packet, packetLen);
        if (!domain.empty()) {
            std::cout << "Consulta DNS: " << domain << std::endl;
        }

        // Reenviar el paquete sin modificarlo
        if (!WinDivertSend(handle, packet, packetLen, NULL, &addr)) { // Corrección aquí
            std::cerr << "Error al reenviar el paquete: " << GetLastError() << std::endl;
        }
    }

    WinDivertClose(handle);
    return 0;
}
