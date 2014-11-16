#include <QApplication>
#include <QQmlApplicationEngine>

#include "document_data.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DocumentData data;

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("DocumentData", &data);

    return app.exec();
}
