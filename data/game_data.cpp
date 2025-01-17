#include "data/game_data.h"

LevelData::LevelData(const QPoint mapSize) :
    statistic(),
    map()
{
    GamePawn pawn;
    QVector<GamePawn> pawnRow(mapSize.y(), pawn);
    map = LevelMap(QVector<QVector<GamePawn>>( mapSize.x(), pawnRow));
}

LevelData::LevelData(LevelData&& levelData) :
    statistic(levelData.statistic),
    map(levelData.map)
{
}

LevelData& LevelData::operator=(LevelData&& levelData)
{
    if(&levelData == this)
        return *this;

    statistic = levelData.statistic;
    map = levelData.map;
    return *this;
}

QDataStream& operator<<(QDataStream& stream, const LevelData& levelData)
{
    stream << levelData.statistic << levelData.map;
    return stream;
}

QDataStream& operator>>(QDataStream& stream, LevelData& levelData)
{
    stream >> levelData.statistic;
    int col;
    int row;
    for(int i = 0; i < levelData.statistic.amountPawn; ++i)
    {
        stream >> col >> row;
        stream >> levelData.map[col][row];
    }
    return stream;
}

QDataStream& operator<<(QDataStream& stream, const LevelStatistic& levelStatistic)
{
    stream << levelStatistic.amountPawn << levelStatistic.amountPawnByType;
    return stream;
}

QDataStream& operator>>(QDataStream& stream, LevelStatistic& levelStatistic)
{
    stream >> levelStatistic.amountPawn >> levelStatistic.amountPawnByType;
    return stream;
}

QDataStream& operator<<(QDataStream& stream, const LevelMap& levelMap)
{
    for(int col = 0; col < levelMap.size(); ++col)
    {
        for(int row = 0; row < levelMap[col].size(); ++row)
        {
            const GamePawn& pawn = levelMap[col][row];
            if(!pawn.typeName.isEmpty())
            {
                stream << col << row << levelMap[col][row];
            }
        }
    }

    return stream;
}

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
    }

    return stream;
}


