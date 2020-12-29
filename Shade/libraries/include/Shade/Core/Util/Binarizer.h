#pragma once
#include "stdafx.h"
#include "Shade/Core/CoreAPI.h"

namespace se {

	class SE_API Binarizer
	{
	public:

		inline static void ReadAt(std::ifstream& file, std::streampos pos)
		{
			file.seekg(pos);
		}
		inline static void WriteAt(std::ofstream& file, std::streampos pos)
		{
			file.seekp(pos);
		}
		template <typename T>
		inline static T ReadNext(std::ifstream& file, const std::streamsize& size = 1)
		{
			T value;

			if (std::is_same<T, std::string>::value)
			{
				char buffer = ' ';

				while (buffer != '\0')
				{
					file.read(&buffer, sizeof(char));
					*reinterpret_cast<std::string*>(&value) += buffer;
				}
			}
			else
			{
				file.read(reinterpret_cast<char*>(&value), sizeof(T) * size);
			}

			return value;
		}
		template <typename T>
		inline static std::streampos WriteNext(std::ofstream& file, T value, const std::streamsize& size = 1)
		{
			std::streampos pos = file.tellp();

			if (std::is_same<T, std::string>::value)
			{
				std::string* buffer = reinterpret_cast<std::string*>(&value);
				file.write((char*)buffer->c_str() + '\0', sizeof(char) * buffer->size() + 1);
			}
			else
			{
				file.write((char*)&value, sizeof(T) * size);
			}

			return pos;
		}
	};
}

