#pragma once

#include <json/reader.h>
#include <json/writer.h>
#include <json/elements.h>

#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include <stdio.h>

class ConfigFile
{
	public:
		ConfigFile() {};
		
		ConfigFile(std::string filename) : FileName(filename) 
		{
			Open();
		};
		
		~ConfigFile() 
		{
			if(IsOpen())
				Close();
		};
		
		std::string GetFileName() { return FileName; };
		
		bool IsOpen() { return File.is_open(); };
		
		bool IsEmpty() { return false; };
		
		bool Open()
		{
			if(FileName.empty())
				return false;
				
			if(IsOpen())
				Close();
				
			File.open(FileName.c_str());

			if(IsOpen())
				FileString << File.rdbuf();

			return IsOpen();
		};
		
		bool Open(std::string FileName)
		{
			this->FileName = FileName;
				
			if(IsOpen())
				Close();
				
			File.open(FileName.c_str());
			
			if(IsOpen())
				FileString << File.rdbuf();
			
			if(!IsEmpty())
				return IsOpen();
			else
				Close();
				
			return false;
		};
		
		void Close()
		{
			File.close();
			FileString.clear();
		};

		std::vector<std::string> tokenize(const std::string& str,const std::string& delimiters)
		{
			std::vector<std::string> tokens;

			// skip delimiters at beginning.
			std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

			// find first "non-delimiter".
			std::string::size_type pos = str.find_first_of(delimiters, lastPos);

			while (std::string::npos != pos || std::string::npos != lastPos)
			{
				// found a token, add it to the vector.
				tokens.push_back(str.substr(lastPos, pos - lastPos));

				// skip delimiters.  Note the "not_of"
				lastPos = str.find_first_not_of(delimiters, pos);

				// find next "non-delimiter"
				pos = str.find_first_of(delimiters, lastPos);
			}

			return tokens;
		}
		
		void GetSetting(std::string SettingName, int& IntSetting)
		{
			std::string Parents = SettingName.substr(0, SettingName.find_last_of("::"));
			SettingName = SettingName.substr(SettingName.find_last_of("::") + 1, SettingName.length());
			

			std::vector<std::string> ParentObjects = tokenize(Parents, "::");

			//json reader for reading the file
			json::Reader Reader;

			//root object of the json file
			json::Object rootObject;

			std::stringstream stream;
			stream << FileString.str();

			//parse the json
			Reader.Read(rootObject, stream);

			if(!ParentObjects.empty())
			{
				std::string RootName = ParentObjects[0];

				for(json::Object::iterator i = rootObject.Begin(); i != rootObject.End(); ++i)
				{
					if(!(*i).name.compare(RootName))
					{
						//Root node found

						if(ParentObjects.size() == 1)
						{
							json::Number Number = rootObject[ParentObjects[0]][SettingName];

							IntSetting = Number;

							return;
						}

						json::Object FirstObject = (*i).element;
						json::Object CurrentObject = FirstObject;

						for(int con = 0; con < ParentObjects.size(); ++con)
						{
							for(json::Object::iterator joi = CurrentObject.Begin(); joi != CurrentObject.End(); ++joi)
							{
								if(!(*joi).name.compare(ParentObjects[con]))
								{
									//std::cout << "Found " << ParentObjects[con] << std::endl;

									if(con != ParentObjects.size() - 1)
										CurrentObject = CurrentObject[ParentObjects[con]];
									else
									{
										//Found the setting
									//	std::cout << "Found " << SettingName << std::endl;
										json::Number Number = CurrentObject[ParentObjects[con]][SettingName];

										IntSetting = Number;
									}
								}
							}
						}
					}
				}
			}
		};

		void GetSetting(std::string SettingName, bool& BoolSetting)
		{
			std::string Parents = SettingName.substr(0, SettingName.find_last_of("::"));
			SettingName = SettingName.substr(SettingName.find_last_of("::") + 1, SettingName.length());


			std::vector<std::string> ParentObjects = tokenize(Parents, "::");

			//json reader for reading the file
			json::Reader Reader;

			//root object of the json file
			json::Object rootObject;

			std::stringstream stream;
			stream << FileString.str();

			//parse the json
			Reader.Read(rootObject, stream);

			if(!ParentObjects.empty())
			{
				std::string RootName = ParentObjects[0];

				for(json::Object::iterator i = rootObject.Begin(); i != rootObject.End(); ++i)
				{
					if(!(*i).name.compare(RootName))
					{
						//Root node found

						if(ParentObjects.size() == 1)
						{
							json::Boolean Bool = rootObject[ParentObjects[0]][SettingName];

							BoolSetting = Bool;

							return;
						}

						json::Object FirstObject = (*i).element;
						json::Object CurrentObject = FirstObject;

						for(int con = 0; con < ParentObjects.size(); ++con)
						{
							for(json::Object::iterator joi = CurrentObject.Begin(); joi != CurrentObject.End(); ++joi)
							{
								if(!(*joi).name.compare(ParentObjects[con]))
								{
									//std::cout << "Found " << ParentObjects[con] << std::endl;

									if(con != ParentObjects.size() - 1)
										CurrentObject = CurrentObject[ParentObjects[con]];
									else
									{
										//Found the setting
										//std::cout << "Found " << SettingName << std::endl;
										json::Boolean Bool = CurrentObject[ParentObjects[con]][SettingName];

										BoolSetting = Bool;
									}
								}
							}
						}
					}
				}
			}
		};

		void GetSetting(std::string SettingName, std::string& StringSetting)
		{
			std::string Parents = SettingName.substr(0, SettingName.find_last_of("::"));
			SettingName = SettingName.substr(SettingName.find_last_of("::") + 1, SettingName.length());


			std::vector<std::string> ParentObjects = tokenize(Parents, "::");

			//json reader for reading the file
			json::Reader Reader;

			//root object of the json file
			json::Object rootObject;

			std::stringstream stream;
			stream << FileString.str();

			//parse the json
			Reader.Read(rootObject, stream);

			if(!ParentObjects.empty())
			{
				std::string RootName = ParentObjects[0];

				for(json::Object::iterator i = rootObject.Begin(); i != rootObject.End(); ++i)
				{
					if(!(*i).name.compare(RootName))
					{
						//Root node found

						if(ParentObjects.size() == 1)
						{
							json::String String = rootObject[ParentObjects[0]][SettingName];

							StringSetting = String;

							return;
						}

						json::Object FirstObject = (*i).element;
						json::Object CurrentObject = FirstObject;

						for(int con = 0; con < ParentObjects.size(); ++con)
						{
							for(json::Object::iterator joi = CurrentObject.Begin(); joi != CurrentObject.End(); ++joi)
							{
								if(!(*joi).name.compare(ParentObjects[con]))
								{
									//std::cout << "Found " << ParentObjects[con] << std::endl;

									if(con != ParentObjects.size() - 1)
										CurrentObject = CurrentObject[ParentObjects[con]];
									else
									{
										//Found the setting
										//std::cout << "Found " << SettingName << std::endl;
										json::String String = CurrentObject[ParentObjects[con]][SettingName];

										StringSetting = String;
									}
								}
							}
						}
					}
				}
			}
		};
		
	private:
		std::string FileName;
		
		std::fstream File;
		
		std::stringstream FileString;
		
		std::map<std::string, std::string> Values;
};