#include "tgiDataHandler.h"

TGIDataHandler::TGIDataHandler()
{
	filePath = "";
	chatLog = "";
}

void TGIDataHandler::setFilePath(std::string path)
{
	this->filePath = path;
}