#include "core/game_object_description.h"

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

QDataStream& operator<<(QDataStream& stream, const GObjectType& objectType)
{
    stream << objectType.name << objectType.icon << objectType.pFieldDescriptions;
    return stream;
}

QDataStream& operator>>(QDataStream& stream, GObjectType& objectType)
{
    stream >> objectType.name >> objectType.icon >> objectType.pFieldDescriptions;

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
