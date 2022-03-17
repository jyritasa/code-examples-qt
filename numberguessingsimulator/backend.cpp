#include "backend.h"

Backend::Backend()
{
  std::cout << "Number of Games being simulated: " << m_simulations << std::endl << std::endl;
  m_timer = clock();
  for(int i = 0; i < m_simulations; i++){
      singleGame() ? m_successes++ : m_fails++;
    }
  m_timer = clock() - m_timer;
  std::cout << "Algorithm Simulations took: " << ((float)m_timer)/CLOCKS_PER_SEC << " Seconds" << std::endl;
  std::cout << "Algorithm Successes: " << m_successes << std::endl;
  std::cout << "Algorithm Fails: " << m_fails << std::endl;
  std::cout << "Algorithm Success Rate: " << m_successes/m_simulations*100 << "%" << std::endl;
  std::cout << std::endl;

  m_timer = clock();
  m_randomGuesses.fill(0);
  for(int i = 0; i< m_simulations; i++){
      singleRandomGame() ? m_randomSuccess++ : m_randomFails++;
    }
  m_timer = clock() - m_timer;
  std::cout << "Random Simulations took: " << ((float)m_timer)/CLOCKS_PER_SEC << " Seconds" << std::endl;
  std::cout << "Random Successes: " << m_randomSuccess << std::endl;
  std::cout << "Random Fails: " << m_randomFails << std::endl;
  std::cout << "Random Success Rate: " << m_randomSuccess/m_simulations*100 << "%" << std::endl;
  std::cout << std::endl;
}

int Backend::randomNumber(){
  std::mt19937 gen(m_rd());
  std::uniform_int_distribution<> distrib(1, 100);
     return distrib(gen);
}

bool Backend::singleGame(){
  m_targetNumber = randomNumber();
  m_num = 50;
  m_max = 100;
  m_min = 0;
  for(int i = 0; i<m_attempts; i++){
      if(guess()){
          return true;
        }
    }
  return false;
}

bool Backend::guess()
{
  if (m_num == m_targetNumber){
      return true;
    }
  if (m_num > m_targetNumber){
      m_max = m_num;
      m_num = m_num-((m_num-m_min)/2);
      return false;
    }
  //else
  m_min = m_num;
  m_num  = m_num +((m_max-m_num)/2);
  return false;
}

bool Backend::singleRandomGame()
{
  m_num = randomNumber();
  m_targetNumber = randomNumber();
  for(int i = 0; i<m_attempts; i++){
      if(guessRandom()){
          return true;
        }
    }
  return false;
}

bool Backend::guessRandom()
{
  if (m_num == m_targetNumber){
      return true;
    }
  //Get a new number that has not already been guessed.
  while (!checkRandomDuplicate()){
      m_num = randomNumber();
    }
  return false;
}

bool Backend::checkRandomDuplicate()
{
  for (int i=0; i<m_attempts; i++){
      if (m_randomGuesses[i] == 0){
          m_randomGuesses[i] = m_num;
          return true;
        }
      if (m_randomGuesses[i] == m_num){
          return false;
        }
    }
  return true;
}
