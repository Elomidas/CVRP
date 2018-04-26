//
// Created by elomidas on 24/04/18.
//

#ifndef CVRP_ALGORITHMSETTINGS_H
#define CVRP_ALGORITHMSETTINGS_H

#include <string>

class AlgorithmSettings {
protected:
    std::string m_configurationFile;

public:
    AlgorithmSettings();
    explicit AlgorithmSettings(const std::string&);
    ~AlgorithmSettings();

    virtual void loadSettings() {};
    virtual void loadSettings(const std::string&) {};
};


#endif //CVRP_ALGORITHMSETTINGS_H
