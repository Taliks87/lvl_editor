#include "core/game_object.h"

//QDataStream& operator<<(QDataStream& stream, const LevelMap& levelMap)
//{
//    for(int col = 0; col < levelMap.size(); ++col)
//        for(int row = 0; row < levelMap[col].size(); ++row)
//            stream << levelMap[col][row];
//    return stream;
//}

//QDataStream& operator>>(QDataStream& stream, LevelMap& levelMap)
//{
//    for(int col = 0; col < levelMap.size(); ++col)
//        for(int row = 0; row < levelMap[col].size(); ++row)
//            stream >> levelMap[col][row];
//    return stream;
//}

QDataStream& operator<<(QDataStream& stream, const GamePawn& gamePawn)
{
    stream << gamePawn.typeName << gamePawn.name << gamePawn.fieldValues;
    return stream;
}

QDataStream& operator>>(QDataStream& stream, GamePawn& gamePawn)
{
    stream >> gamePawn.typeName >> gamePawn.name >> gamePawn.fieldValues;
    return stream;
}

QDataStream& operator<<(QDataStream& stream, const PtrIFieldValue& pFieldValue)
{
    stream << pFieldValue->type();
    switch(pFieldValue->type())
    {
        case FieldType::INT:
            {
                PtrIntValue pInt = std::dynamic_pointer_cast<IntValue>(pFieldValue);
                stream << pInt->value;
            }
            break;
        case FieldType::FLOAT:
            {
                PtrFloatValue pFloat = std::dynamic_pointer_cast<FloatValue>(pFieldValue);
                stream << pFloat->value;
            }
            break;
        case FieldType::SELECTION:
            {
                PtrSelectionValue pSelection = std::dynamic_pointer_cast<SelectionValue>(pFieldValue);
                stream << pSelection->value;
            }
            break;
        //TODO::error
    }

    return stream;
}

QDataStream& operator>>(QDataStream& stream, PtrIFieldValue& pFieldValue)
{
    unsigned type;
    stream >> type;
    switch(static_cast<FieldType>(type))
    {
        case FieldType::INT:
            {
                PtrIntValue ptr = std::make_shared<IntValue>();
                stream >> ptr->value;
                pFieldValue = ptr;
            }
            break;
        case FieldType::FLOAT:
            {
                PtrFloatValue ptr = std::make_shared<FloatValue>();
                stream >> ptr->value;
                pFieldValue = ptr;
            }
            break;
        case FieldType::SELECTION:
            {
                PtrSelectionValue ptr = std::make_shared<SelectionValue>();
                stream >> ptr->value;
                pFieldValue = ptr;
            }
            break;
            //TODO::error
    }

    return stream;
}
