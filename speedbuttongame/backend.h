#pragma once
#include <QObject>
#include <QRandomGenerator>
#include <QDebug>
#include <qtimer.h>

class Backend : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int m_score READ getScore WRITE setScore NOTIFY scoreChanged)
  Q_PROPERTY(int m_nextButton READ getNextButton WRITE setNextButton NOTIFY nextButtonChanged)
  Q_PROPERTY(bool m_gameOver READ getGameOver WRITE setGameOver NOTIFY gameOverChanged)

public:
  explicit Backend(QObject *parent = nullptr);
  int getScore();
  void setScore(int);
  int getNextButton();
  void setNextButton(int);
  bool getGameOver() const;
  void setGameOver(bool);
  Q_INVOKABLE void startGame();

public slots:
  void buttonPress(int);

private:
  int m_score = 0;
  int m_nextButton;
  int m_buttonOrder[255];
  int m_currenButtontIndex = 0;
  int m_currentPlayIndex = 0;
  QTimer *m_timer = new QTimer(this);
  int m_timerTime;
  bool m_start = false;
  bool m_gameOver = false;
  int getNextNumber(int);
  void timerSignaled();
  void decreaseTime();

signals:
  void scoreChanged();
  void nextButtonChanged();
  void gameOverChanged();
};
