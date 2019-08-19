#pragma once

#include "core/game_object_description.h"
#include <QMap>
#include <QHash>
#include <QPoint>
#include <QBitmap>
#include <QDebug>

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
using FieldValues = QMap<QString, PtrIFieldValue>;
//Object
struct GamePawn
{
    GamePawn() :
        typeName(""),
        name(""),
        icon(nullptr),
        fieldValues()
    {}

    GamePawn(const GamePawn&) = default;

    GamePawn(GamePawn&& gamePawn) :
        typeName(gamePawn.typeName),
        name(gamePawn.name),
        icon(gamePawn.icon),
        fieldValues(gamePawn.fieldValues)
    {
    }

    GamePawn& operator=(const GamePawn& gamePawn) = default;

    GamePawn& operator=(GamePawn&& gamePawn)
    {
        if(&gamePawn == this)
            return *this;

        typeName = gamePawn.typeName;
        name = gamePawn.name;
        icon = gamePawn.icon;
        fieldValues = gamePawn.fieldValues;

        return *this;
    }

    QString typeName;    
    QString name;    
    const QPixmap* icon;
        
    FieldValues fieldValues;
};

//inline uint qHash (const QPoint & key)
//{
//    return qHash (static_cast <qint64> (key.x () ) << 32 | key.y () );
//}

struct LevelStatistic
{
    int amountPawn;
    QHash<QString, int> amountPawnByType;
};

using LevelMap = QVector<QVector<GamePawn>>;

struct LevelData
{
    LevelData() = default;
    LevelData(const LevelData&) = default;

    LevelData(const QPoint mapSize) :
        statistic(),
        map()
    {
        GamePawn pawn;
        QVector<GamePawn> pawnRow(mapSize.y(), pawn);
        map = LevelMap(QVector<QVector<GamePawn>>( mapSize.x(), pawnRow));
    }

    LevelData(LevelData&& levelData) :
        statistic(levelData.statistic),
        map(levelData.map)
    {
    }

    LevelData& operator=(LevelData&) = default;
    LevelData& operator=(const LevelData&) = default;

    LevelData& operator=(LevelData&& levelData)
    {
        if(&levelData == this)
            return *this;

        statistic = levelData.statistic;
        map = levelData.map;
        return *this;
    }

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

QDataStream& operator<<(QDataStream& stream, const LevelData& levelData);
QDataStream& operator>>(QDataStream& stream, LevelData& levelData);
QDataStream& operator<<(QDataStream& stream, const LevelStatistic& levelStatistic);
QDataStream& operator>>(QDataStream& stream, LevelStatistic& levelStatistic);
QDataStream& operator<<(QDataStream& stream, const LevelMap& levelMap);
QDataStream& operator<<(QDataStream& stream, const GamePawn& gamePawn);
QDataStream& operator>>(QDataStream& stream, GamePawn& gamePawn);
QDataStream& operator<<(QDataStream& stream, const PtrIFieldValue& pFieldValue);
QDataStream& operator>>(QDataStream& stream, PtrIFieldValue& pFieldValue);
