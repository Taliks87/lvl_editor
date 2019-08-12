//#pragma once

//#include <array>
//#include <unordered_map>

//#include "core/config.h"
//#include "core/game_object.h"

//constexpr Point sizeMap{30,15};

//namespace std
//{
//    template<>
//    struct hash<Point>
//    {
//        size_t operator()(const Point& obj) const
//        {
//            auto pX = obj.x;
//            auto pY = obj.y;
//            return hash<unsigned>()(pX + sizeMap.x * pY);
//        }
//    };
//}

//struct LevelMap
//{
//    std::array<std::array<GObjectTypeId, sizeMap.x>, sizeMap.y> map;
//    std::unordered_map<Point, GObject> objects;
//};

//class LevelEditor
//{
//public:
    
//    void selectLevel(LevelMap*);
//    void deselectLevel(LevelMap*);
    
//    GObject* getObject(Point p) const;
//    int addObject(Point p, GObject object);
//    int removeObject(Point p);
    
//private:
//    LevelMap* m_levelMap;
//};

