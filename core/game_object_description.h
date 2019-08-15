#pragma once

#include <memory>
#include <QDataStream>
#include <QString>
#include <QSet>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

//Description
enum FieldType
{
    FLOAT,
    INT,
    SELECTION
};

struct IFieldDescription
{
    virtual ~IFieldDescription() = default;
    virtual FieldType type() = 0;
    virtual void deserialize(const QJsonObject& jsObj) = 0;
};

using PtrFieldDescription = std::shared_ptr<IFieldDescription>;

struct FloatDescription : public IFieldDescription
{
    ~FloatDescription() override = default;
    FieldType type() override { return FieldType::FLOAT; }
    void deserialize(const QJsonObject& jsObj) override;

    float from;
    float to;
};

using PtrFloatDescription = std::shared_ptr<FloatDescription>;

struct IntDescription : public IFieldDescription
{
    ~IntDescription() override = default;
    FieldType type() override { return FieldType::INT; }
    void deserialize(const QJsonObject& jsObj) override;

    int from;
    int to;
};

using PtrIntDescription = std::shared_ptr<IntDescription>;

struct SelectionDescription : public IFieldDescription
{
    ~SelectionDescription() override = default;
    FieldType type() override { return FieldType::SELECTION; }
    void deserialize(const QJsonObject& jsObj) override;

    QSet<QString> variants;
};

using PtrSelectionDescription = std::shared_ptr<SelectionDescription>;

struct GameRules
{
    GameRules() : mapSize(30,15), mapAmountPawns(){}
    void deserialize(QJsonValue& jsValue);

    const QPoint mapSize;
    QHash<QString, int> mapAmountPawns;
};

struct PawnType
{
    void deserialize(const QJsonObject& jsObj, const QString& rootPath);

    QPixmap icon;
    QHash<QString, PtrFieldDescription> pFieldDescriptions;
};

using PawnTypes = QHash<QString, PawnType>;

//TODO::is need?
inline QDataStream& operator<<(QDataStream& stream, const PtrFieldDescription& fieldDescription);
inline QDataStream& operator>>(QDataStream& stream, PtrFieldDescription& fieldDescription);
inline QDataStream& operator<<(QDataStream& stream, const PawnType& objectType);
inline QDataStream& operator>>(QDataStream& stream, PawnType& objectType);
//QDataStream& operator<<(QDataStream& stream, const QVector<GObjectType>& objectTypes);
//QDataStream& operator>>(QDataStream& stream, QVector<GObjectType>& objectTypes);






