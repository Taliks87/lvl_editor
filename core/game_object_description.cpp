#include "core/game_object_description.h"
#include <QDebug>

void FloatDescription::deserialize(const QJsonObject& jsObj)
{
    from = static_cast<float>(jsObj["from"].toDouble());
    to = static_cast<float>(jsObj["to"].toDouble());
}

void IntDescription::deserialize(const QJsonObject& jsObj)
{
    from = jsObj["from"].toInt();
    to = jsObj["to"].toInt();
}

void SelectionDescription::deserialize(const QJsonObject& jsObj)
{
    QJsonArray jsArrayVariantss = jsObj["variants"].toArray();
    int amountVariants =  jsArrayVariantss.size();
    variants.resize(amountVariants);
    for (int i = 0; i < amountVariants; ++i)
    {
        variants[i] = jsArrayVariantss[i].toString();
    }
}

void PawnType::deserialize(const QJsonObject& jsObj, const QString& rootPath)
{
    qWarning() <<  jsObj;
    name = jsObj["name"].toString();
    //TODO: error
    icon = QPixmap(rootPath + jsObj["img"].toString());
    QJsonArray jsArrayProperties = jsObj["properties"].toArray();
    //read properties
    for (auto jsNodePropertie : jsArrayProperties)
    {
        QJsonObject jsPropertie = jsNodePropertie.toObject();
        QString type = jsPropertie["type"].toString();
        //TODO::error
        PtrFieldDescription pPropertie;
        if( type == "float") {
            pPropertie = PtrFieldDescription(new FloatDescription);
        } else if( type == "int") {
            pPropertie = PtrFieldDescription(new IntDescription);
        } else if( type == "selection") {
            pPropertie = PtrFieldDescription(new SelectionDescription);
        }
        pPropertie->deserialize(jsPropertie);
        pFieldDescriptions.insert(jsPropertie["name"].toString(),pPropertie);
    }
}

void GameRules::deserialize(QJsonValue& jsValue)
{
    //read pawn_rules
    QJsonArray jsNodeObjRules = jsValue["pawn_rules"].toArray();
    for (int i = 0; i < jsNodeObjRules.size(); ++i)
    {
        QJsonObject jsObjRules = jsNodeObjRules[i].toObject();
        mapAmountPawns.insert(jsObjRules["name"].toString(), jsObjRules["amount"].toInt());
    }
}

QDataStream& operator<<(QDataStream& stream, const PtrFieldDescription& pFieldDescription)
{
    stream << pFieldDescription->type();
    switch(pFieldDescription->type())
    {
        case FieldType::INT:
            {
                PtrIntDescription pInt = std::dynamic_pointer_cast<IntDescription>(pFieldDescription);
                stream << pInt->from << pInt->to;
            }
            break;
        case FieldType::FLOAT:
            {
                PtrFloatDescription pFloat = std::dynamic_pointer_cast<FloatDescription>(pFieldDescription);
                stream << pFloat->from << pFloat->to;
            }
            break;
        case FieldType::SELECTION:
            {
                PtrSelectionDescription pSelection = std::dynamic_pointer_cast<SelectionDescription>(pFieldDescription);
                stream << pSelection->variants;
            }
            break;
            //TODO::error
    }

    return stream;
}

QDataStream& operator>>(QDataStream& stream, PtrFieldDescription& pFieldDescription)
{
    unsigned type;
    stream >> type;
    switch(static_cast<FieldType>(type))
    {
        case FieldType::INT:
            {
                PtrIntDescription ptr = std::make_shared<IntDescription>();
                stream >> ptr->from >> ptr->to;
                pFieldDescription = ptr;
            }
            break;
        case FieldType::FLOAT:
            {
                PtrFloatDescription ptr = std::make_shared<FloatDescription>();
                stream >> ptr->from >> ptr->to;
                pFieldDescription = ptr;
            }
            break;
        case FieldType::SELECTION:
            {
                PtrSelectionDescription ptr = std::make_shared<SelectionDescription>();
                stream >> ptr->variants;
                pFieldDescription = ptr;
            }
            break;
            //TODO::error
    }

    return stream;
}

QDataStream& operator<<(QDataStream& stream, const PawnType& pawnType)
{
    stream << pawnType.name << pawnType.icon << pawnType.pFieldDescriptions;
    return stream;
}

QDataStream& operator>>(QDataStream& stream, PawnType& pawnType)
{
    stream >> pawnType.name >> pawnType.icon >> pawnType.pFieldDescriptions;

    return stream;
}

//QDataStream& operator<<(QDataStream& stream, const QVector<GObjectType>& objectTypes)
//{
//    //stream << objectType.name << objectType.icon << objectType.pFieldDescriptions;
//    return stream;
//}

//QDataStream& operator>>(QDataStream& stream, QVector<GObjectType>& objectTypes)
//{
//    //stream >> objectType.name >> objectType.icon >> objectType.pFieldDescriptions;

//    return stream;
//}
