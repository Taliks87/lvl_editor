#include "gui/editorwindow.h"
#include "gui/dialog_enter_level.h"
#include "gui/widget_object_types.h"
#include "gui/widget_map.h"
#include "gui/widget_objects.h"
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
    widgetMap(nullptr),
    widgetObjects(nullptr),
    rootPath(QDir::currentPath() + "/data/"),
    configPath(rootPath + "/config.json"),
    gameData(),
    levelEvent(LevelEvent::none),
    levelName("")
{    
    ui->setupUi(this);
    widgetObjectTypes = new WidgetObjectTypes(gameData, ui->centralWidget);
    widgetMap = new WidgetMap(gameData, ui->centralWidget);
    widgetObjects = new WidgetObjects(gameData, ui->centralWidget);
    ui->horizontalLayout->addWidget(widgetObjectTypes);
    ui->horizontalLayout->addWidget(widgetMap);
    ui->horizontalLayout->addWidget(widgetObjects);
    connect(dialogLevelName, SIGNAL(enter_name(QString)), this, SLOT(enter_level(QString)));    
    connect(widgetMap, SIGNAL(select_pawn(const QModelIndex&)), widgetObjects, SLOT(select_pawn(const QModelIndex&)));
}

EditorWindow::~EditorWindow()
{
    delete widgetObjectTypes;
    delete widgetMap;
    delete widgetObjects;
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
        QJsonDocument jsonDoc = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObj = jsonDoc.object();
        //read rules
        QJsonValue jsNodeRules = jsonObj["rules"];        
        //read object_rules
        gameData.rules.deserialize(jsNodeRules);
        // read object type
        QJsonArray jsArrayObjTypes = jsonObj["pawn_types"].toArray();
        int amountObjTypes = jsArrayObjTypes.size();
        for (int i = 0; i < amountObjTypes; ++i) {
            QJsonObject jsObjType = jsArrayObjTypes[i].toObject();
            gameData.pawnTypes[ jsObjType["name"].toString() ].deserialize(jsObjType,rootPath);
        }
        widgetObjectTypes->refreshData();
    } else {        
        QMessageBox::critical(this, "Error", "Can't open config file");
    }
    configFile.close();
    fillObjectTypesView();

    levelEvent = LevelEvent::load;
    enter_level("test");
}

void EditorWindow::fillObjectTypesView()
{
//        ui->centralWidget
}

void EditorWindow::enter_level(const QString& name)
{
    QString path = QDir::currentPath() + "/data/" + name + ".lvl";
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
                QMessageBox::warning(this, "Can't create", "Can't create file");
            } else {                
                QDataStream  stream(&levelDataFile);
                stream.setVersion(QDataStream::Qt_5_13);
                GamePawn pawn;
                QVector<GamePawn> pawnRow(gameData.rules.mapSize.y(), pawn);
                LevelMap levelMap(QVector<QVector<GamePawn>>( gameData.rules.mapSize.x(), pawnRow));
                stream << levelMap;
                if(stream.status() != QDataStream::Ok)
                {
                    QMessageBox::critical(this, "Error", "Error create file");
                } else {
                    levelName = name;

                    gameData.levelsData[levelName].map = levelMap;
                    widgetObjects->setLevel(levelName);
                    widgetMap->setLevel(levelName);
                    widgetObjectTypes->setLevel(levelName);
                }
            }
        }
        break;

    case LevelEvent::load: // open level from disk
        if(!checkFile.exists() || !checkFile.isFile())
        {
            QMessageBox::warning(this, "Not found", "Lavel not found");
        } else {
            if(!levelDataFile.open(QFile::ReadOnly))
            {
                QMessageBox::warning(this, "Not found", "Level not found");
            } else {
                QDataStream  stream(&levelDataFile);
                stream.setVersion(QDataStream::Qt_5_13);
    //            QByteArray fileContents = levelDataFile.readAll();
                LevelMap levelMap;
                stream >> levelMap;
                if( (stream.status() != QDataStream::Ok) )
                {
                    QMessageBox::critical(this, "Error", "Error read file");
                } else {
                    levelName = name;
                    gameData.levelsData[levelName].map = levelMap;
                    widgetObjects->setLevel(levelName);
                    widgetMap->setLevel(levelName);
                    widgetObjectTypes->setLevel(levelName);
                }
            }
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
