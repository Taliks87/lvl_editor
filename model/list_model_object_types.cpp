#include "list_model_object_types.h"
#include <QBrush>
#include <QFont>
#include <QPixmap>
#include <QMap>
#include <QHash>
#include <QMimeData>

ListModelObjectTypes::ListModelObjectTypes(GameData& data, QObject* perent)
    : QAbstractListModel (perent)
    , pGameData(&data)
    , pRules(&data.rules)
    , pLevelStutistic(nullptr)
    , pPawnTypes(&data.pawnTypes)
{    
}

void ListModelObjectTypes::refreshLevelData(const QString& levelName)
{
    pLevelStutistic = &pGameData->levelsData[levelName].statistic;
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
        return name;
    case Qt::SizeHintRole:
        return QSize(0, 25);
    case Qt::ToolTipRole:
        return name;
    case Qt::TextAlignmentRole:
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    case Qt::FontRole:
        if(isPawnLimit(index))
            return QFont("Times New Roman", 12, QFont::Thin);
        return QFont("Times New Roman", 12, QFont::Bold);
    case Qt::BackgroundRole:
        if(isPawnLimit(index))
            return QBrush(Qt::gray);
        return QBrush(Qt::white);
    case Qt::DecorationRole:
        return it->icon.scaled(24,24);
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
    return false;
}

//is can edit
Qt::ItemFlags ListModelObjectTypes::flags(const QModelIndex& index) const
{    
    if(!index.isValid())
        return Qt::NoItemFlags;
    if(isPawnLimit(index))
        return Qt::ItemIsEnabled;
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

bool ListModelObjectTypes::isPawnLimit(const QModelIndex& index) const
{
    if(pLevelStutistic)
    {
        PawnTypes::iterator itPawnTypes = pPawnTypes->begin();
        itPawnTypes += index.row();
        auto& name = itPawnTypes.key();
        auto it = pRules->mapAmountPawns.find(name);

        return (it != pRules->mapAmountPawns.end()) && ((*pLevelStutistic)[name] >= pRules->mapAmountPawns[name]);
    }
    return true;
}

