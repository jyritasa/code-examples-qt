#include "scoredatabasehandler.h"

ScoreDatabaseHandler::ScoreDatabaseHandler(QObject *parent) : QObject(parent) {

  //Setting Database to be SQLite type
  if(QSqlDatabase::contains("qt_sql_default_connection")) {
      m_database = QSqlDatabase::database("qt_sql_default_connection");
    }
  else {
      m_database = QSqlDatabase::addDatabase("QSQLITE");
    }

  qDebug() << "\t\tCreating Database...";


  //Using two different Database creation styles for Windows and Android as practice:

  //Creating from scratch:
#ifdef Q_OS_WIN
  QFileInfo databaseFileInfo(QString("%1/%2").arg(m_homeFolder, "scores.db"));
  const QString databasePath = databaseFileInfo.absoluteFilePath();

  //For Debugging Purposes. Deletes existing database and creates a new one
  //QFile::remove(databasePath);

  m_database.setDatabaseName(databasePath);
  m_database.open();
  if(!(m_database.tables().contains( QLatin1String("scores")))){
      qDebug() << "\t\tCREATING DATABASE FROM SCRATCH:";
      QSqlQuery query;
      query.exec("CREATE TABLE 'scores' ('id' INTEGER UNIQUE, 'score' INTEGER NOT NULL, 'name' TEXT, 'date'	TEXT, PRIMARY KEY('id' AUTOINCREMENT));");
      qDebug() << query.lastError();
    }
  else {
      qDebug() << "\t\tDATABASE ALREADY EXISTS";
    }
#endif


  //copying during build:
#ifdef Q_OS_ANDROID
  //Finding path for the database file within Android filesystem.
  QFileInfo databaseFileInfo(QString("%1/%2").arg(m_homeFolder, "scores.db"));
  const QString databasePath = databaseFileInfo.absoluteFilePath();

  //For Debugging Purposes. Deletes existing database and creates a new one
  //QFile::remove(databasePath);

  //If Database does not exist during build, copy it into build folder.
  if(!QFile::exists(databasePath)) {
      bool copySuccess = QFile::copy( QString("assets:/database/scores.db"), databasePath );
      qDebug() << "\t\tCOPYING...";
      if ( !copySuccess ) {
          qDebug() << "\t\tCOPY NOT SUCCESSFUL";
        }
      else {
          qDebug() <<"\t\tCOPY SUCCESSFUL!";
          QFile(databasePath).setPermissions(QFile::ReadOwner|QFile::WriteOwner);
        }
    }
  else {
      qDebug() << "\t\tDATABASE ALREADY EXISTS: " << QFile::exists(databasePath);
    }
  //Binding Database into variable
  m_database.setDatabaseName(databasePath);
#endif

  //Connecting to Database.
  if (!m_database.open()) {
      qDebug() << "\t\tERROR: Failed to connect database." << m_database.lastError();
    }
  else {
      qDebug() << "\t\tCONNECTION SUCCESSFUL!";
      qDebug() << "\t\tAVAILABLE TABLES:" << m_database.tables();
    }
}

void ScoreDatabaseHandler::print() {
  static QSqlQuery query(m_database);
  query.exec("SELECT score, name, date FROM scores");

  while (query.next()) {
      QString name = query.value(1).toString();
      int score = query.value(0).toInt();
      QString date = query.value(2).toString();
      qDebug() << "\t\t" << date << name << score;
    }
}

void ScoreDatabaseHandler::insert(PlayerScore playerScore) {
  static QSqlQuery query(m_database);
  query.prepare("INSERT INTO scores (name, score, date) "
                "VALUES (?, ?, ?)");
  query.addBindValue(playerScore.name);
  query.addBindValue(playerScore.score);
  query.addBindValue(playerScore.date);
  query.exec();
  if (query.lastError().type() != QSqlError::NoError) {
      qDebug() << query.lastError();
    }
}

QVector<PlayerScore> ScoreDatabaseHandler::getPlayerScoreVector() {
  QVector<PlayerScore> scoreVector;
  static QSqlQuery query(m_database);
  query.exec("SELECT name, score, date FROM scores ORDER BY score DESC");
  if (query.lastError().type() != QSqlError::NoError) {
      qDebug() << query.lastError();
    }

  while (query.next()) {
      PlayerScore score{query.value(0).toString(),
            query.value(1).toInt(),
            query.value(2).toString()};
      scoreVector.push_back(score);
    }
  qDebug() << "\t\tRead "<< scoreVector.size() << " Rows into Vector";
  return scoreVector;
}
