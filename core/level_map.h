//#pragma once
//#include "core/config.h"
//#include "core/game_object.h"

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
//    QHash<Point, GObject> objects;
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

