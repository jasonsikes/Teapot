#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIntValidator>
#include "rendermain.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // Keep track of whether or not we are actively rendering.
    bool isRendering = false;

    // Set the enabled state of the buttons according to isRendering.
    void setButtonsEnabled();

    // The renderer main object
    RenderMain * renderer = NULL;

    // Call to kick off rendering
    void beginRender();

    bool canFindSupportFiles();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void beginButtonPressed();
    void cancelButtonPressed();
    void saveButtonPressed();
    void renderingHasEnded();
    void shutdown();
    void imageClickedAt(QPoint p);

private:
    Ui::MainWindow *ui;
    QIntValidator intFieldValidator;
};
#endif // MAINWINDOW_H
