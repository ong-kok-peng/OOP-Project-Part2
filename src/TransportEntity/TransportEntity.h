#pragma once

#ifndef TRANSPORT_ENTITY_H
#define TRANSPORT_ENTITY_H

class TransportEntity {
private:
	string destination;
	string time;
public:
	TransportEntity();
	bool setDestination(string destination);
	bool setTime(string time);
	string getDestination();
	string getTime();
};

#endif