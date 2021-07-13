#include <iostream>
#include <chrono>
#include <random>
 
int main ()
{
  // obtain a seed from the system clock:
  unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
 
  std::mt19937 g1 (seed1);  // mt19937 is a standard mersenne_twister_engine
  uint32_t u32Random = g1();
  std::cout << "A time seed produced: " << u32Random << std::endl;
  
  std::mt19937_64 g2 (seed1);
  uint64_t u64Random = g2();
  std::cout << "A time seed produced: " << u64Random << std::endl;
  u64Random = g2();
  std::cout << "A time seed produced: " << u64Random << std::endl;
  
  return 0;
}