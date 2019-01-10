#include <iostream>
#include "tgiCppAPI.h"

/* ENTRY POINT */

int main()
{
	std::string command;
	TGICppAPI_WIN bot;
	while(1)
	{
		std::cin >> command;
		if (command == "end") break;
		else if (command == "start") bot.startPoll();
		else if (command == "stop")  bot.closePoll();
		//else if (command.find("add") != command.npos) bot.addCommand(command);
		//else if (command == "update") bot.update();
		else if (command == "channel")
		{
			std::string in;
			std::cout << "\n enter channel...\n";
			std::cin >> in;
			bot.changeChannel(in);
		}
		else std::cout << "\ninvalid command ... \n";
	}
	if (bot.isRunning) bot.closePoll();
	return 0;
}