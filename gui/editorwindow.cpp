#include "gui/editorwindow.h"
#include "ui_editorwindow.h"
#include "gui/dialog_enter_level.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QDebug>

namespace gui {

    EditorWindow::EditorWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::EditorWindow),
        windowLevel(new DialogEnterLevel(this)),
        levelEvent(LevelEvent::none)
    {
        ui->setupUi(this);        
        connect(windowLevel, SIGNAL(enter_name(QString)), this, SLOT(enter_level(QString)));
    }

    EditorWindow::~EditorWindow()
    {
        delete windowLevel;
        delete ui;
    }

    void EditorWindow::enter_level(const QString& fileName)
    {
        QString path = QDir::currentPath() + "/data/" + fileName;
        QFile levelDataFile(path);
        QFileInfo checkFile(path);
        switch(levelEvent)
        {
        case LevelEvent::create: // create new level
            if(checkFile.exists() && checkFile.isFile())
            {
                QMessageBox::information(this, "Error", "Level with this name already exist");
            } else {
                if(!levelDataFile.open(QFile::WriteOnly))
                {
                    QMessageBox::information(this, "Error", "Can't open level");
                } else {
                    QDataStream  stream(&levelDataFile);
                    stream.setVersion(QDataStream::Qt_5_13);
                    QByteArray fileContents = levelDataFile.readAll();
                    if(stream.status() != QDataStream::Ok)
                    {
                        QMessageBox: ss:information(this, "Error", "Error create file");
                    }
                }
            }
            break;

        case LevelEvent::load: // open level from disk
            if(!levelDataFile.open(QFile::ReadOnly))
            {
                QMessageBox::information(this, "Error", "Level not found");
            } else {
                QDataStream  stream(&levelDataFile);
                stream.setVersion(QDataStream::Qt_5_13);
                QByteArray fileContents = levelDataFile.readAll();
                if(stream.status() != QDataStream::Ok)
                {
                    QMessageBox::information(this, "Error", "Error read file");
                }
            }
            levelDataFile.flush();
            break;
        case LevelEvent::save: // save level to disk
            if(!levelDataFile.open(QFile::WriteOnly))
            {
                QMessageBox::information(this, "Error", "Can't save file");
            } else {
                QDataStream stream(&levelDataFile);
                stream.setVersion(QDataStream::Qt_5_13);
                if(stream.status() != QDataStream::Ok)
                {
                    QMessageBox::information(this, "Error", "Error write file");
                }
            }
            break;
        default:
            qDebug() << "Wrong level event";
        }
        levelDataFile.close();
        levelEvent = LevelEvent::none;
    }
}

void gui::EditorWindow::on_action_create_triggered()
{    
    windowLevel->setWindowTitle("Create level");
    windowLevel->show();
    levelEvent = LevelEvent::create;
}


