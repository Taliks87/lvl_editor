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

struct FloatValue : public IFieldValue
{
    virtual ~FloatValue() = default;
    FieldType type() { return FieldType::FLOAT; }

    float m_value;
};

struct IntValue : public IFieldValue
{
    virtual ~IntValue() = default;
    FieldType type() { return FieldType::INT; }

    float m_value;
};

struct SelectionValue : public IFieldValue
{
    virtual ~SelectionValue() = default;
    FieldType type() { return FieldType::SELECTION; }

    unsigned m_id;
};

using GPawnTypeId = unsigned;

//Object
struct GamePawn
{
    GPawnTypeId typeId;
    QString name;
    QPoint position;
    QBitmap icon;
        
    QVector<IFieldValue*> fieldValues;
};

using LevelData = QHash<QPoint, GamePawn>;
using PtrLevelData = std::shared_ptr<LevelData>;

struct GameData
{
    GameRules rules;
    PtrPawnTypes pPawnTypes;
    QMap<QString, PtrLevelData> levelMaps;
};


