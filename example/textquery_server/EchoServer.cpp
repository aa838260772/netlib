#include "EchoServer.h"
#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;
using namespace placeholders;

EchoServer::EchoServer(const InetAddress &addr)
    :server_(addr),
     pool_(1000, 4)
{
    server_.setConnection(bind(&EchoServer::onConnection, this, _1));
    server_.setMessage(bind(&EchoServer::onMessage, this, _1));
    server_.setClose(bind(&EchoServer::onClose, this, _1));
}

void EchoServer::start(ifstream &is)
{
    text_.read_file(is);
    pool_.start();
    server_.start();
}

void EchoServer::onConnection(const TcpConnectionPtr &conn)
{
    cout << conn->getPeerAddr().toIp() << " port: "
        << conn->getPeerAddr().toPort() << endl;
    conn->send("Hello, welcome to Echo Server!!!\r\n");
}


void EchoServer::onMessage(const TcpConnectionPtr &conn)
{
    string s(conn->receive());
    //不要把recv任务放到线程池
    //conn->send(s);
    pool_.addTask(bind(&EchoServer::compute, this, s, conn));
}

//把计算任务和tcp回发做成一个函数，交给线程池
void EchoServer::compute(const std::string &word, const TcpConnectionPtr &conn)
{
    string s = word;
    string s1;
    set<textquery::line_no> se;
    se = text_.run_query(s);
    if(se.size() == 0)
        conn->send("not found\n");
    else
    {
        char buf[4] = {0};
        sprintf(buf, "%d", se.size());
        conn->send(string("ocuurs ") + buf + " times\n");
    }
    for(set<textquery::line_no>::iterator it = se.begin(); 
         it != se.end();
         it++)
    {
        char s2[20] = {0};
      sprintf(s2, "%d", *it);
    s1 =  s2 + text_.text_line(*it) + "\n";
    conn->send(s1);
    }
}

void EchoServer::onClose(const TcpConnectionPtr &conn)
{
    cout << conn->getPeerAddr().toIp() << " port: "
        << conn->getPeerAddr().toPort() << "Close" << endl;
    conn->shutdown();
}


