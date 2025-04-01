#include "mainInclude.h"
#include <ws2tcpip.h>
#pragma once

class network {
public:
    WSADATA wsaData;
    SOCKET Socket;
    SOCKET clientSocket; // Добавляем сокет для клиента
    sockaddr_in serverAddr;

    ~network() {
        closesocket(Socket);
        WSACleanup();
    }

    network() {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Ошибка инициализации Winsock!" << std::endl;
            return;
        }

        Socket = socket(AF_INET, SOCK_STREAM, 0);
        if (Socket == INVALID_SOCKET) {
            std::cerr << "Ошибка создания сокета!" << std::endl;
            WSACleanup();
            return;
        }
    }

    bool createServer() {
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(60000);

        if (bind(Socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Ошибка привязки сокета!" << std::endl;
            closesocket(Socket);
            WSACleanup();
            return false;
        }

        std::cout << "Сервер запущен на порту 60000\n";
        std::cout << serverAddr.sin_addr.s_addr << "\n";
        return true;
    }

    std::string listenSocket() {
        std::string temp;
        if (listen(Socket, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Ошибка прослушивания порта!" << std::endl;
            closesocket(Socket);
            WSACleanup();
            return temp;
        }

        std::cout << "Сервер ожидает подключения..." << std::endl;

        clientSocket = accept(Socket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Ошибка принятия подключения!" << std::endl;
            closesocket(Socket);
            WSACleanup();
            return temp;
        }

        std::cout << "Клиент подключился!" << std::endl;

        char buffer[512];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            std::cout << "Получено: " << std::string(buffer, bytesReceived) << std::endl;
        }

        return temp;
    }

    std::string sendClient(std::string data) {
        if (clientSocket != INVALID_SOCKET) {
            send(clientSocket, data.c_str(), data.size(), 0);
        }
        char buffer[512];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            std::cout << "Получено: " << std::string(buffer, bytesReceived) << std::endl;
            return std::string(buffer, bytesReceived);
        }

        return ""; 
    }

    bool connectServer(int port, std::string ip) {
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(60000);

        // Заменяем INADDR_ANY на конкретный IP
        if (inet_pton(AF_INET,ip.c_str(), &serverAddr.sin_addr) <= 0) {
            std::cerr << "Ошибка преобразования IP-адреса!" << std::endl;
            return false;
        }

        if (connect(Socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Ошибка подключения к серверу!" << std::endl;
            closesocket(Socket);
            WSACleanup();
            return false;
        }

        std::cout << "Подключение к серверу успешно!\n";
        return true;
    }

    std::string sendToServer(std::string data) {
        const char* message = data.c_str();
        send(Socket, message, strlen(message), 0);

        char buffer[512];
        int bytesReceived = recv(Socket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            std::cout << "Ответ от сервера: " << std::string(buffer, bytesReceived) << std::endl;
            return std::string(buffer, bytesReceived);
        }
        return "";
    }
};