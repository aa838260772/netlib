#include "EchoServer.h"
using namespace std;

int main(int argc, const char *argv[])
{
    ifstream is("EX");
    EchoServer server(InetAddress(8989));
    server.start(is);
    return 0;
}
