#include "data/pawn_data.h"

IFieldValue::~IFieldValue() = default;

FieldType FloatValue::type() { return FieldType::FLOAT; }

FieldType IntValue::type() { return FieldType::INT; }

FieldType SelectionValue::type() { return FieldType::SELECTION; }

GamePawn::GamePawn() :
    typeName(""),
    name(""),
    icon(nullptr),
    fieldValues()
{}

GamePawn::GamePawn(GamePawn&& gamePawn) :
    typeName(gamePawn.typeName),
    name(gamePawn.name),
    icon(gamePawn.icon),
    fieldValues(gamePawn.fieldValues)
{
}

GamePawn& GamePawn::operator=(GamePawn&& gamePawn)
{
    if(&gamePawn == this)
        return *this;

    typeName = gamePawn.typeName;
    name = gamePawn.name;
    icon = gamePawn.icon;
    fieldValues = gamePawn.fieldValues;

    return *this;
}
