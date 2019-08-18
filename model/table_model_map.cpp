#include "model/table_model_map.h"
#include "gui/widget_map.h"
#include <QBrush>
#include <QFont>
#include <QPixmap>
#include <QMap>
#include <QMimeData>
#include <QPoint>
#include <QColor>
#include <QDropEvent>
#include <QItemSelection>
#include <QDebug>

TableModelMap::TableModelMap(GameData& data, QObject* perent)
    : QAbstractTableModel (perent)
    , pGameData(&data)
    , pRules(&data.rules)
    , pPawnTypes(&data.pawnTypes)
    , pLevelMaps(nullptr)
    , mimeList({"lvl_editor/pawn.type", "lvl_editor/pawn.onMap"})
{    
}

void TableModelMap::refreshLevelData(const QString& levelName)
{
    pLevelMaps = &pGameData->levelsData[levelName].map;
    pLevelStutistic = &pGameData->levelsData[levelName].statistic;
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
                    case Qt::ToolTipRole:
                        return gamePawn.name;                                        
                    case Qt::DecorationRole:                        
                        if(gamePawn.icon)
                        {
                            return gamePawn.icon->scaled(32,32);
                        } else {
                            auto it = pPawnTypes->find(gamePawn.typeName);
                            if(it != pPawnTypes->end())
                            {
                                gamePawn.icon = &it->icon;
                                return gamePawn.icon->scaled(32,32);
                            }
                        }
                        break;
                    case Qt::BackgroundRole:
                        return QBrush(QColor(50,50,50));
                }
            } else {
                //empty pawn
                switch(role){
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

bool TableModelMap::setRolesData(const QModelIndex& index, const QVariant &value, int role)
{    
    if(pLevelMaps && index.isValid())
    {
        if (role == Qt::EditRole) {
            if(checkIndex(index) && value.isNull()) // remove pawn
            {
                GamePawn& gamePawn = (*pLevelMaps)[index.column()][index.row()];
                auto it = pLevelStutistic->find(gamePawn.typeName);
                if( it != pLevelStutistic->end() )
                {
                    --(it.value());
                } else {
                    qWarning() << "Type name not found" << gamePawn.typeName;
                }
                (gamePawn = GamePawn());
                emit change_completed(index);
            }
            return true;
        }
    }
    return false;
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
                return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled;
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
    return mimeList;
}

QMimeData* TableModelMap::mimeData(const QModelIndexList& indexes) const
{
    QMimeData* mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            stream << index.column() << index.row();
        }
    }

    mimeData->setData("lvl_editor/pawn.onMap", encodedData);

    return mimeData;
}

bool TableModelMap::canDropMimeData(const QMimeData* /*data*/, Qt::DropAction /*action*/, int /*row*/, int /*column*/, const QModelIndex &parent) const
{    
    return ( parent.isValid() && (*pLevelMaps)[parent.column()][parent.row()].typeName.isEmpty() );
}

bool TableModelMap::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int /*row*/, int /*column*/, const QModelIndex &parentIndex)
{
    if (!parentIndex.isValid())
        return false;
    if (action == Qt::IgnoreAction)
        return true;
    int perentColumn = parentIndex.column();
    int perentRow = parentIndex.row();
    //drop pawns type
    if (data->hasFormat(mimeList[0]))
    {
        QByteArray encodedData = data->data(mimeList[0]);
        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        QString typeName;
        stream >> typeName;
        PawnTypes::const_iterator itPawnTypes = pPawnTypes->find(typeName);
        if(itPawnTypes != pPawnTypes->end())
        {
            GamePawn& newPown = ((*pLevelMaps)[perentColumn][perentRow] = GamePawn());
            newPown.typeName = typeName;
            auto it = pLevelStutistic->find(typeName);
            if( it == pLevelStutistic->end() )
            {
                it = pLevelStutistic->insert(typeName,0);
            } else {
                ++(it.value());
            }
            newPown.name = QString("pawn_") + typeName + QString("_") + QString::number(it.value());
            newPown.icon = &(itPawnTypes->icon);
            for(auto itDescription = itPawnTypes->fieldDescriptions.begin(); itDescription != itPawnTypes->fieldDescriptions.end(); ++itDescription)
            {
                auto& pDescription = itDescription.value();
                switch (pDescription->type())
                {
                    case FieldType::INT: {
                        PtrIntDescription pInt = std::dynamic_pointer_cast<IntDescription>(pDescription);
                        newPown.fieldValues[itDescription.key()] = PtrIFieldValue(new IntValue(pInt->from));
                        break;
                    }
                    case FieldType::FLOAT: {
                        PtrFloatDescription pFloat = std::dynamic_pointer_cast<FloatDescription>(pDescription);
                        newPown.fieldValues[itDescription.key()] = PtrIFieldValue(new FloatValue(pFloat->from));
                        break;
                    }
                case FieldType::SELECTION: {
                        PtrSelectionDescription pSelection = std::dynamic_pointer_cast<SelectionDescription>(pDescription);
                        newPown.fieldValues[itDescription.key()] = PtrIFieldValue(new SelectionValue(*pSelection->variants.begin()));
                        break;
                    }
                }
            }            
        } else {
            return false;
        }
    }

    //drop pawn, move pawn on a map
    if (data->hasFormat(mimeList[1])) {
        QByteArray encodedData = data->data(mimeList[1]);
        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        int columnMovedPawn;
        int rowMovedPawn;
        stream >> columnMovedPawn >> rowMovedPawn;
        GamePawn& movedPawn = (*pLevelMaps)[columnMovedPawn][rowMovedPawn];
        GamePawn& pawnOnArea = ((*pLevelMaps)[perentColumn][perentRow] = GamePawn());
        std::swap(movedPawn, pawnOnArea);

    }    
    emit change_completed(parentIndex);

    return true;
}


