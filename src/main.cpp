#include <QApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QLocale>
#include <QSettings>
#include <QStringList>
#include <QTranslator>

#include "config.h"
#include "mainwindow.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName(PROJECT_NAME);
    QApplication::setApplicationVersion(PROJECT_VERSION);
    QApplication::setOrganizationName("stemoretti");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QSettings settings;
    QString lang(QLocale::system().name());
    if (settings.value("language").isValid()) {
        lang = settings.value("language").toString();
    } else {
        if (!Utils::languages().contains(lang))
            lang = "en_US";
        settings.setValue("language", lang);
    }

    QTranslator qtTranslator;
    QTranslator translator;
    if (lang != "en_US") {
        if (qtTranslator.load(QLocale(lang), "qt", "_", QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
            app.installTranslator(&qtTranslator);

        if (translator.load(QLocale(lang), PROJECT_NAME, "_", Utils::resourcePath(TRANSLATIONS_PATH)))
            app.installTranslator(&translator);
    }

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
