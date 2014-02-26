/*
 * Report.hpp
 *
 *  Created on: Feb 24, 2014
 *      Author: cameron
 */

#ifndef REPORT_HPP_
#define REPORT_HPP_

#include <string>

static std::string location = "/usr/share/lastresortrecovery/";

class Report {
public:
	Report();
	virtual ~Report();

	// Collects the data
	void collectData();

	// Creates the post data to be sent to server
	std::string toPost();

	// Getters & Setters
	const std::string& getLocalIp() const;
	void setLocalIp(const std::string& localIp);
	const std::string& getTraceroute() const;
	void setTraceroute(const std::string& traceroute);
	const std::string& getWifi() const;
	void setWifi(const std::string& wifi);

private:

	// Local IP address
	std::string localIP;
	// List of wifi hotspots
	std::string wifi;
	// Traceroute to a host
	std::string traceroute;

};

#endif /* REPORT_HPP_ */
