#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLocale>
#include <QMessageBox>
#include <QSettings>
#include <QVBoxLayout>

#include "config.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(PROJECT_DISPLAY_NAME);

    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::showSettings);
    connect(ui->actionAbout, &QAction::triggered, this, [this]() {
        QMessageBox::about(
            this,
            tr("About %1").arg(PROJECT_DISPLAY_NAME),
            "<p><b>" PROJECT_DISPLAY_NAME " " PROJECT_VERSION "</b></p><p>"
            + tr("A template for creating Qt Widgets desktop applications.")
            + "</p><p><a href='" PROJECT_URL "'>" PROJECT_URL "</a></p>"
        );
    });
    connect(ui->actionAbout_Qt, &QAction::triggered, this, [this]() {
        QMessageBox::aboutQt(this);
    });

    QSettings settings;

    if (settings.value("windowGeometry").isValid())
        restoreGeometry(settings.value("windowGeometry").toByteArray());
}

MainWindow::~MainWindow()
{
    QSettings settings;

    settings.setValue("windowGeometry", saveGeometry());

    delete ui;
}

void MainWindow::showSettings()
{
    QSettings settings;

    auto dialog = new QDialog(this);
    dialog->setWindowTitle(tr("Settings"));

    auto label = new QLabel;
    label->setText(tr("Language (requires restart):"));

    auto select = new QComboBox;
    for (const auto &lang : Utils::languages()) {
        QLocale locale(lang);
        QString displayString(QLocale::languageToString(locale.language()));
        if (lang.contains("_"))
            displayString += " (" + QLocale::countryToString(locale.country()) + ")";
        select->addItem(displayString, lang);
    }

    QString lang = settings.value("language").toString();
    int index = select->findData(lang);
    if (index == -1)
        index = select->findData(lang.left(2));
    select->setCurrentIndex(index);

    auto buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttons, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, dialog, &QDialog::reject);

    dialog->setLayout(new QVBoxLayout);
    dialog->layout()->addWidget(label);
    dialog->layout()->addWidget(select);
    dialog->layout()->addWidget(buttons);

    int dialogResult = dialog->exec();
    QVariant data = select->currentData();

    delete dialog;

    if (dialogResult == QDialog::Accepted)
        settings.setValue("language", data);
}
