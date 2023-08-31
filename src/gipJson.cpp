/*
 * gipJson.cpp
 *
 *  Created on: Mar 11, 2023
 *      Author: Noyan Culum & Ecem Yaglioglu
 */

#include "gipJson.h"


gipJson::gipJson() {
}

gipJson::~gipJson() {
}

void gipJson::loadJsonFile(const std::string& filename) {
	gFile file;
	file.loadFile(filename, gFile::FILEMODE_READONLY, false);
	std::string filecontent = file.getText();
	js = nlohmann::json::parse(filecontent);
	file.close();
}

std::string gipJson::getValue(const std::string& key) {
    std::vector<std::string> segments;
    std::istringstream segmentStream(key);
    std::string segment;
    while (std::getline(segmentStream, segment, '.')) {
        segments.push_back(segment);
    }
    nlohmann::json* currentObject = &js;
    for (const std::string& segment : segments) {
        if (currentObject->contains(segment)) {
            currentObject = &(*currentObject)[segment];
        } else {
            return "";
            // Return an empty string if key doesn't exist
        }
    }
    if (currentObject->is_string()) {
        return currentObject->get<std::string>();
    } else if (currentObject->is_array()) {
        return currentObject->dump();
        // Return JSON representation of the array
    } else {
        return "";
        // Return empty string for unsupported types
    }
}

void gipJson::setValue(const std::string& key, const std::string& newValue) {
    std::vector<std::string> segments;
    std::istringstream segmentStream(key);
    std::string segment;
    while (std::getline(segmentStream, segment, '.')) {
        segments.push_back(segment);
    }
    nlohmann::json* currentObject = &js;
    for (size_t i = 0; i < segments.size() - 1; ++i) {
        if (currentObject->contains(segments[i])) {
            currentObject = &(*currentObject)[segments[i]];
        } else {
            (*currentObject)[segments[i]] = nlohmann::json::object();
            currentObject = &(*currentObject)[segments[i]];
        }
    }
    (*currentObject)[segments.back()] = newValue;
}

void gipJson::saveJsonFile(const std::string& filename) {
    gFile file;
    file.loadFile(filename, gFile::FILEMODE_WRITEONLY, false);
	file.write(js.dump());
	file.close();
}
