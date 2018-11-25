#ifndef _E_heat_lattice_h
#define _E_heat_lattice_h

#include <math.h>

class Heat_Lattice
{

public:
  Heat_Lattice();                                   
  ~Heat_Lattice()
  {}
  ;                                  

  bool heat_flow_enabled;

  float initial_diameter;

  int numParticles;

  double delta_x, delta_y;

  void heat_flow();   
  
  

  void set_cell_temperature(float x, float y, float t);      

  float set_particle_temperature(float x, float y);       

  void set_Parameters(float, float, float);

  void reset_heat_distribution();

  void save_heat_distribution();                          

  void SetHeatFlowParameters(float, float, float, float);

  void SetHeatFlowEnabled(int);

private:
  double a[800][800],
  a_save[800][800],
  a_inv[800][800],
  b[800][800],
  interim_heat_distribution[800][800],
  diffusivity,                    
  rho,                         
  c,                              
  heat_distribution[800][800],       
  
  alpha,                          
  beta,
  adiabatic_temperature,
  pressure,
  wall_pos,
  time,
  factor;

  float boundary_condition;

  int                 col, counter;                       

  void invert();                                       

  void multiplication();                               

  void set_matrices_1();

  void set_matrices_2();

  void transpose();                                    

  void set_boundary_condition(float pressure);

  void multiplication_two();                              

  void transpose_interim_distribution();

};

#endif
