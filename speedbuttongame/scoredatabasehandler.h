#pragma once
#include <QSqlDatabase>
#include <QStandardPaths>
#include <QObject>
#include <QDate>
#include <QDebug>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QApplication>
#include <QFile>
#include <QFileInfo>

struct PlayerScore {
  QString name;
  int score;
  QString date;
};

class ScoreDatabaseHandler : public QObject
{
  Q_OBJECT
public:
  explicit ScoreDatabaseHandler(QObject *parent = nullptr);
  void print();
  void insert(PlayerScore);
  QVector<PlayerScore>getPlayerScoreVector();

private:
  QSqlDatabase m_database;
  const QString m_homeFolder = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
};
