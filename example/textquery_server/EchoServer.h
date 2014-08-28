#ifndef ECHO_TCP_SERVER_H
#define ECHO_TCP_SERVER_H 

#include <echo/TcpServer.h>
#include <echo/ThreadPool.h>
#include <echo/NonCopyable.h>
#include "textquery.h"
#include <fstream>
#include <iostream>
class EchoServer : NonCopyable
{
    public:
        EchoServer(const InetAddress &addr);
        void start(std::ifstream &);
    private:
        void onConnection(const TcpConnectionPtr &conn);
        void onMessage(const TcpConnectionPtr &conn);
        void onClose(const TcpConnectionPtr &conn);
        void compute(const std::string &s, const TcpConnectionPtr &conn);

        TcpServer server_;
        ThreadPool pool_;
        textquery text_;
};



#endif  /*ECHO_TCP_SERVER_H*/
