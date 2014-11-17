#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "Application.h"
#include "TextViewer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Application appData;

    QQmlApplicationEngine engine;
    qmlRegisterType<TextViewer>("TextViewer", 1, 0, "TextViewer");
    qmlRegisterType<Document>("Document", 1, 0, "Document");
    engine.rootContext()->setContextProperty("AppData", &appData);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
