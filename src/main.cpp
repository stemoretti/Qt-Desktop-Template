#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QSettings>
#include <QStringList>
#include <QTranslator>

#include "appinfo.h"
#include "mainwindow.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName(PROJECT_DISPLAY_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);
    QCoreApplication::setOrganizationName(PROJECT_DISPLAY_NAME);

    QApplication app(argc, argv);

    QSettings settings;
    QString lang(QLocale::system().name());
    if (settings.value("language").isValid()) {
        lang = settings.value("language").toString();
    } else {
        QStringList languages = Utils::languages();
        if (!languages.contains(lang) && !languages.contains(lang.left(2)))
            lang = "en_US";
        settings.setValue("language", lang);
    }

    QTranslator qtTranslator;
    QTranslator translator;
    if (lang != "en_US") {
        if (qtTranslator.load(QLocale(lang), "qt", "_", QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
            app.installTranslator(&qtTranslator);

        if (translator.load(QLocale(lang), PROJECT_NAME, "_", Utils::resourcePath(TRANSLATIONS_PATH)))
            app.installTranslator(&translator);
    }

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
