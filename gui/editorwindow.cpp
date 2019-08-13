#include "gui/editorwindow.h"
#include "gui/dialog_enter_level.h"
#include "gui/widget_object_types.h"
#include "ui_editorwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

EditorWindow::EditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorWindow),
    dialogLevelName(new DialogEnterLevel(this)),
    widgetObjectTypes(nullptr),
    rootPath(QDir::currentPath() + "/data/"),
    configPath(rootPath + "/config.json"),
    gObjectTypes(),
    gRules(),
    levelEvent(LevelEvent::none),
    levelName("")
{
    ui->setupUi(this);
    widgetObjectTypes = new WidgetObjectTypes(&gObjectTypes, ui->centralWidget);
    ui->horizontalLayout->addWidget(widgetObjectTypes);
    connect(dialogLevelName, SIGNAL(enter_name(QString)), this, SLOT(enter_level(QString)));

}

EditorWindow::~EditorWindow()
{
    delete widgetObjectTypes;
    delete dialogLevelName;
    delete ui;
}

void EditorWindow::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );
    QFile configFile(configPath);
    QFileInfo checkFile(configPath);
    if(checkFile.exists() && checkFile.isFile() && configFile.open(QFile::ReadOnly | QIODevice::Text))
    {
        QString val = configFile.readAll();
        qWarning() << val;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObj = jsonDoc.object();
        //rules
        QJsonValue jsNodeRules = jsonObj["rules"];
        qWarning() << jsNodeRules;
        //object_rules
        QJsonArray jsNodeObjRules = jsNodeRules["object_rules"].toArray();
        for (int npcIndex = 0; npcIndex < jsNodeObjRules.size(); ++npcIndex) {
            QJsonObject objectRules = jsNodeObjRules[npcIndex].toObject();
            qWarning() <<  objectRules;
            gRules.mapAmountObjects.insert(objectRules["name"].toString(), objectRules["amount"].toInt());
        }
    } else {
        QMessageBox::critical(this, "Error", "Can't open config file");
    }
    configFile.close();
    fillObjectTypesView();
}

void EditorWindow::fillObjectTypesView()
{
//        ui->centralWidget
}

void EditorWindow::enter_level(const QString& name)
{
    QString path = QDir::currentPath() + "/data/" + name;
    QFile levelDataFile(path);
    QFileInfo checkFile(path);
    switch(levelEvent)
    {
    case LevelEvent::create: // create new level
        if(checkFile.exists() && checkFile.isFile())
        {
            QMessageBox::warning(this, "Can't create", "Level with this name already exist");
        } else {
            if(!levelDataFile.open(QFile::WriteOnly))
            {
                QMessageBox::critical(this, "Error", "Can't open level");
            } else {
                levelName = name;
//                    QDataStream  stream(&levelDataFile);
//                    stream.setVersion(QDataStream::Qt_5_13);
//                    if(stream.status() != QDataStream::Ok)
//                    {
//                        QMessageBox::critical(this, "Error", "Error create file");
//                    }
            }
        }
        break;

    case LevelEvent::load: // open level from disk
        if(!levelDataFile.open(QFile::ReadOnly))
        {
            QMessageBox::warning(this, "Not found", "Level not found");
        } else {
            QDataStream  stream(&levelDataFile);
            stream.setVersion(QDataStream::Qt_5_13);
//                QByteArray fileContents = levelDataFile.readAll();

//                if( (stream.status() != QDataStream::Ok) )
//                {
//                    QMessageBox::critical(this, "Error", "Error read file");
//                } else {
                levelName = name;
//                }
        }
        break;
    default:
        qDebug() << "Wrong level event";
    }
    levelDataFile.close();
    levelEvent = LevelEvent::none;
}

void EditorWindow::on_action_create_triggered()
{    
    dialogLevelName->setWindowTitle("Create level");
    dialogLevelName->show();
    levelEvent = LevelEvent::create;
}



void EditorWindow::on_action_save_triggered()
{
//    if(!levelDataFile.open(QFile::WriteOnly))
//    {
//        QMessageBox::warning(this, "Can't save", "Can't save level");
//    } else {
//        QDataStream stream(&levelDataFile);
//        stream.setVersion(QDataStream::Qt_5_13);
//        if(stream.status() != QDataStream::Ok)
//        {
//            QMessageBox::critical(this, "Error", "Error write to file");
//        }
//    }
}
