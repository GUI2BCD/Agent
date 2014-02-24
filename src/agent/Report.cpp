/*
 * Report.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: cameron
 */

#include "Report.hpp"
#include "../linux/process.hpp"
#include <iostream>

Report::Report() {
	// TODO Auto-generated constructor stub

}

Report::~Report() {
	// TODO Auto-generated destructor stub
}

void Report::collectData() {



	// Local ip
	setLocalIp( runProgram("scripts/getlocalip.sh", "r") );

	// Remote ip
	setRemoteIp( runProgram("scripts/getremoteip.sh", "r") );

	// Wifi hotspots
	setWifi( runProgram("scripts/nearbywifi.sh", "r") );

	// Traceroute
	setTraceroute( runProgram("scripts/traceroute.sh", "r") );


}

std::string Report::toPost() {

	//std::cout << getLocalIp() << std::endl;
	//std::cout << getRemoteIp() << std::endl;
	//std::cout << getWifi() << std::endl;
	//std::cout << getTraceroute() << std::endl;

	return "";
}

const std::string& Report::getLocalIp() const {
	return localIP;
}

void Report::setLocalIp(const std::string& localIp) {
	localIP = localIp;
}

const std::string& Report::getRemoteIp() const {
	return remoteIP;
}

void Report::setRemoteIp(const std::string& remoteIp) {
	remoteIP = remoteIp;
}

const std::string& Report::getTraceroute() const {
	return traceroute;
}

void Report::setTraceroute(const std::string& traceroute) {
	this->traceroute = traceroute;
}

const std::string& Report::getWifi() const {
	return wifi;
}

void Report::setWifi(const std::string& wifi) {
	this->wifi = wifi;
}
