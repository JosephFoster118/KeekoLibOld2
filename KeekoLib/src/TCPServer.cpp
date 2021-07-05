#include "TCPServer.h"


using std::cout;
using std::endl;


TCPClientConnection::TCPClientConnection(sockaddr c_addr, socklen_t a_len, int c_fd)
{
    client_address = c_addr;
    addr_len = a_len;
    client_fd = c_fd;
    receive_thread = std::make_unique<std::thread>([this]()
    {
        receiveListener();
    });
}

TCPClientConnection::~TCPClientConnection()
{
    run_receive_thread = false;
    if(client_fd != 0)
    {
        close(client_fd);
        std::cout << "CLOSED\n";
    }
    if(receive_thread != nullptr && receive_thread->joinable())
    {
        receive_thread->join();
    }
}


void TCPClientConnection::send(void* data, uint32_t size)
{
    write(client_fd, data, size);
}

void TCPClientConnection::disconnect()
{
    run_receive_thread = false;
}

void TCPClientConnection::receiveListener()
{
    epoll_fd = epoll_create1(0);
    if(epoll_fd == -1)
    {
        printf("Failed to create epoll file descriptor\n");
        return ;
    }

    printf("asfasf\n");
    int const MAX_EVENTS = 10;
    epoll_event ev, events[MAX_EVENTS];
    ev.events = EPOLLIN;
    ev.data.fd = client_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1)
    {
        printf("epoll_ctl: listen_sock");
        return;
    }
    run_receive_thread = true;
    connected = true;
    while(run_receive_thread)
    {
        cout << "In loop" << endl;
        bool first_message{true};
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, 1000);
        if (nfds == -1)
        {
            perror("epoll_wait");
            run_receive_thread = false;
            break;

        }
        for (int n = 0; n < nfds; n++)
        {
            if (events[n].data.fd == client_fd)
            {
                while(true)
                {
                    std::uint8_t read_data[MAX_READ_LENGTH]{0,};
                    std::uint16_t read_size = read(client_fd, read_data, MAX_READ_LENGTH);
                    if(read_size == -1)
                    {
                        std::cout << "Got -1\n";
                        run_receive_thread = false;
                        failed = true;
                        break;
                    }
                    else if(read_size == 0)
                    {
                        if(first_message)
                        {
                            run_receive_thread = false;
                        }
                        std::cout << "Got Empty\n";
                        break;
                    }
                    cout << read_size << endl;
                    //cout << "Client sent: \"" << read_data << "\"" << endl;
                    if(receive_callback != nullptr)
                    {
                        std::vector<std::uint8_t>(std::begin(read_data), std::begin(read_data) + read_size);
                        //receive_callback();
                    }
                    else
                    {
                        //todo: Queue events until callback is set
                    }
                    first_message = false;
                }
                
            }
        }
    }

    if(close(epoll_fd))
    {
        epoll_fd = 0;
        printf("Failed to close epoll file descriptor\n");
        return;
    }
    connected = false;

}




TCPServer::TCPServer(uint16_t port)
{
    setupServer(htonl(INADDR_ANY), port);
}

TCPServer::~TCPServer()
{
    run_listen_thread = false;
    if(clint_listen_fd != 0)
    {
        close(clint_listen_fd);
    }
    if(listen_thread != nullptr && listen_thread->joinable())
    {
        listen_thread->join();
    }
}

void TCPServer::setupServer(uint32_t bind_address, uint16_t port)
{
    clint_listen_fd = socket(AF_INET, SOCK_STREAM, 0); // creating socket
    if(clint_listen_fd == 0)
    {
        std::cout << "Fail to create socket!\n";
        failed = true;
        return;
    }
    ipOfServer.sin_family = AF_INET;
	ipOfServer.sin_addr.s_addr = bind_address;
    ipOfServer.sin_port = htons(port);
    timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    if (setsockopt(clint_listen_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
    {
        std::cout << "Fail to set socket timeout!\n";
        failed = true;
        close(clint_listen_fd);
        clint_listen_fd = 0;
        return;
    }
    if (setsockopt(clint_listen_fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
    {
        std::cout << "Fail to set socket timeout!\n";
        failed = true;
        close(clint_listen_fd);
        clint_listen_fd = 0;
        return;
    }
    if(bind(clint_listen_fd, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer)) != 0)
    {
        std::cout << "Fail to bind socket!\n";
        failed = true;
        close(clint_listen_fd);
        clint_listen_fd = 0;
        return;
    }
}

void TCPServer::startListening()
{
    if(listen_thread.get() == nullptr)
    {
        listen_thread = std::make_unique<std::thread>([this]()
        {
            connectionListener();
        });
    }
}

void TCPServer::connectionListener()
{
    listen(clint_listen_fd,20);
    epoll_fd = epoll_create1(0);
    if(epoll_fd == -1)
    {
        printf("Failed to create epoll file descriptor\n");
        return ;
    }

    printf("asfasf\n");
    int const MAX_EVENTS = 10;
    epoll_event ev, events[MAX_EVENTS];
    ev.events = EPOLLIN;
    ev.data.fd = clint_listen_fd;
    int conn_sock = 0;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clint_listen_fd, &ev) == -1)
    {
        printf("epoll_ctl: listen_sock");
        return;
    }
    run_listen_thread = true;
    while(run_listen_thread)
    {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, 1000);
        if (nfds == -1)
        {
            perror("epoll_wait");
            run_listen_thread = false;
            break;

        }
        cout << "Check Epoll " << nfds << endl;
        for (int n = 0; n < nfds; n++)
        {
            if (events[n].data.fd == clint_listen_fd)
            {
                sockaddr client_address;
                socklen_t addrlen;
                conn_sock = accept(clint_listen_fd,(struct sockaddr *) &client_address, &addrlen);
                std::shared_ptr<TCPClientConnection> new_client{new TCPClientConnection{client_address, addrlen, conn_sock}};
                //std::cout << "Got connection from " << inet_ntoa(client_address.sin_addr.s_addr) << std::endl;
                std::string data_string = "Hello World\nTest Test 123";
                new_client->send((void*)data_string.c_str(),data_string.length() + 1);
                if(onConnectCallback != nullptr)
                {
                    onConnectCallback(new_client);
                }
            }
        }
    }

    if(close(epoll_fd))
    {
        epoll_fd = 0;
        printf("Failed to close epoll file descriptor\n");
        return;
    }
}


void TCPServer::registerOnConnect(ConnectionCallback_t lambda)
{
    onConnectCallback = lambda;
}

void TCPServer::closeServer()
{
    run_listen_thread = false;
}
