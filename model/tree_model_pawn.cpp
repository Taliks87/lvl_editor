#include "tree_model_pawn.h"
#include <QStringList>

TreeModelPawn::TreeModelPawn(GameData& data, QObject* perent)
    : QAbstractTableModel (perent)
    , pGameData(&data)
    , pPawnTypes(&data.pawnTypes)
    , pLevelMaps(nullptr)
    , pSelectPawn(nullptr)
    , pawnPos()
{
}

void TreeModelPawn::refreshLevelData(const QString& levelName)
{
    pLevelMaps = &pGameData->levelsData[levelName].map;
    pSelectPawn = nullptr;
}

void TreeModelPawn::selectPawn(const QModelIndex& index)
{
    pawnPos = QPoint(index.column(), index.row());
    QMessageLogger();
    pSelectPawn = &(*pLevelMaps)[pawnPos.x()][pawnPos.y()];
}

int TreeModelPawn::rowCount(const QModelIndex& /*parent*/) const
{
    if(pSelectPawn && !pSelectPawn->typeName.isEmpty())
        return pSelectPawn->fieldValues.size() + AMOUNT_COMMON_FIELD;
    return 0;
}

int TreeModelPawn::columnCount(const QModelIndex& /*parent*/) const
{
    return 2;
}

QVariant TreeModelPawn::data(const QModelIndex& index, int role) const
{
    if(pSelectPawn && !pSelectPawn->typeName.isEmpty() && index.isValid())
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

        switch(row){
            case TYPE_NAME_FIELD:
                if(col == 0) {
                    switch(role){
                        case Qt::DisplayRole:
                            return "Type";
                    }
                } else {
                    switch(role){
                        case Qt::DisplayRole:
                            return pSelectPawn->typeName;
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
                            return pSelectPawn->name;
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
            auto it = pSelectPawn->fieldValues.begin();
            it += index.row() - AMOUNT_COMMON_FIELD;
            auto& fildName = it.key();
            if(col == 0) {
                switch(role){
                    case Qt::DisplayRole:
                        return fildName;
                    case Qt::ToolTipRole:
                        return fildName;
                }
            } else {
                const PtrIFieldValue& pFieldValue = it.value();
                switch(pFieldValue->type())
                {
                    case FieldType::INT: {
                            PtrIntValue pInt = std::dynamic_pointer_cast<IntValue>(pFieldValue);
                            if(role == Qt::DisplayRole)
                            {
                                return pInt->value;
                            }
                        } break;
                    case FieldType::FLOAT: {
                            PtrFloatValue pFloat = std::dynamic_pointer_cast<FloatValue>(pFieldValue);
                            if(role == Qt::DisplayRole)
                            {
                                return pFloat->value;
                            }
                        } break;
                    case FieldType::SELECTION: {
                            PtrSelectionValue pSelection = std::dynamic_pointer_cast<SelectionValue>(pFieldValue);
                            if(role == Qt::DisplayRole)
                            {
                                return pSelection->value;//QVariantList
                            }
                        } break;
                }
            }
        }
    }
    return QVariant();
}

bool TreeModelPawn::setRolesData(const QModelIndex &/*index*/, const QVariant &/*value*/, int /*role*/)
{
    return true;
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
