/*
 * PassiveConnection.hpp
 *
 *  Created on: Jan 25, 2014
 *      Author: cameron
 */

#ifndef PASSIVECONNECTION_HPP_
#define PASSIVECONNECTION_HPP_

#include <string>

class PassiveConnection {
public:

	// Initializes the URLs
	PassiveConnection();
	// Cleans up
	virtual ~PassiveConnection();

	// Gets the status of the user's device
	std::string getStatus( std::string userName, std::string password, std::string deviceID );

	// Getters & Setters
	const std::string& getReportUrl() const;
	void setReportUrl(const std::string& reportUrl);
	const std::string& getStatusUrl() const;
	void setStatusUrl(const std::string& statusUrl);

private:
	std::string statusURL;
	std::string reportURL;
};

#endif /* PASSIVECONNECTION_HPP_ */
