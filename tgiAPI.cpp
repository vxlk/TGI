#include "tgiAPI.h"

//todo : convert <thread> to boost::thread
//https://stackoverflow.com/questions/15188937/using-clr-and-stdthread

//using copy constructor .. did not overload hope this works
tgiAPI::CLI::tgiApp::tgiApp() : _impl(new PhantomBot) {

}
tgiAPI::CLI::tgiApp::~tgiApp() {
	
}

tgiAPI::CLI::tgiApp::!tgiApp() {

}

const PhantomBot* tgiAPI::CLI::tgiApp::getInstance() {
	return this->_impl;
}

void tgiAPI::CLI::tgiApp::closeInstance() {

}

int tgiAPI::CLI::tgiApp::createInstance() {
	this->_impl = new PhantomBot();
	if (_impl) return 1;
	else return 0;
}

void tgiAPI::CLI::tgiApp::botInit() {
	if (this->_impl)
		this->_impl->start();
}

std::string tgiAPI::CLI::tgiApp::editConfigFile() {
	return "";
}

