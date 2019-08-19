#ifndef PAWN_DATA_H
#define PAWN_DATA_H

#include "data/pawn_type.h"
#include <QString>
#include <QMap>

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
    GamePawn();
    GamePawn(const GamePawn&) = default;
    GamePawn(GamePawn&& gamePawn);

    GamePawn& operator=(const GamePawn& gamePawn) = default;
    GamePawn& operator=(GamePawn&& gamePawn);

    QString typeName;
    QString name;
    const QPixmap* icon;

    FieldValues fieldValues;
};

#endif // PAWN_DATA_H
