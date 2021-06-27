//
// Created by 파란눈탱이 on 2021/06/24.
//

#ifndef CONFIG_LISTENER_H
#define CONFIG_LISTENER_H


class Listener {
public:
    void start();
    void handle(int fd);
    void parse(int fd, char* data, int len);
    void sendfile(int fd, const std::string& path);
};


#endif //CONFIG_LISTENER_H
