/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef TRANSPORT_ENTITY_H
#define TRANSPORT_ENTITY_H

class TransportEntity {
private:
	string destination;
	string time;
public:
	struct validationOutcome { bool validationPass = true; string message = ""; };
	TransportEntity();
	validationOutcome setValues(string dest, string time);
	string getDestination();
	string getTime();
};

#endif

