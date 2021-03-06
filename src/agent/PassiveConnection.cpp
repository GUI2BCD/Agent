/*
 * PassiveConnection.cpp
 *
 *  Created on: Jan 25, 2014
 *      Author: cameron
 */

#include "PassiveConnection.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cstdio>
#include <iostream>

#include <curl/curl.h>

struct MemoryStruct {
	char *memory;
	size_t size;
};

// Source: http://curl.haxx.se/libcurl/c/getinmemory.html
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb,
		void *userp) {
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *) userp;

	mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;

}

PassiveConnection::PassiveConnection() {
	// TODO Auto-generated constructor stub

}

PassiveConnection::~PassiveConnection() {
	// TODO Auto-generated destructor stub
}

/**
 * This function will to connect to the serverside and request the status of
 * the device under a user's account and return the status as a string
 *
 * Source for curl: http://curl.haxx.se/libcurl/c/getinmemory.html
 *
 * @param username User name of the user
 * @param password User's password
 * @param deviceID numeric indentification of device
 * @return string representation of device status
 */
std::string PassiveConnection::getStatus(std::string userName,
		std::string password, std::string deviceID) {

	CURL *curl_handle;
	CURLcode res;

	struct MemoryStruct tmp;
	std::string userURL;
	std::string postData;
	std::string result;

	// Build user URL
	userURL = getReportUrl() + "?action=status";

	// Build post data
	postData = "email=" + userName;
	postData += "&password=";
	postData += password;
	postData += "&deviceid=";
	postData += deviceID;

	//std::cout << "Requesting: " << userURL << std::endl;

	// Temporary storage
	tmp.memory = (char *) malloc(1);
	tmp.size = 0;

	// Initialize curl
	curl_global_init(CURL_GLOBAL_ALL);

	// Init session
	curl_handle = curl_easy_init();

	// Set URL
	curl_easy_setopt(curl_handle, CURLOPT_URL, userURL.c_str());
	// Set callback
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	// Set POST data
	curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, postData.c_str());

	// Set data destination
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void * ) &tmp);

	// Set user agent
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	// Perform http request
	res = curl_easy_perform(curl_handle);

	// Check for errors
	if (res != CURLE_OK) {
		std::cout << "Request status failed: " << curl_easy_strerror(res)
				<< std::endl;
	}
	// Save result
	else {
		result = tmp.memory;
	}

	// Cleanup curl handle
	curl_easy_cleanup(curl_handle);

	// Cleanup temp memory
	free(tmp.memory);

	// Cleanup libcurl
	curl_global_cleanup();

	return result;

}

const std::string& PassiveConnection::getReportUrl() const {
	return reportURL;
}

void PassiveConnection::setReportUrl(const std::string& reportUrl) {
	reportURL = reportUrl;
}

const std::string& PassiveConnection::getStatusUrl() const {
	return statusURL;
}

void PassiveConnection::setStatusUrl(const std::string& statusUrl) {
	statusURL = statusUrl;
}
/**
 * Checks username and password against server
 * @param userName User's email
 * @param password User's password
 * @return result from server
 */
std::string PassiveConnection::authenticate(std::string userName,
		std::string password) {

	CURL *curl_handle;
	CURLcode res;

	struct MemoryStruct tmp;
	std::string userURL;
	std::string postData;
	std::string result;

	// Build user URL
	userURL = getReportUrl() + "?action=auth";

	// Build post data
	postData = "email=" + userName;
	postData += "&password=";
	postData += password;
	//std::cout << "Requesting: " << userURL << std::endl;

	// Temporary storage
	tmp.memory = (char *) malloc(1);
	tmp.size = 0;

	// Initialize curl
	curl_global_init(CURL_GLOBAL_ALL);

	// Init session
	curl_handle = curl_easy_init();

	// Set URL
	curl_easy_setopt(curl_handle, CURLOPT_URL, userURL.c_str());
	// Set callback
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	// Set POST data
	curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, postData.c_str());

	// Set data destination
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void * ) &tmp);

	// Set user agent
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	// Perform http request
	res = curl_easy_perform(curl_handle);

	// Check for errors
	if (res != CURLE_OK) {
		std::cout << "Request status failed: " << curl_easy_strerror(res)
				<< std::endl;
	}
	// Save result
	else {
		result = tmp.memory;
	}

	// Cleanup curl handle
	curl_easy_cleanup(curl_handle);

	// Cleanup temp memory
	free(tmp.memory);

	// Cleanup libcurl
	curl_global_cleanup();

	return result;

}

/**
 * Registers a new device to the server
 * @param userName User's email
 * @param password User's password
 * @param deviceName Name of this device
 * @return result from server
 */
std::string PassiveConnection::registerDevice(std::string userName,
		std::string password, std::string deviceName) {

	CURL *curl_handle;
	CURLcode res;

	struct MemoryStruct tmp;
	std::string userURL;
	std::string postData;
	std::string result;

	// Build user URL
	userURL = getReportUrl() + "?action=register";

	// Build post data
	postData = "email=" + userName;
	postData += "&password=";
	postData += password;
	postData += "&devicename=";
	postData += deviceName;

	//std::cout << "Requesting: " << userURL << std::endl;

	// Temporary storage
	tmp.memory = (char *) malloc(1);
	tmp.size = 0;

	// Initialize curl
	curl_global_init(CURL_GLOBAL_ALL);

	// Init session
	curl_handle = curl_easy_init();

	// Set URL
	curl_easy_setopt(curl_handle, CURLOPT_URL, userURL.c_str());
	// Set callback
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	// Set POST data
	curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, postData.c_str());

	// Set data destination
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void * ) &tmp);

	// Set user agent
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	// Perform http request
	res = curl_easy_perform(curl_handle);

	// Check for errors
	if (res != CURLE_OK) {
		std::cout << "Request status failed: " << curl_easy_strerror(res)
				<< std::endl;
	}
	// Save result
	else {
		result = tmp.memory;
	}

	// Cleanup curl handle
	curl_easy_cleanup(curl_handle);

	// Cleanup temp memory
	free(tmp.memory);

	// Cleanup libcurl
	curl_global_cleanup();

	return result;

}

/**
 * Sends report to the server to be stored
 * @param userName User's email
 * @param password Password of user
 * @param deviceID Device id
 * @param data Collected data
 * @return result from server
 */
std::string PassiveConnection::sendReport(std::string userName,
		std::string password, std::string deviceID, std::string data) {

	CURL *curl_handle;
	CURLcode res;

	struct MemoryStruct tmp;
	std::string userURL;
	std::string postData;
	std::string result;

	// Build user URL
	userURL = getReportUrl() + "?action=report";

	// Build post data
	postData = "email=" + userName;
	postData += "&password=";
	postData += password;
	postData += "&deviceid=";
	postData += deviceID;
	// Add collected fields
	postData += data;

	//std::cout << "Requesting: " << userURL << std::endl;

	// Temporary storage
	tmp.memory = (char *) malloc(1);
	tmp.size = 0;

	// Initialize curl
	curl_global_init(CURL_GLOBAL_ALL);

	// Init session
	curl_handle = curl_easy_init();

	// Set URL
	curl_easy_setopt(curl_handle, CURLOPT_URL, userURL.c_str());
	// Set callback
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	// Set POST data
	curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, postData.c_str());

	// Set data destination
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void * ) &tmp);

	// Set user agent
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	// Perform http request
	res = curl_easy_perform(curl_handle);

	// Check for errors
	if (res != CURLE_OK) {
		std::cout << "Request status failed: " << curl_easy_strerror(res)
				<< std::endl;
	}
	// Save result
	else {
		result = tmp.memory;
	}

	// Cleanup curl handle
	curl_easy_cleanup(curl_handle);

	// Cleanup temp memory
	free(tmp.memory);

	// Cleanup libcurl
	curl_global_cleanup();

	return result;

}

std::string PassiveConnection::submitImages(std::string reportID,
		std::string webcam, std::string screenshot) {
	CURL *curl;
	CURLcode res;
	std::string result;

	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;
	static const char buf[] = "Expect:";

	struct MemoryStruct tmp;

	// Build user URL
	std::string userURL = getReportUrl() + "?action=upload";

//	std::cout << userURL << std::endl;

	curl_global_init(CURL_GLOBAL_ALL);

	// Temporary storage
	tmp.memory = (char *) malloc(1);
	tmp.size = 0;

	// Report ID
	curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "reportid",
			CURLFORM_COPYCONTENTS, reportID.c_str(), CURLFORM_END);

	// Screenshot
	if( screenshot == "0\n") {
	curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "screenshot",
			CURLFORM_FILE, "screenshot.png", CURLFORM_END);
	}
	// Webcam
	if( webcam == "0\n" ) {
	curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "webcam",
			CURLFORM_FILE, "webcam.jpeg", CURLFORM_END);
	}
	curl = curl_easy_init();

	headerlist = curl_slist_append(headerlist, buf);
	// Set URL
	curl_easy_setopt(curl, CURLOPT_URL, userURL.c_str());

	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	// Set callback
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	// Set data destination
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void * ) &tmp);

	// Run it
	res = curl_easy_perform(curl);
	// Error check
	if (res != CURLE_OK) {
		std::cout << "Request status failed: " << curl_easy_strerror(res)
				<< std::endl;
	} else {
		result = tmp.memory;
	}
	// Clean up
	curl_easy_cleanup(curl);

	// Cleanup form
	curl_formfree(formpost);
	// Clean up other
	curl_slist_free_all(headerlist);

	// Clean up files
	if( screenshot == "0\n" ) {
	std::remove("screenshot.png");
	}
	if( webcam == "0\n" ) {
	std::remove("webcam.jpeg");
	}

	return result;
}

