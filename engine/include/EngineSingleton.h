#pragma once
#include <iostream>
#include <ConfigFile.h>
#include <WindowHandle.h>
#include <restclient/restclient.h>

namespace scx
{
	class EngineSingleton
	{
	public:
		EngineSingleton();
		~EngineSingleton();

		ConfigFile& GetConfig() { return Config; };

		void Initialize() 
		{ 
			if(!Config.Open("config.txt"))
				std::cout << "configuration file failed to load.\n";

			// Window
			{
				// Dimensions
				Config.GetSetting("graphics::window::width", WinWidth);
				Config.GetSetting("graphics::window::height", WinHeight);

				// Title
				Config.GetSetting("graphics::window::title", WindowTitle);
			}

			// Web app
			{
				Config.GetSetting("web app::address", WebAppAddress);

				Config.GetSetting("web app::creds::user name", WebAppUsername);
				Config.GetSetting("web app::creds::password", WebAppPassword);
			}


			std::printf("initializing window...\n");

			Window.Initialize(WinWidth, WinHeight, WindowTitle);

			std::printf("window size: %ix%i \n", WinWidth, WinHeight);

			std::printf("attempting to connect to: %s, username: %s\n", WebAppAddress.c_str(), WebAppUsername.c_str());

			std::string HeartBeatAddress = WebAppAddress + "heartbeat";
			RestClient::response r = RestClient::get(HeartBeatAddress);

			std::string response = r.body + "\n";

			if(r.code == 200)
				std::printf(response.c_str());
			else
				std::printf("connection attempt failed, code %i\n", r.code);
		};

		WindowHandle& GetWindow() { return Window; };
	protected:

	private:
		ConfigFile Config;

		std::string WindowTitle;
		int WinWidth, WinHeight;
		WindowHandle Window;

		std::string WebAppAddress;

		std::string WebAppUsername;
		std::string WebAppPassword;
	};

	static EngineSingleton Engine;
}