#pragma once

#include <QDataStream>

using GObjectTypeId = unsigned;

struct Point {
    unsigned x;
    unsigned y;
};

enum Errors
{
    NONE = 0,
    
    ERROR_CREATE_LEVEL = 101,
    ERROR_SAVE_LEVEL = 102,
    ERROR_LOAD_LEVEL = 103,
    ERROR_EDIT_LEVEL = 104,
    
    ERROR_ADD_OBJECT = 201,
    ERROR_REMOVE_OBJECT = 202,
    ERROR_SELECT_OBJECT = 203,
    ERROR_EDIT_OBJECT = 204,
    
    ERROR_ADD_TYPE_OBJECT = 301,
    ERROR_REMOVE_TYPE_OBJECT = 302,
    ERROR_SELECT_TYPE_OBJECT = 303,
    ERROR_EDIT_TYPE_OBJECT = 304,
};

struct Rules
{

};
