#ifndef TOYGEN_RANDOM_H
#define TOYGEN_RANDOM_H

#include <random>

class Random
{
private:
  static std::mt19937_64                          _engine;

  static std::uniform_real_distribution< double > _uniform;
  static std::exponential_distribution < double > _exponential;
  static std::normal_distribution      < double > _normal;
  static std::uniform_int_distribution < int >    _integer;

public:
  static std::mt19937_64& engine()
  {
    return _engine;
  }

  static void setSeed( const unsigned& seed ) { _engine.seed( seed ); }

  static const double flat   ( const double& min = 0.0, const double& max = 1.0 )
  {
    return min + ( max - min ) * _uniform( engine() );
  }

  static const double uniform( const double& min = 0.0, const double& max = 1.0 )
  {
    return min + ( max - min ) * _uniform( engine() );
  }

  static const double exponential( const double& lambda = 1.0 )
  {
    return _exponential( _engine );
  }

  static const double normal( const double& mu = 0.0, const double& sigma = 1.0 )
  {
    return mu + sigma * _normal( _engine );
  }

  static const int integer( const int& a = 0, const int& b = 1 )
  {
    return _integer( _engine );
  }
};

#endif