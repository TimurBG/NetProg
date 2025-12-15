#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // 1. Создание TCP-сокета
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return 1;
    }

    // 2. Адрес сервера echo (172.16.40.1:7)
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7);  // Порт echo
    server_addr.sin_addr.s_addr = inet_addr("172.16.40.1");

    // 3. Установка соединения
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(sock);
        return 1;
    }

    std::cout << "Connected to echo server. Type messages (type 'exit' to quit):" << std::endl;

    char buffer[256];
    while (true) {
        std::cout << "> ";
        std::cin.getline(buffer, sizeof(buffer));

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // 4. Отправка сообщения
        if (send(sock, buffer, strlen(buffer), 0) == -1) {
            perror("send");
            break;
        }

        // 5. Приём эхо-ответа
        memset(buffer, 0, sizeof(buffer));
        ssize_t received = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (received == -1) {
            perror("recv");
            break;
        } else if (received == 0) {
            std::cout << "Server closed connection." << std::endl;
            break;
        }

        buffer[received] = '\0';
        std::cout << "Echo: " << buffer << std::endl;
    }

    // 6. Закрытие сокета
    close(sock);
    return 0;
}
