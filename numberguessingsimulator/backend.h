#pragma once
#include <random>
#include <iostream>
#include <array>
#include <time.h>

class Backend
{
public:
  Backend();
private:
  clock_t m_timer;
  const int m_simulations = 1000000;
  const int m_attempts = 10;
  int m_targetNumber = 50;
  int m_num = 50;
  int m_max = 100;
  int m_min = 0;
  bool m_numberFound = false;
  double m_successes = 0;
  double m_fails = 0;
  double m_randomSuccess = 0;
  double m_randomFails = 0;
  std::random_device m_rd;
  std::array<int,10> m_randomGuesses;

  int randomNumber();
  bool singleGame();
  bool guess();
  bool singleRandomGame();
  bool guessRandom();
  bool checkRandomDuplicate();
};

