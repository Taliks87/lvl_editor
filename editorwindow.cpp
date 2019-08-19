#include "editorwindow.h"
#include "dialog_windows/dialog_enter_level.h"
#include "pawn_type/widget_object_types.h"
#include "map/widget_map.h"
#include "pawn_info/widget_objects.h"
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
    activelevelName("")
{    
    ui->setupUi(this);
    setFixedSize(1493, 547);

    widgetObjectTypes = new WidgetObjectTypes(gameData, ui->centralWidget);
    widgetMap = new WidgetMap(gameData, ui->centralWidget);
    widgetObjects = new WidgetObjects(gameData, ui->centralWidget);
    ui->horizontalLayout->addWidget(widgetObjectTypes);
    ui->horizontalLayout->addWidget(widgetMap);
    ui->horizontalLayout->addWidget(widgetObjects);

    connect(dialogLevelName, SIGNAL(enter_name(QString)), this, SLOT(enter_level(QString)));    
    connect(widgetMap, SIGNAL(select_pawn(const QModelIndex&)), widgetObjects, SLOT(select_pawn(const QModelIndex&)));

    QFile configFile(configPath);
    QFileInfo checkFile(configPath);
    if(checkFile.exists() && checkFile.isFile())
    {
        if( configFile.open(QFile::ReadOnly | QIODevice::Text) )
        {
            //load config.json
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
            configFile.flush();
        } else {
            QMessageBox::critical(this, "Error", "Can't open config file");
        }
    } else {
        QMessageBox::warning(this, "Create config", "Create empty data/config.json file");
        QDir dir(QDir::currentPath());
        if(!dir.mkpath(rootPath))
        {
            QMessageBox::critical(this, "Error", "Can't create folder data");
        } else {
            if(!configFile.open(QFile::WriteOnly | QIODevice::Text))
            {
                QMessageBox::critical(this, "Error", "Can't create config file");
            }
        }
    }

    configFile.close();
    fillObjectTypesView();

    levelEvent = LevelEvent::load;
    enter_level("test");
}

EditorWindow::~EditorWindow()
{
    delete widgetObjectTypes;
    delete widgetMap;
    delete widgetObjects;
    delete dialogLevelName;
    delete ui;
}

void EditorWindow::fillObjectTypesView()
{
//        ui->centralWidget
}

void EditorWindow::enter_level(const QString& levelname)
{
    QString path = QDir::currentPath() + "/data/" + levelname + ".lvl";
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
                QMessageBox::warning(this, "Can't create", "Can't create level");
            } else {                
                QDataStream  stream(&levelDataFile);
                stream.setVersion(QDataStream::Qt_5_13);
                LevelData levelData(gameData.rules.mapSize);
                stream << levelData;
                if(stream.status() != QDataStream::Ok)
                {
                    QMessageBox::critical(this, "Error", "Error create file");
                } else {
                    activelevelName = levelname;

                    gameData.levelsData[activelevelName] = std::move(levelData);
                    widgetObjects->setLevel(activelevelName);
                    widgetMap->setLevel(activelevelName);
                    widgetObjectTypes->setLevel(activelevelName);
                }
            }
        }
        break;
    case LevelEvent::save:
        if(!levelDataFile.open(QFile::WriteOnly))
        {
            QMessageBox::warning(this, "Can't save", "Can't save level");
        } else {
            QDataStream stream(&levelDataFile);
            stream.setVersion(QDataStream::Qt_5_13);
            stream << gameData.levelsData[activelevelName];
            if(stream.status() != QDataStream::Ok)
            {
                QMessageBox::critical(this, "Error", "Error write to file");
            }
        }
        break;
    case LevelEvent::load: // open level from disk
        if(activelevelName != levelname)
        {
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

                    LevelData levelData(gameData.rules.mapSize);
                    stream >> levelData;
                    if( (stream.status() != QDataStream::Ok) )
                    {
                        QMessageBox::critical(this, "Error", "Error read file");
                    } else {
                        activelevelName = levelname;
                        gameData.levelsData[activelevelName] = std::move(levelData);
                        widgetObjects->setLevel(activelevelName);
                        widgetMap->setLevel(activelevelName);
                        widgetObjectTypes->setLevel(activelevelName);
                    }
                    levelDataFile.flush();
                }
            }
        }
        break;
    default:
        qWarning() << "Wrong level event";
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
    levelEvent = LevelEvent::save;
    enter_level(activelevelName);
}

void EditorWindow::on_action_load_triggered()
{
    dialogLevelName->setWindowTitle("Load level");
    dialogLevelName->show();
    levelEvent = LevelEvent::load;
}
