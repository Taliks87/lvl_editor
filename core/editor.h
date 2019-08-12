#pragma once

#include <vector>
#include <unordered_map>

#include "core/config.h"
#include "core/game_object_description.h"
#include "core/level_map.h"

//Editor
class Editor
{
public:
    Editor();
    
    void createLevel(const std::string& name);
    void saveLevel(const std::string& name);
    void loadLevel(const std::string& name);
    //void removeLevel(const std::string& name);
    
private:
    std::unordered_map<GObjectTypeId, GObjectType> m_objectTypeDescriptions;
    
//    LevelEditor m_levelEditor;
//    LevelMap m_levelMap;
};
