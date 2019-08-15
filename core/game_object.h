#pragma once

#include "core/game_object_description.h"
#include <QHash>
#include <QPoint>
#include <QBitmap>

struct IFieldValue
{
    virtual ~IFieldValue() = default;
    virtual FieldType type() = 0;
};

using PtrIFieldValue = std::shared_ptr<IFieldValue>;

struct FloatValue : public IFieldValue
{
    virtual ~FloatValue() = default;
    FieldType type() { return FieldType::FLOAT; }

    float value;
};

using PtrFloatValue = std::shared_ptr<FloatValue>;

struct IntValue : public IFieldValue
{
    virtual ~IntValue() = default;
    FieldType type() { return FieldType::INT; }

    float value;
};

using PtrIntValue = std::shared_ptr<IntValue>;

struct SelectionValue : public IFieldValue
{
    virtual ~SelectionValue() = default;
    FieldType type() { return FieldType::SELECTION; }

    QString value;
};

using PtrSelectionValue = std::shared_ptr<SelectionValue>;

using GPawnTypeId = unsigned;

//Object
struct GamePawn
{        
    QString typeName;
    QString name;    
    QBitmap* icon;
        
    QVector<PtrIFieldValue> fieldValues;
};

inline uint qHash (const QPoint & key)
{
    return qHash (static_cast <qint64> (key.x () ) << 32 | key.y () );
}
using LevelMap = QVector<QVector<GamePawn>>;
using LevelMaps = QHash<QString, LevelMap>;

struct GameData
{
    GameRules rules;
    PawnTypes pawnTypes;
    LevelMaps levelMaps;
};

//QDataStream& operator<<(QDataStream& stream, const LevelMap& levelMap);
//QDataStream& operator>>(QDataStream& stream, LevelMap& levelMap);
QDataStream& operator<<(QDataStream& stream, const GamePawn& gamePawn);
QDataStream& operator>>(QDataStream& stream, GamePawn& gamePawn);
QDataStream& operator<<(QDataStream& stream, const PtrIFieldValue& pFieldValue);
QDataStream& operator>>(QDataStream& stream, PtrIFieldValue& pFieldValue);
