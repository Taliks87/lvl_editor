#include "model/table_model_map.h"
#include <QBrush>
#include <QFont>
#include <QPixmap>
#include <QMap>
#include <QMimeData>
#include <QPoint>

TableModelMap::TableModelMap(GameData& data, QObject* perent)
    : QAbstractTableModel (perent)
    , pGameData(&data)
    , pRules(&data.rules)
    , pPawnTypes(&data.pawnTypes)
    , pLevelMaps(nullptr)
{
}

void TableModelMap::refreshLevelMap(const QString& levelName)
{
    pLevelMaps = &pGameData->levelMaps[levelName];
}

int TableModelMap::rowCount(const QModelIndex& /*parent*/) const
{
    if(pRules)
        return pRules->mapSize.y();
    return 0;
}

int TableModelMap::columnCount(const QModelIndex& /*parent*/) const
{
    if(pRules)
        return pRules->mapSize.x();
    return 0;
}

QVariant TableModelMap::data(const QModelIndex& index, int role) const
{
    if(pLevelMaps && index.isValid())
    {
        //game pawn
        int col =  index.column();
        int row =  index.row();
        if((pLevelMaps->size() > col) && ((*pLevelMaps)[0].size() > row))
        {
            GamePawn& gamePawn = (*pLevelMaps)[col][row];
            if(!gamePawn.typeName.isEmpty())
            {
                switch(role){
                    case Qt::DisplayRole:
                //    case Qt::EditRole:
                        return gamePawn.name;
                    case Qt::SizeHintRole:
                        return QSize(0, 25);
                    case Qt::ToolTipRole:
                        return gamePawn.name;
                    case Qt::TextAlignmentRole:
                        return Qt::AlignHCenter;
                    case Qt::FontRole:
                        return QFont("Times New Roman", 12, QFont::Bold);
                    case Qt::DecorationRole:
                        if(gamePawn.icon)
                        return *gamePawn.icon;
                }
            } else {
                //empty pawn
                switch(role){
                    case Qt::DisplayRole:
                        return "";
                    case Qt::TextColorRole:
                        return QBrush(Qt::white);
                    case Qt::BackgroundRole:
                        return QBrush(Qt::black);
                }
            }
        }
    }
    switch(role){
        case Qt::BackgroundRole:
            return QBrush(Qt::gray);
    }
    return QVariant();
}

bool TableModelMap::setRolesData(const QModelIndex &/*index*/, const QVariant &/*value*/, int /*role*/)
{
    return true;
}

Qt::ItemFlags TableModelMap::flags(const QModelIndex& index) const
{
    if(pLevelMaps && index.isValid())
    {
        int col =  index.column();
        int row =  index.row();
        if((pLevelMaps->size() > col) && ((*pLevelMaps)[0].size() > row))
        {
            GamePawn& gamePawn = (*pLevelMaps)[col][row];
            if(!gamePawn.typeName.isEmpty())
            {
                return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
            } else {
                return Qt::ItemIsEnabled | Qt::ItemIsSelectable |  Qt::ItemIsDropEnabled;
            }
        }
    }
    return Qt::NoItemFlags;
}

Qt::DropActions TableModelMap::supportedDragActions() const
{
    return Qt::CopyAction;
}

QStringList TableModelMap::mimeTypes() const
{
    QStringList types;
    types << "lvl_editor/pawn.type";
    return types;
}

bool TableModelMap::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;
    if (!data->hasFormat("lvl_editor/pawn.type"))
        return false;

    (*pLevelMaps)[column][row] = GamePawn();

    QByteArray encodedData = data->data("lvl_editor/pawn.type");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QStringList newItems;
    int rows = 0;

    while (!stream.atEnd()) {
        QString text;
        stream >> text;
        newItems << text;
        ++rows;
    }
    return true;
}


