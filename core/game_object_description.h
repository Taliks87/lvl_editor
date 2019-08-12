#pragma once

#include <memory>
#include <QDataStream>
#include <QString>
#include <QMap>
#include <QVector>

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
};

using PtrFieldDescription = std::shared_ptr<IFieldDescription>;

struct FloatDescription : public IFieldDescription
{
    virtual ~FloatDescription() = default;
    FieldType type() { return FieldType::FLOAT; }

    float from;
    float to;
};

using PtrFloatDescription = std::shared_ptr<FloatDescription>;

struct IntDescription : public IFieldDescription
{
    virtual ~IntDescription() = default;
    FieldType type() { return FieldType::INT; }

    int from;
    int to;
};

using PtrIntDescription = std::shared_ptr<IntDescription>;

struct SelectionDescription : public IFieldDescription
{
    virtual ~SelectionDescription() = default;
    FieldType type() { return FieldType::SELECTION; }

    QVector<QString> variants;
};

using PtrSelectionDescription = std::shared_ptr<SelectionDescription>;

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

struct GObjectType
{
    QString name;
    QMap<QString, PtrFieldDescription> pFieldDescriptions;
};

QDataStream& operator<<(QDataStream& stream, const PtrFieldDescription fieldDescription);
QDataStream& operator>>(QDataStream& stream, PtrFieldDescription fieldDescription);
QDataStream& operator<<(QDataStream& stream, const GObjectType& objectType);
QDataStream& operator>>(QDataStream& stream, GObjectType& objectType);





