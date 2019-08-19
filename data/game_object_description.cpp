#include "data/game_object_description.h"
#include <QDebug>

void FloatDescription::deserialize(const QJsonObject& jsObj)
{
    from = static_cast<float>(jsObj["from"].toDouble());
    to = static_cast<float>(jsObj["to"].toDouble());
    if(from>to) std::swap(from, to);
}

void IntDescription::deserialize(const QJsonObject& jsObj)
{
    from = jsObj["from"].toInt();
    to = jsObj["to"].toInt();
    if(from>to) std::swap(from, to);
}

void SelectionDescription::deserialize(const QJsonObject& jsObj)
{
    QJsonArray jsArrayVariantss = jsObj["variants"].toArray();
    int amountVariants =  jsArrayVariantss.size();
    for (int i = 0; i < amountVariants; ++i)
    {
        variants.insert(jsArrayVariantss[i].toString());
    }
}

void PawnType::deserialize(const QJsonObject& jsObj, const QString& rootPath)
{        
    icon = QPixmap(rootPath + jsObj["icon"].toString());
    QJsonArray jsArrayProperties = jsObj["properties"].toArray();
    //read properties
    for (auto jsNodePropertie : jsArrayProperties)
    {
        QJsonObject jsPropertie = jsNodePropertie.toObject();
        QString type = jsPropertie["type"].toString();        
        PtrFieldDescription pPropertie;
        if( type == "float") {
            pPropertie = PtrFieldDescription(new FloatDescription);
        } else if( type == "int") {
            pPropertie = PtrFieldDescription(new IntDescription);
        } else if( type == "selection") {
            pPropertie = PtrFieldDescription(new SelectionDescription);
        } else {
            continue;
        }
        pPropertie->deserialize(jsPropertie);
        fieldDescriptions.insert(jsPropertie["name"].toString(),pPropertie);
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
