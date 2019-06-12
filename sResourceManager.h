#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

class sResourceManager
{
public:
	sResourceManager()
	{
		// Try to load textures
		std::ifstream config;
		config.open("textures.cfg");

		if (config.fail())
			std::cout << "Could not open textures.cfg\n";
		else
		{
			std::string name, path;
			while (!config.eof())
			{
				config >> name >> path;
				
				sf::Texture texture;
				if (!texture.loadFromFile(path))
				{
					// Error
				}
				else
				{
					// Add texture to the map at the key name
					m_textures[name] = texture;
				}
			}
		}

		std::cout << "Loaded " << m_textures.size() << " texture(s)\n";
	}

	// static functions -> can be called with sResourceManager::get()
	// Creates a single instance of the class thanks to static
	static sResourceManager &get()
	{
		static sResourceManager manager;
		return manager;
	}

	// Check if a texture exists
	// Send back that texture if it does
	// If it doesn't send back error texture
	sf::Texture &getTexture(std::string name)
	{
		if (m_textures.find(name) != m_textures.end())
		{
			return m_textures.at(name);
		}
		else return m_textures.at("error");
	}

private:
	std::map<std::string, sf::Texture> m_textures;
};

