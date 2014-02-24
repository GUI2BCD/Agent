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

	// Wifi hotspots
	setWifi( runProgram("scripts/nearbywifi.sh", "r") );

	// Traceroute
	setTraceroute( runProgram("scripts/traceroute.sh", "r") );


}

std::string Report::toPost() {

	std::string data = "&";

	data += "localip=";
	data += getLocalIp();
	data += "&wifi=";
	data += getWifi();
	data += "&traceroute=";
	data += getTraceroute();

	return data;
}

const std::string& Report::getLocalIp() const {
	return localIP;
}

void Report::setLocalIp(const std::string& localIp) {
	localIP = localIp;
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
