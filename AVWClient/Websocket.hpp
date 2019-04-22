#pragma once
#include "Singleton.hpp"

class Websocket : 
	public Singleton<Websocket>
{
public:
	Websocket();
	~Websocket();
};

