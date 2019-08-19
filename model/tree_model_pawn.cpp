#include "tree_model_pawn.h"
#include <QStringList>
#include <QDebug>

TreeModelPawn::TreeModelPawn(GameData& data, QObject* perent)
    : QAbstractTableModel (perent)
    , pGameData(&data)
    , pPawnTypes(&data.pawnTypes)
    , pLevelMaps(nullptr)
    , pSelectedPawn(nullptr)
    , pFieldDescriptions(nullptr)
    , pawnPos()
{
}

void TreeModelPawn::refreshLevelData(const QString& levelName)
{
    pLevelMaps = &pGameData->levelsData[levelName].map;
    pSelectedPawn = nullptr;
    pFieldDescriptions = nullptr;
}

void TreeModelPawn::selectPawn(const QModelIndex& index)
{
    if(pLevelMaps != nullptr)
    {
        pawnPos = QPoint(index.column(), index.row());
        pSelectedPawn = &(*pLevelMaps)[pawnPos.x()][pawnPos.y()];
        auto itPawnType = pPawnTypes->find(pSelectedPawn->typeName);
        if(itPawnType != pPawnTypes->end())
        {
            if(!itPawnType->isEmpty())
            {
                QMessageLogger();

                pFieldDescriptions = &itPawnType->fieldDescriptions;
            } else {
                pSelectedPawn = nullptr;
                pFieldDescriptions = nullptr;
            }
        }
    }
}

int TreeModelPawn::rowCount(const QModelIndex& /*parent*/) const
{
    if(pSelectedPawn && !pSelectedPawn->typeName.isEmpty())
    {
        if(pFieldDescriptions)
            return pSelectedPawn->fieldValues.size() + AMOUNT_COMMON_FIELD;
        return AMOUNT_COMMON_FIELD;
    }

    return 0;
}

int TreeModelPawn::columnCount(const QModelIndex& /*parent*/) const
{
    return 2;
}

QVariant TreeModelPawn::data(const QModelIndex& index, int role) const
{
    if(pSelectedPawn && !pSelectedPawn->typeName.isEmpty() && index.isValid())
    {
        //game pawn
        int col =  index.column();
        int row =  index.row();
        if((row < NAME_FIELD) && role == Qt::BackgroundRole)
            return QBrush(Qt::gray);

        switch(role){
            case Qt::TextAlignmentRole:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
            case Qt::FontRole:
                return QFont("Times New Roman", 10, QFont::Thin);
        }
        //Common fields
        switch(row){
            case TYPE_NAME_FIELD:
                if(col == 0) {
                    switch(role){
                        case Qt::DisplayRole:
                            return "Pawns type";
                    }
                } else {
                    switch(role){
                        case Qt::DisplayRole:
                            return pSelectedPawn->typeName;
                    }
                }
            break;
            case NAME_FIELD:
                if(col == 0) {
                    switch(role){
                        case Qt::DisplayRole:
                            return "Name";
                    }
                } else {
                    switch(role){
                        case Qt::DisplayRole:
                            return pSelectedPawn->name;
                    }
                }
            break;
            case POSITION_FIELD:
                if(col == 0) {
                    switch(role){
                        case Qt::DisplayRole:
                            return "Position";
                    }
                } else {
                    switch(role){
                        case Qt::DisplayRole:
                            return QString::number(pawnPos.x()) + QString("x") + QString::number(pawnPos.y());
                    }
                }
            break;

        default:
            {
                if(pFieldDescriptions == nullptr) return QVariant();
                //Other fields
                auto itPawn = pSelectedPawn->fieldValues.begin();
                itPawn += index.row() - AMOUNT_COMMON_FIELD;
                auto& fildName = itPawn.key();
                auto itDescription = pFieldDescriptions->find(fildName);
                bool isDescriptionExist = ( itDescription != pFieldDescriptions->end() );
                bool error = !isDescriptionExist;
                //field exist in field descriptions
                if(col == 0) {
                    //column field name
                    switch(role){
                        case Qt::DisplayRole:
                            return fildName;
                        case Qt::ToolTipRole:
                            return fildName;
                    }
                } else {
                    if(!isDescriptionExist) return QVariant();
                    //column field value
                    const PtrFieldDescription& pFieldDescription = itDescription.value();
                    const PtrIFieldValue& pFieldValue = itPawn.value();

                    if(pFieldValue->type() == itDescription.value()->type())
                    {
                        switch(pFieldValue->type())
                        {
                            case FieldType::INT: {
                                PtrIntDescription pIntType = std::dynamic_pointer_cast<IntDescription>(pFieldDescription);
                                PtrIntValue pInt = std::dynamic_pointer_cast<IntValue>(pFieldValue);
                                if(role == Qt::DisplayRole || role == Qt::EditRole )
                                {
                                    return pInt->value;
                                } else if(role == Qt::ToolTipRole) {
                                    return QString("frmo %1 to %2").arg(QString::number(pIntType->from), QString::number(pIntType->to));
                                } else if(role == Qt::WhatsThisPropertyRole ) {
                                    return QPoint(pIntType->from, pIntType->to);
                                } else if(role == Qt::BackgroundRole ) {
                                    error = ( (pInt->value < pIntType->from) || (pInt->value > pIntType->to) );
                                }
                            } break;

                            case FieldType::FLOAT: {
                                PtrFloatDescription pFloatType = std::dynamic_pointer_cast<FloatDescription>(pFieldDescription);
                                PtrFloatValue pFloat = std::dynamic_pointer_cast<FloatValue>(pFieldValue);
                                if(role == Qt::DisplayRole || role == Qt::EditRole )
                                {
                                    return pFloat->value;
                                } else if(role == Qt::ToolTipRole) {
                                    QString::number(static_cast<double>(pFloatType->from));
                                    return QString("frmo %1 to %2").arg(QString::number(static_cast<double>(pFloatType->from)),
                                                                        QString::number(static_cast<double>(pFloatType->to)));
                                } else if(role == Qt::WhatsThisPropertyRole ) {
                                    return QPointF(static_cast<double>(pFloatType->from),
                                                   static_cast<double>(pFloatType->to));
                                } else if(role == Qt::BackgroundRole ) {
                                    error = ( (pFloat->value < pFloatType->from) || (pFloat->value > pFloatType->to) );
                                }
                            } break;

                            case FieldType::SELECTION: {
                                PtrSelectionValue pSelection = std::dynamic_pointer_cast<SelectionValue>(pFieldValue);
                                PtrSelectionDescription pSelectionType = std::dynamic_pointer_cast<SelectionDescription>(pFieldDescription);
                                if(role == Qt::WhatsThisPropertyRole)
                                {
                                    QStringList list;
                                    list.push_back(pSelection->value);
                                    for(const QString& variant : pSelectionType->variants)
                                    {
                                        if(variant != pSelection->value)
                                        {
                                            list.push_back(variant);
                                        }
                                    }
                                    return list;
                                } else if(role == Qt::DisplayRole || role == Qt::EditRole )
                                {
                                    return pSelection->value;
                                } else if(role == Qt::BackgroundRole ) {
                                    error = ( pSelectionType->variants.find(pSelection->value) == pSelectionType->variants.end() );
                                }
                            } break;
                        }
                    } else {
                        error = true;
                    }
                }
                if(error && (role == Qt::BackgroundRole))
                    return QBrush(Qt::red);
            }
        }
    }

    return QVariant();
}

bool TreeModelPawn::setRolesData(const QModelIndex& index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        if(pSelectedPawn && !pSelectedPawn->typeName.isEmpty() && index.isValid())
        {
            int col =  index.column();
            int row =  index.row();
            //Common fields
            if(row == NAME_FIELD)
            {
                pSelectedPawn->name = value.toString();
                return true;
            } else {
                //Other fields
                auto itPawn = pSelectedPawn->fieldValues.begin();
                itPawn += index.row() - AMOUNT_COMMON_FIELD;
                //column field value
//                auto itDescription = (*pFieldDescriptions).begin();
//                itDescription += index.row() - AMOUNT_COMMON_FIELD;
//                const PtrFieldDescription& pFieldDescription = itDescription.value();
                const PtrIFieldValue& pFieldValue = itPawn.value();
//                if(pFieldValue->type() == itDescription.value()->type())
                switch(pFieldValue->type())
                {
                    case FieldType::INT: {
//                        PtrIntDescription pIntType = std::dynamic_pointer_cast<IntDescription>(pFieldDescription);

                        PtrIntValue pInt = std::dynamic_pointer_cast<IntValue>(pFieldValue);
                        pInt->value = value.toInt();
                        return true;

                    }
                    case FieldType::FLOAT: {
//                        PtrFloatDescription pFloatType = std::dynamic_pointer_cast<FloatDescription>(pFieldDescription);
                        PtrFloatValue pFloat = std::dynamic_pointer_cast<FloatValue>(pFieldValue);
                        pFloat->value = value.toFloat();
                        return true;

                    }
                    case FieldType::SELECTION: {
//                            PtrSelectionDescription pSelectionType = std::dynamic_pointer_cast<SelectionDescription>(pFieldDescription);
                        PtrSelectionValue pSelection = std::dynamic_pointer_cast<SelectionValue>(pFieldValue);
                        pSelection->value = value.toString();
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

Qt::ItemFlags TreeModelPawn::flags(const QModelIndex& index) const
{
    if( (index.column() == 1) && (index.row() > POSITION_FIELD))
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModelPawn::headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if(section == 0)
            return QString("Field");
        else
            return QString("Value");
    }
    if (role == Qt::FontRole)
    {
        QFont serifFont("Times New Roman", 10, QFont::Bold, true);
        return serifFont;
    }

//    if (role == Qt::TextAlignmentRole)
//    {
//        return Qt::AlignRight;
//    }

//    if (role == Qt::BackgroundRole)
//    {
//        return QBrush(Qt::blue);
//    }

//    if (role == Qt::ForegroundRole)
//    {
//        return QBrush(Qt::red);
//    }

    return QVariant();
}
