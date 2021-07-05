#pragma once
//#include <string.h> // contains string functions
#include <stdint.h>
#include <stdlib.h> // this includes functions regarding memory allocation
#include <memory>
#include <cstring>
#include <iostream>
#include <atomic>
#include <thread>
#include <sys/types.h>
#include <stdio.h>
#include <vector>
#include <functional>
#include <exception>
#include <unistd.h> //contains various constants
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <sys/epoll.h> // for epoll_create1()


class TCPClientConnection
{
public:
    TCPClientConnection() = delete;
    TCPClientConnection( const TCPClientConnection &obj) = delete;
    TCPClientConnection(sockaddr c_addr, socklen_t a_len, int c_fd);
    ~TCPClientConnection();

    typedef std::function<void(std::vector<std::uint8_t> data)> ReceiveCallback_t;

    void send(void* data, uint32_t size);
    void disconnect();

    static constexpr std::uint16_t MAX_READ_LENGTH{1024};
private:

    void receiveListener();

    sockaddr client_address;
    socklen_t addr_len;
    int client_fd{0};
    int epoll_fd{0};
    std::atomic<bool> failed{false};
    std::atomic<bool> run_receive_thread{false};
    std::atomic<bool> connected{false};
    std::unique_ptr<std::thread> receive_thread;
    ReceiveCallback_t receive_callback{nullptr};


    //void readThread
};


class TCPServer
{
public:
    TCPServer() = delete;
    TCPServer(uint16_t port);
    virtual ~TCPServer();

    typedef std::function<void(std::shared_ptr<TCPClientConnection> client)> ConnectionCallback_t;
    void registerOnConnect(ConnectionCallback_t lambda);
    void closeServer();


    void startListening();
    
private:
    void setupServer(uint32_t bind_address, uint16_t port);
    void connectionListener();


    sockaddr_in ipOfServer{0,};
    int clint_listen_fd{0};
    int epoll_fd{0};
    std::atomic<bool> failed{false};
    std::atomic<bool> run_listen_thread{false};
    std::unique_ptr<std::thread> listen_thread;

    ConnectionCallback_t onConnectCallback{nullptr};

};

