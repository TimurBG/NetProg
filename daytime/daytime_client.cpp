#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // 1. Создание UDP-сокета
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        perror("socket");
        return 1;
    }

    // 2. Адрес сервера daytime (172.16.40.1:13)
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13);  // Порт daytime
    server_addr.sin_addr.s_addr = inet_addr("172.16.40.1");

    // 3. Отправка пустого пакета
    if (sendto(sock, "", 0, 0, 
               (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("sendto");
        close(sock);
        return 1;
    }

    // 4. Приём ответа
    char buffer[256];
    socklen_t addr_len = sizeof(server_addr);
    ssize_t received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                                (struct sockaddr*)&server_addr, &addr_len);
    if (received == -1) {
        perror("recvfrom");
        close(sock);
        return 1;
    }

    // 5. Вывод времени
    buffer[received] = '\0';
    std::cout << "Daytime from server: " << buffer;

    // 6. Закрытие сокета
    close(sock);
    return 0;
}
