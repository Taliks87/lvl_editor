#include "list_model_object_types.h"

ListModelObjectTypes::ListModelObjectTypes(QVector<GObjectType>* pData_, QObject* perent)
    : QAbstractListModel (perent)
    , pData(pData_)
{

}

//amount elements
int ListModelObjectTypes::rowCount(const QModelIndex &parent) const
{
    return pData->size();
}

//retune value
QVariant ListModelObjectTypes::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    switch(role){
    case Qt::DisplayRole:
        return pData->at(index.row()).name;
    default:
        return QVariant();
    }
}

////set new value
//bool ListModelObjectTypes::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if(role == Qt::EditRole)
//        (*pData)[index.row()].name = value.toString();
//    return true;
//}

//is can edit
Qt::ItemFlags ListModelObjectTypes::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
