 ///
 /// @file    TcpServer.cc
 /// @author  zzseven
 /// @date    2016-03-25 14:41:56
 ///
 
#include "TcpServer.h"


namespace wd
{
TcpServer::TcpServer(unsigned short port)
: _sock()
, _epoll(_sock.fd())
{
	InetAddress addr(port);
	_sock.ready(addr);

}

TcpServer::TcpServer(const char * ip, unsigned short port)
: _sock()
, _epoll(_sock.fd())
{
	InetAddress addr(ip, port);
	_sock.ready(addr);
	
}

void TcpServer::start()
{
	_epoll.setConnectionCallback(_onConnection);
	_epoll.setMessageCallback(_onMessage);
	_epoll.setCloseCallback(_onClose);

	_epoll.loop();
}

void TcpServer::stop()
{
	_epoll.unloop();
}


void TcpServer::setConnectionCallback(TcpServerCallback cb)
{
	_onConnection = cb;
}

void TcpServer::setMessageCallback(TcpServerCallback cb)
{
	_onMessage = cb;
}

void TcpServer::setCloseCallback(TcpServerCallback cb)
{
	_onClose = cb;
}

}
