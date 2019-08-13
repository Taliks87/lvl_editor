#pragma once

#include <string>
#include <vector>

#include "core/config.h"

class GObjectType;
class IFieldValue;

//Image
class Image
{
    std::string path;
};

//Object
class GObject
{
    GObjectTypeId typeId;
    std::string name;
    Point position;
    Image img;
    
    GObjectType* description;
    std::vector<IFieldValue> fieldValues;
};

class GObjectEditor
{
public:
    void selectObject(GObject* selectGObject);
    void deselectObject();
    
private:
    GObject* m_gObject;
};
