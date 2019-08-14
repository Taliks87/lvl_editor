#include "list_model_object_types.h"
#include <QBrush>
#include <QFont>
#include <QPixmap>
#include <QMap>

ListModelObjectTypes::ListModelObjectTypes(GameData* pData, QObject* perent)
    : QAbstractListModel (perent)
    , pRules(&pData->rules)
    , pPawnTypes(pData->pPawnTypes)
{    
}

//amount elements
int ListModelObjectTypes::rowCount(const QModelIndex& /*parent*/) const
{
    return pPawnTypes->size();
}

//retune value
QVariant ListModelObjectTypes::data(const QModelIndex& index, int role) const
{        
    auto& name = pPawnTypes->at(index.row()).name;
    if(!index.isValid())
        return QVariant();
    switch(role){
    case Qt::DisplayRole:
//    case Qt::EditRole:
        return name;
    case Qt::SizeHintRole:
        return QSize(0, 25);
    case Qt::ToolTipRole:
        return name;
    case Qt::TextAlignmentRole:
        return Qt::AlignHCenter;
    case Qt::FontRole:
        return QFont("Times New Roman", 12, QFont::Bold);
    case Qt::BackgroundRole:
        return QBrush(Qt::gray);
    case Qt::DecorationRole:
        return pPawnTypes->at(index.row()).icon;
    default:
        return QVariant();
    }    
}

////set new value
//bool ListModelObjectTypes::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if(role == Qt::EditRole)
//        (*pPawnTypes)[index.row()].name = value.toString();
//    return true;
//}

//is can edit
Qt::ItemFlags ListModelObjectTypes::flags(const QModelIndex& index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

//Qt::DropActions ListModelObjectTypes::supportedDragActions() const
//{
//    return Qt::CopyAction;
//}

//Qt::DropActions ListModelObjectTypes::supportedDropActions() const
//{
//    return Qt::CopyAction;
//}
