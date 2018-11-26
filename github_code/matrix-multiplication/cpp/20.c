#ifndef _E_heat_lattice_h
#define _E_heat_lattice_h

#include <math.h>

class Heat_Lattice
{

public:
  Heat_Lattice();                                   // Constructor (gives number of cells (=col^2))
  ~Heat_Lattice()
  {}
  ;                                  // Destructor   (does nothing)

  bool heat_flow_enabled;

  float initial_diameter;

  int numParticles;

  double delta_x, delta_y;

  void heat_flow();   // 'main'-function, ̹bergibt x-schritt,
  // y-schritt, gr̦�e der matrix, deform-zeitschritt,
  // dichte, spezifische w�rme, w�rmeleitf�higkeit, pressure

  void set_cell_temperature(float x, float y, float t);      // ̹bergibt x- und y-position, mit delta temp f̹r die zelle

  float set_particle_temperature(float x, float y);       // gibt zell-temperatur an x/y-stelle

  void set_Parameters(float, float, float);

  void reset_heat_distribution();

  void save_heat_distribution();                          // copies heat_distr. to prev._heat_distr.

  void SetHeatFlowParameters(float, float, float, float);

  void SetHeatFlowEnabled(int);

private:
  double a[800][800],
  a_save[800][800],
  a_inv[800][800],
  b[800][800],
  interim_heat_distribution[800][800],
  diffusivity,                    // w�rmeleitf�higkeit
  rho,                         // dichte
  c,                              // w�rmekapazit�t
  heat_distribution[800][800],       // current temperature-field
  //previous_heat_distribution[800][800],  // f̹r vor̹bergehende umwandlungen
  alpha,                          // coefficients (for matrices)
  beta,
  adiabatic_temperature,
  pressure,
  wall_pos,
  time,
  factor;

  float boundary_condition;

  int                 col, counter;                       // number of rows and columns (of lattice/matrix), and a counter

  void invert();                                       // gauss algorithmus

  void multiplication();                               // matrix-multiplication

  void set_matrices_1();

  void set_matrices_2();

  void transpose();                                    // transpose matrix

  void set_boundary_condition(float pressure);

  void multiplication_two();                              // multiplication von invertierter matrix mit aktuelle w�rmeverteilung (=implizite l̦sung)

  void transpose_interim_distribution();

};

#endif
