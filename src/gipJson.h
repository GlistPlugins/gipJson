/*
 * gipJson.h
 *
 *  Created on: Mar 11, 2023
 *      Author: Noyan Culum & Ecem Yaglioglu
*/

#ifndef SRC_GIPJSON_H_
#define SRC_GIPJSON_H_

#include "gBaseComponent.h"
#include "json.hpp"
#include "gFile.h"

/**
 *Getting, setting and saving the values from both simple and nested json files.
 */
class gipJson : public gBaseComponent{
public:
	gipJson();
	virtual ~gipJson();

/**
 * @brief Load JSON data from a file.
 * @param filename The name of the JSON file to load.
 */
	void loadJsonFile(const std::string& filename);

/**
 * @brief Get the value associated with a key.
 * @param key The key in the JSON structure (e.g., "quiz.maths.q1.options").
 * @return The value associated with the key.
 */
	std::string getValue(const std::string& key);

/**
 * @brief Set the value associated with a key.
 * @param key The key in the JSON structure.
 * @param newValue The new value to set.
 */
    void setValue(const std::string& key, const std::string& newValue);

/**
 * @brief Save the JSON data to a file.
 * @param filename The name of the file to save the JSON data to.
 */
    void saveJsonFile(const std::string& filename);


private:
	gFile file;
	std::string path;
	nlohmann::json js;
};

#endif /* SRC_GIPJSON_H_ */
