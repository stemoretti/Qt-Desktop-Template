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

    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::showSettings);
    connect(ui->actionAbout, &QAction::triggered, this, [this]() {
        QMessageBox::about(
            this,
            tr("About %1").arg(PROJECT_NAME),
            tr("<b>%1 %2</b>"
               "<p>A template for creating Qt-based desktop applications.</p>"
               "<p>See <a href='https://github.com/stemoretti/qt-desktop-template'>"
               "github.com/stemoretti/qt-desktop-template</a> for more "
               "informations.</p>"
               "<p>Copyright &copy; 2019 Stefano Moretti <a "
               "href='mailto:stemoretti@gmx.com'>stemoretti@gmx.com</a></p>")
                .arg(PROJECT_NAME)
                .arg(PROJECT_VERSION)
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
    select->setCurrentIndex(select->findData(settings.value("language").toString()));

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
