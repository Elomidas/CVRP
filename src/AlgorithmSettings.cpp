//
// Created by elomidas on 24/04/18.
//

#include "../include/AlgorithmSettings.h"

#define _DEFAULT_CONFIGURATION_FILE "config/default.json"

/**
 * Default constructor
 */
AlgorithmSettings::AlgorithmSettings() : m_configurationFile(_DEFAULT_CONFIGURATION_FILE) {
    //Nothing
}

/**
 * Other constructor
 * @param path
 */
AlgorithmSettings::AlgorithmSettings(const std::string &path) : m_configurationFile(path) {
    //Nothing
}

/**
 * Destructor
 */
AlgorithmSettings::~AlgorithmSettings() {
    //Nothing
}
