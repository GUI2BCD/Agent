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

/**
 * Runs the collection scripts and stores result in memory
 */
void Report::collectData() {

	std::string runAs;

	// Check our effective username
	if( getUser() == "root" ) {
		runAs = runProgram( location + "scripts/loggedin.sh", "r");
	}

	// Local ip
	setLocalIp( runProgram(location + "scripts/getlocalip.sh", "r") );

	// Wifi hotspots
	setWifi( runProgram(location + "scripts/nearbywifi.sh", "r") );

	// Traceroute
	setTraceroute( runProgram(location + "scripts/traceroute.sh", "r") );

	// Webcam
	runProgram(location + "scripts/webcam.sh " + runAs, "r");

	// Screenshot
	runProgram(location + "scripts/screenshot.sh " + runAs, "r");


}

/**
 * Converts stored data into POST compatible data
 * @return string containing POST data
 */
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

const std::string& Report::getUser() const {
	return user;
}

void Report::setUser(const std::string& user) {
	this->user = user;
}
