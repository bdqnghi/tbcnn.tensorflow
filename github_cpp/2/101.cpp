#include "../include/btree.h"
#include "../include/compress.h"
#include "../include/decompress.h"
#include "../include/prob-Calc.h"
#include "../include/util.h"
#include <algorithm>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<char, boost::dynamic_bitset<>> char_bit_t;
typedef unordered_map<char, double> char_doub_t;

int main(int argc, char *argv[]) {

  string entrada;
  string entradaComprimida;
  string arquivoProbabilidades;

  switch (argc) {

  case 2:
    entrada = argv[1];
    huffmanCompress(entrada);
    break;

  case 3:
    entradaComprimida = argv[1];
    arquivoProbabilidades = argv[2];
    decompress(entradaComprimida, arquivoProbabilidades);
    break;

  default:
    cout << "ENTRADA INVALIDA" << endl;
  }

  return 0;
}
