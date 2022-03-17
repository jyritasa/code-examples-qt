/* SPEED SPEDE
 * SPEED SPEDE is a clone of a four button reaction game from Finnish TV series Speden Spelit.
 * Originally made for Mobile Software Deveplovement Class at school for AndroidOS. Can be built for Windows.
 * Icon made by Freepik from www.flaticon.com
 * Jyri Tasala 14.2.2022
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend.h"
#include "scoremodel.h"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);
  Backend backend;
  ScoreModel myModel;
  QQmlApplicationEngine engine;
  QQmlContext *context = engine.rootContext();

  context->setContextProperty("_backend", &backend);
  context->setContextProperty("_myModel", &myModel);
  engine.load(QUrl("qrc:/main.qml"));

  return app.exec();
}
