#pragma once

#include "data/pawn_data.h"
#include <QHash>
#include <QPoint>

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
    LevelData(const QPoint mapSize);
    LevelData(LevelData&& levelData);

    LevelData& operator=(const LevelData&) = default;
    LevelData& operator=(LevelData&& levelData);

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
