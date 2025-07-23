/*
Created by: Ong Kok Peng (2403435)
Date: 23/7/2025
*/

#pragma once

#include <string>

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

class UserInterface {
	virtual void waitForKey() = 0;
	virtual void clearScreen() = 0;
	virtual void showMenu() = 0;
};

#endif