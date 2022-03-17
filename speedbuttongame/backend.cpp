#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
  //Connecting Timer's timeout signal to this object's timerSignaled() method
  connect(m_timer, &QTimer::timeout, this, &Backend::timerSignaled);
}

int Backend::getNextButton() {
  return m_nextButton;
}

void Backend::setNextButton(int button) {
  if(m_nextButton == button) {
      return;
    }
  m_nextButton = button;
  emit nextButtonChanged();
}

int Backend::getScore() {
  return m_score;
}

void Backend::setScore(int score) {
  if (m_score == score) {
      return;
    }
  m_score = score;
  emit scoreChanged();
}

bool Backend::getGameOver() const {
  return m_gameOver;
}

void Backend::setGameOver(bool game) {
  if (m_gameOver == game) {
      return;
    }
  m_gameOver = game;
  emit gameOverChanged();
}

void Backend::startGame() {
  m_currenButtontIndex = 0;
  m_currentPlayIndex = 0;
  m_timerTime = 1000;
  //stopping timer after gameover
  m_timer->stop();
  for(int i=0; i<255; i++){
      m_buttonOrder[i] = getNextNumber(i);
    }
  m_nextButton = m_buttonOrder[m_currenButtontIndex];
  emit nextButtonChanged();
}

int Backend::getNextNumber(int index) {
  const int newNum = QRandomGenerator::global()->bounded(1,5);
  //If number is duplicate of previous number, get new number.
  if(index != 0 && newNum == m_buttonOrder[index-1]){
      return getNextNumber(index);
    }
  else {
      return newNum;
    }
}

void Backend::timerSignaled() {
  m_currenButtontIndex++;
  //In case of timer getting to the end of the array...
  if (m_currenButtontIndex != 255){
      m_nextButton = m_buttonOrder[m_currenButtontIndex];
      emit nextButtonChanged();
      emit scoreChanged();
      decreaseTime();
    }
  //...reset game.
  else {
      m_start = false;
      startGame();
    }
}

void Backend::decreaseTime() {
  if (m_timerTime <= 1000 && m_timerTime > 500){
      m_timerTime = m_timerTime - (m_timerTime*0.05);
    }
  else {
      m_timerTime = m_timerTime - (m_timerTime*0.005);
    }
  qDebug() << "Timer speed: " << QString::number(m_timerTime) << "ms";
  m_timer->start(m_timerTime);
}

void Backend::buttonPress(int button) {
  //Starting Game if not already in progress
  if (!m_start){
      m_timer->start();
      m_start = true;
    }
  //If Correct Button was Pressed or Not
  if (m_buttonOrder[m_currentPlayIndex] == button) {
      m_currentPlayIndex++;
      m_score++;
      emit scoreChanged();
    }
  else {
      m_timer->stop();
      m_start = false;
      m_gameOver = true;
      emit gameOverChanged();
    }
}
