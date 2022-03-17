#include "scoremodel.h"

ScoreModel::ScoreModel(QObject *parent) : QAbstractListModel(parent) {
  m_scoresVector = m_database.getPlayerScoreVector();
  m_database.print();
}

int ScoreModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
      return 0;
    }
  return m_scoresVector.count();
}

QVariant ScoreModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) {
      return QVariant();
    }
  PlayerScore data = m_scoresVector.at(index.row());
  if (role == nameRole) {
      return data.name;
    }
  else if (role == scoreRole) {
      return data.score;
    }
  else if (role == dateRole) {
      return data.date;
    }
  else {
      return QVariant();
    }
}

QHash<int, QByteArray> ScoreModel::roleNames() const {
  static QHash<int, QByteArray> mapping {
    {nameRole, "name"},
    {scoreRole, "score"},
    {dateRole, "date"},

  };
  return mapping;
}

void ScoreModel::submitScore(QString name, int score) {
  const QDate date = QDate::currentDate();
  m_database.insert(PlayerScore{name, score, date.toString("dd.MM.yyyy")});
  m_scoresVector = m_database.getPlayerScoreVector();
  emit layoutChanged();
}
