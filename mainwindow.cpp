#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "renderview.h"
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

// The MainWindow class is the main window of the application.
// In Qt, the main window is the controller.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setButtonsEnabled();
    renderer = new RenderMain(&ui->widget->image, this);

    intFieldValidator.setRange(99, 9999);
    ui->rowsField->setValidator(&intFieldValidator);
    ui->rowsField->setText("1080");
    ui->rowsField->setValidator(&intFieldValidator);

    connect(renderer, &RenderMain::setProgressRangeSignal, ui->progressBar, &QProgressBar::setRange);
    connect(renderer, &RenderMain::updateProgressSignal, ui->progressBar, &QProgressBar::setValue);
    connect(renderer, &RenderMain::updateRenderViewSignal, ui->widget, &RenderView::update);
    connect(ui->beginButton, &QPushButton::clicked, this, &MainWindow::beginButtonPressed);
    connect(ui->cancelButton, &QPushButton::clicked, this, &MainWindow::cancelButtonPressed);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveButtonPressed);
    connect(renderer, &RenderMain::renderingHasEndedSignal, this, &MainWindow::renderingHasEnded);
    connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, this, &MainWindow::shutdown);
    connect(ui->widget, &RenderView::renderPixelRequestedSignal, renderer, &RenderMain::requestRenderPixel);
    connect(ui->widget, &RenderView::newHeightSignal, ui->heightLabel, static_cast<void(QLabel::*)(int)>(&QLabel::setNum));
}



MainWindow::~MainWindow()
{
    delete renderer;
    delete ui;
}


void MainWindow::setButtonsEnabled()
{
    ui->beginButton->setEnabled( ! isRendering);
    ui->beginButton->setDefault( ! isRendering);

    ui->cancelButton->setEnabled(isRendering);
    ui->cancelButton->setDefault(isRendering);
    ui->saveButton->setEnabled( ! (isRendering || ui->widget->image.isNull()));

    ui->rowsField->setEnabled( ! isRendering);

    ui->progressBar->reset();

    extern bool enableDebug;
    enableDebug = ! isRendering;
}

void MainWindow::imageClickedAt(QPoint p)
{
    renderer->requestRenderPixel(p);
}

void MainWindow::beginButtonPressed()
{
    Q_ASSERT( ! isRendering);
    isRendering = true;
    setButtonsEnabled();
    ui->widget->beginRendering();
    beginRender();
}


void MainWindow::saveButtonPressed()
{
    Q_ASSERT( ! isRendering);
    QString filename = QFileDialog::getSaveFileName(this, "Save Image", "", "*.png");
    if (filename.isEmpty())
        return;
    ui->widget->image.save(filename);
}


void MainWindow::cancelButtonPressed()
{
    Q_ASSERT(isRendering);
    renderer->cancelRendering();
}


void MainWindow::shutdown()
{
    if (isRendering)
        renderer->cancelRendering();
}


void MainWindow::renderingHasEnded()
{
    Q_ASSERT(isRendering);
    isRendering = false;
    setButtonsEnabled();
}


void MainWindow::beginRender()
{
    if ( ! canFindSupportFiles())
        return;

    int imageRows = ui->rowsField->text().toInt();
    int imageColumns = imageRows * 16 / 9; // Keep 1920 x 1080 ratio
    ui->widget->image = QImage(imageColumns, imageRows, QImage::Format_RGB32);
    if (ui->widget->image.isNull()) {
        qDebug() <<"Unable to allocate memory for image!!!";
        return;
    }

    ui->widget->image.fill(Qt::lightGray);
    renderer->beginRendering();
}


bool MainWindow::canFindSupportFiles()
{
    QString prefix = FIND_FILES;
    bool canFindFiles = QFile::exists(prefix + "/" + "bunny_surface0.norm")
        && QFile::exists(prefix + "/" + "teapot_surface0.norm")
      && QFile::exists(prefix + "/" + "earth_2k.jpg");
    if ( ! canFindFiles) {
        QString message = "Unable to find support files. Please ensure that the "
           "bunny_surface0.norm, teapot_surface0.norm, and earth_2k.jpg files are in %1";
        QMessageBox::critical(this, "Error", message.arg(FIND_FILES));
    }
    return canFindFiles;
}