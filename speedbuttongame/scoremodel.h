#pragma once
#include <QAbstractListModel>
#include <QObject>

#include "scoredatabasehandler.h"

class ScoreModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum Roles {
    nameRole= Qt::UserRole,
    scoreRole,
    dateRole
  };
  explicit ScoreModel(QObject *parent = nullptr);
  int rowCount(const QModelIndex& parent) const override;
  QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
  QHash<int, QByteArray> roleNames() const override;

public slots:
  void submitScore(QString, int);

private:
  ScoreDatabaseHandler m_database;
  QVector <PlayerScore> m_scoresVector;
};
