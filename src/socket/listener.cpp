//
// Created by 파란눈탱이 on 2021/06/24.
//

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <poll.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <thread>
#include "listener.h"
#include "../http/httprequestparser.h"
#include "../http/httpheader.h"


#define OPEN_MAX 600
#define BUFFER_SIZE 1024

void Listener::start() {
    int server_sockfd;
    int client_sockfd;
    int sockfd;
    struct sockaddr_in clientaddr;
    struct sockaddr_in serveraddr;

    char buf[255];
    char line[255];

    struct pollfd client[OPEN_MAX];

    if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "error " << std::endl;
        return;
    }
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(80);

    int state = bind(server_sockfd, (struct  sockaddr *)&serveraddr, sizeof(serveraddr));

    if (state == -1) {
        std::cout << "fail to bind" << std::endl;
        return;
    }

    state = listen(server_sockfd, 5);
    if (state == -1) {
        std::cout << "fail to listen" << std::endl;
    }

    client[0].fd = server_sockfd;
    client[0].events = POLLIN;

    for(int i = 1; i < OPEN_MAX; i++) {
        client[i].fd = -1;
    }

    char buffer[BUFFER_SIZE];

    while(1) {
        int result = poll(client, OPEN_MAX, -1);
        if (result > 0) {
            if (client[0].revents == POLLIN) {
                socklen_t size = sizeof(clientaddr);
                client_sockfd = accept(server_sockfd, (struct sockaddr *)&clientaddr, &size);
                for (int i = 1; i < OPEN_MAX; i++) {
                    if(client[i].fd == -1) {
                        client[i].fd = client_sockfd;
                        client[i].events = POLLIN;
                        client[i].revents = 0;
                        break;
                    }
                }
            }
            int len = 0;
            for(int i = 1; i < OPEN_MAX; i++) {
                switch (client[i].revents) {
                    case 0:
                        break;
                    case POLLIN:
                        memset(buffer, 0, sizeof buffer);
                        len = read(client[i].fd, buffer, BUFFER_SIZE);
                        buffer[len] = '\0';
                       parse(client[i].fd, buffer, len);
                         break;
                    default: {
                        close(client[i].fd);
                        client[i].fd = -1;
                        client[i].revents = 0;
                    }
                }
            }
        }
    }
    close(server_sockfd);
}

void Listener::handle(int fd) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof buffer);
    int len = read(fd, buffer, BUFFER_SIZE);
    buffer[len] = '\0';
    parse(fd, buffer, len);
}

void Listener::parse(int fd, char* data, int len) {
    HttpRequestParser parser;
    HttpRequest request;
    parser.parse(data, len, request);

//
//    std::cout << "method : " << request.getMethod() << std::endl;
//    std::cout << "uri : " << request.getUri() << std::endl;
//    std::cout << "query string : " << request.getQueryString() << std::endl;
//    std::cout << "version : " << request.getVersion() << std::endl;
//
//    auto names = request.getHeader()->getHeaderNames();
//    for_each(names.begin(), names.end(), [&](auto name) {
//        std::cout << name << " --> " << request.getHeader()->getHeader(name) << std::endl;
//    });
    sendfile(fd, request.getUri());
}

void Listener::sendfile(int fd, const std::string& path) {
    FILE *fp;
    std::string fullpath = "/Users/blueeyes/IdeaProjects/wafull-sattang-all/sattang-demo/src/test/resources";
    fullpath += path;
    fp = fopen(fullpath.c_str(), "rb");
    if (fp == NULL){
        printf("File not Exist");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char buffer[1024 * 32];
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "HTTP/1.1 200 OK\r\nContent-Length : %d\r\nContent-Type: text/html\r\n\r\n", file_size);
    int sendBytes = send(fd, buffer, strlen(buffer), 0);
    while ((sendBytes = fread(buffer, sizeof(char), sizeof(buffer), fp))>0) {
        send(fd, buffer, sendBytes, 0);
    }
    fclose(fp);
}