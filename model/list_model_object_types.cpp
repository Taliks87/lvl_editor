#include "list_model_object_types.h"
#include <QBrush>
#include <QFont>
#include <QPixmap>
#include <QMap>
#include <QHash>
#include <QMimeData>

ListModelObjectTypes::ListModelObjectTypes(GameData& data, QObject* perent)
    : QAbstractListModel (perent)
    , pRules(&data.rules)
    , pPawnTypes(&data.pawnTypes)
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

    PawnTypes::iterator it = pPawnTypes->begin();
    it += index.row();
    auto& name = it.key();
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
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    case Qt::FontRole:
        return QFont("Times New Roman", 12, QFont::Bold);
    case Qt::BackgroundRole:
        return QBrush(Qt::gray);
    case Qt::DecorationRole:
        return it->icon;
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

bool ListModelObjectTypes::setRolesData(const QModelIndex &/*index*/, const QVariant &/*value*/, int /*role*/)
{
    return true;
}

//is can edit
Qt::ItemFlags ListModelObjectTypes::flags(const QModelIndex& index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
}

Qt::DropActions ListModelObjectTypes::supportedDragActions() const
{
    return Qt::CopyAction;
}

//QStringList ListModelObjectTypes::mimeTypes() const
//{
//    QStringList types;
//    types << "lvl_editor/pawn.type";
//    return types;
//}

QMimeData* ListModelObjectTypes::mimeData(const QModelIndexList& indexes) const
{
    QMimeData* mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
        }
    }

    mimeData->setData("lvl_editor/pawn.type", encodedData);
    return mimeData;
}

