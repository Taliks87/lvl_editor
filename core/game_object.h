#pragma once

#include "core/game_object_description.h"
#include <QHash>
#include <QPoint>
#include <QBitmap>

struct IFieldValue
{
    virtual ~IFieldValue();
    virtual FieldType type() = 0;
};

using PtrIFieldValue = std::shared_ptr<IFieldValue>;

struct FloatValue : public IFieldValue
{
    FloatValue() = default;
    explicit FloatValue(float value_) : value(value_) {}
    ~FloatValue() override = default;
    FieldType type() override;

    float value;
};

using PtrFloatValue = std::shared_ptr<FloatValue>;

struct IntValue : public IFieldValue
{
    IntValue() = default;
    explicit IntValue(int value_) : value(value_) {}
    ~IntValue() override = default;
    FieldType type() override;

    int value;
};

using PtrIntValue = std::shared_ptr<IntValue>;

struct SelectionValue : public IFieldValue
{
    SelectionValue() = default;
    explicit SelectionValue(const QString& value_) : value(value_) {}
    ~SelectionValue() override = default;
    FieldType type() override;

    QString value;
};

using PtrSelectionValue = std::shared_ptr<SelectionValue>;

using GPawnTypeId = unsigned;
using FieldValues = QHash<QString, PtrIFieldValue>;
//Object
struct GamePawn
{        
    QString typeName;
    QString name;    
    const QPixmap* icon;
        
    FieldValues fieldValues;
};

//inline uint qHash (const QPoint & key)
//{
//    return qHash (static_cast <qint64> (key.x () ) << 32 | key.y () );
//}

using LevelStatistic = QHash<QString, int>;
using LevelMap = QVector<QVector<GamePawn>>;

struct LevelData
{
    LevelStatistic statistic;
    LevelMap map;
};

using LevelsData = QHash<QString, LevelData>;

struct GameData
{
    GameRules rules;
    PawnTypes pawnTypes;
    LevelsData levelsData;
};

//QDataStream& operator<<(QDataStream& stream, const LevelMap& levelMap);
//QDataStream& operator>>(QDataStream& stream, LevelMap& levelMap);
QDataStream& operator<<(QDataStream& stream, const GamePawn& gamePawn);
QDataStream& operator>>(QDataStream& stream, GamePawn& gamePawn);
QDataStream& operator<<(QDataStream& stream, const PtrIFieldValue& pFieldValue);
QDataStream& operator>>(QDataStream& stream, PtrIFieldValue& pFieldValue);
