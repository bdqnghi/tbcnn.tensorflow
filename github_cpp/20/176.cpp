#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdio> /* NULL */
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

#include "hmm.hpp"

typedef float T;
typedef std::size_t U;

static const std::string version = "0.1";
struct Help {};
struct NoInput {};
struct Version {};
static const std::string nstate_header = "NStates:";
static const std::string nsymbol_header = "NSymbols:";
static const std::string label_header = "Labels";
static const std::string initial_header = "Initial-Probabilities:"; // not log
static const std::string transitional_header = "Transitional-Log-Probabilities:"; // log
static const std::string emission_header = "Emission-Log-Probabilities:";

void do_log(std::vector<T>& v) {
  T sum = 0, one = 1;
  const double epsilon = 1e-4;
  for ( std::size_t i = 0; i < v.size(); ++i ) {
    sum += v[i];
    if ( 0 != v[i] )
      v[i] = std::log(v[i]);
    else
      v[i] = ci::inf<T>();
  } // for
  if ( std::abs(sum-one) > epsilon )
    throw("Probabilities do not sum to 1, vector<T>");
}

void do_log(std::vector<std::vector<T>>& v) {
  const T one = 1;
  const T epsilon = 1e-4;
  for ( std::size_t i = 0; i < v.size(); ++i ) {
    T sum = 0;
    for ( std::size_t j = 0; j < v[i].size(); ++j ) {
      sum += v[i][j];
      if ( 0 != v[i][j] )
        v[i][j] = std::log(v[i][j]);
      else
        v[i][j] = ci::inf<T>();
    } // for
    if ( std::abs(sum-one) > epsilon )
      throw("Probabilities do not sum to 1, vector<vector<T>>");
  } // for
}

void do_exp(std::vector<T>& v) {
  T sum = 0, one = 1;
  const T epsilon = 1e-4;
  for ( std::size_t i = 0; i < v.size(); ++i ) {
    if ( ci::inf<T>() != v[i] )
      v[i] = std::exp(v[i]);
    else
      v[i] = 0;
    sum += v[i];
  } // for
  if ( std::abs(sum-one) > epsilon )
    throw("Probabilities do not sum to 1, do_exp()");
}

std::string Usage(std::string s) {
  std::string msg = s + "\n\nUSAGE:";
  msg += "\n0) --help or --version";
  msg += "\n1) train [--verbose] [--seed=<+integer>] <number-states> <number-iterations> <observations-file>";
  msg += "\n2) probability <hmm-parameters-file> <observations-file>";
  msg += "\n3) decode <hmm-parameters-file> <observations-file>";
  msg += "\n4) train-and-decode [--verbose] [--seed=<+integer>] <number-states> <number-iterations> <observations-file>";
  msg += "\n\nAll output is sent to stdout.";
  msg += "\nYou can train a discrete hmm, save its output, and then use it as an <hmm-parameters-file> to";
  msg += "\ndetermine the probability of another set of observations, or to decode the hidden states";
  msg += "\nof another set of observations.";
  msg += "\nYou can also train an hmm on observations and decode the hidden states of that";
  msg += "\ninformation using train-and-decode.";
  return msg;
}

enum class Ops { TRAIN, PROB, DECODE, TRAIN_AND_DECODE };

std::vector<std::string> split(const std::string& s, const std::string& d) {
  std::vector<std::string> rtn;
  std::string::size_type pos1 = 0, pos2 = 0;
  do {
    pos2 = s.find(d, pos1);
    rtn.push_back(s.substr(pos1, pos2-pos1));
    pos1 = pos2 + 1;
  } while ( pos2 != std::string::npos ); // while
  return rtn;
}

struct Input {
  Input(int argc, char** argv);

  int _niters;
  int _nstates;
  int _nsymbols;
  bool _verbose;
  bool _read_params;
  int _seed;
  std::string _src;
  std::string _params;
  Ops _operation;
  std::vector<T> _initial, _observed;
  std::vector<std::vector<T>> _transition, _emission;
  std::map<std::string, std::size_t> _mapID;
  static constexpr int _MAXITER = 1000000; // can be bigger; likely an error if you exceeded this though
  static constexpr int _MAXSTATES = 10000; // can be bigger; likely an error if you exceeded this though

private:
  void read_data();
  void read_parameters();
  void initialize_parameters();
};

void output(const Input& input);

void do_work(Input& input);

int main(int argc, char** argv) {
  try {
    Input input(argc, argv);

    do_work(input);

    return EXIT_SUCCESS;
  } catch(Help h) {
    std::cout << Usage(argv[0]) << std::endl;
    return EXIT_SUCCESS;
  } catch(Version v) {
    std::cout << argv[0] << " Version: " << version << std::endl;
    return EXIT_SUCCESS;
  } catch(NoInput n) {
    std::cout << Usage(argv[0]) << std::endl;
  } catch(const char* c) {
    std::cerr << c << std::endl;
  } catch(std::string& s) {
    std::cerr << s << std::endl;
  } catch(std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch(...) {
    std::cerr << "Unknown problem" << std::endl;
  }
  return EXIT_FAILURE;
}

void do_work(Input& input) {
  if ( input._operation == Ops::TRAIN || input._operation == Ops::TRAIN_AND_DECODE ) {
    auto last_trans = input._transition;
    auto last_emiss = input._emission;
    double log_likelihood = 0;
    for ( int i = 0; i < input._niters; ++i ) {
      ci::hmm::train(input._observed, input._initial, input._transition, input._emission);
      if ( input._emission == last_emiss ) {
        if ( input._transition == last_trans )
          break;
      } else {
        log_likelihood = ci::hmm::evalp(input._observed, input._initial, input._transition, input._emission);
      }

      if ( input._verbose ) {
        std::cout << "# iteration " << i+1 << std::endl;
        std::cout << "# log-likelihood " << log_likelihood << std::endl;
        std::cout << "# ";
        std::copy(input._observed.begin(), input._observed.end(), std::ostream_iterator<U>(std::cout, " "));
        std::cout << std::endl;
      }
      last_trans = input._transition;
      last_emiss = input._emission;
    } // for
  }
  output(input);
}

void output(const Input& input) {
  if ( input._operation == Ops::TRAIN ) {
    std::cout << nstate_header << " " << input._nstates << std::endl;
    std::cout << nsymbol_header << " " << input._nsymbols << std::endl;

    std::cout << label_header << std::endl << "{" << std::endl;;
    for ( auto& i : input._mapID )
      std::cout << i.second << " " << i.first << std::endl;
    std::cout << "}" << std::endl;

    std::cout << initial_header;
    for ( std::size_t i = 0; i < input._initial.size(); ++i )
      std::cout << " " << input._initial[i];
    std::cout << std::endl;

    std::cout << transitional_header << std::endl << "{" << std::endl;
    for ( std::size_t i = 0; i < input._transition.size(); ++i ) {
      if ( input._transition[i][0] == ci::inf<T>() )
        std::cout << 0;
      else
        std::cout << input._transition[i][0];

      for ( std::size_t j = 1; j < input._transition[i].size(); ++j ) {
        if ( input._transition[i][j] == ci::inf<T>() )
          std::cout << " " << 0;
        else
          std::cout << " " << input._transition[i][j];
      } // for
      std::cout << std::endl;
    } // for
    std::cout << "}" << std::endl;

    std::cout << emission_header << std::endl << "{" << std::endl;
    for ( std::size_t i = 0; i < input._emission.size(); ++i ) {
      if ( input._emission[i][0] == ci::inf<T>() )
        std::cout << 0;
      else
        std::cout << input._emission[i][0];

      for ( std::size_t j = 1; j < input._emission[i].size(); ++j ) {
        if ( input._emission[i][j] == ci::inf<T>() )
          std::cout << " " << 0;
        else
          std::cout << " " << input._emission[i][j];
      } // for
      std::cout << std::endl;
    } // for
    std::cout << "}" << std::endl;
  } else if ( input._operation == Ops::PROB ) {
    std::cout << ci::hmm::evalp(input._observed, input._initial, input._transition, input._emission) << std::endl;
  } else if ( input._operation == Ops::DECODE ) { \
    auto initial_cpy = input._initial;
    do_exp(initial_cpy);
    std::ostream_iterator<U> os(std::cout, " ");
    ci::hmm::viterbi(input._observed, initial_cpy, input._transition, input._emission, os);
    std::cout << std::endl;
  } else { // Ops::TRAIN_AND_DECODE
    std::ostream_iterator<U> os(std::cout, " ");
    ci::hmm::viterbi(input._observed, input._initial, input._transition, input._emission, os);
    std::cout << std::endl;
  }
}


struct ByLine : public std::string {
  friend std::istream& operator>>(std::istream& is, ByLine& b) {
    std::getline(is, b);
    return(is);
  }
};

Input::Input(int argc, char** argv) : _niters(1), _nstates(1), _nsymbols(0),
                                      _verbose(false), _read_params(false),
                                      _seed(std::time(NULL)) {
  for ( int i = 1; i < argc; ++i ) {
    if ( std::string(argv[i]) == "--help" )
      throw(Help());
    else if ( std::string(argv[i]) == "--version" )
      throw(Version());
  } // for

  if ( argc == 1 )
    throw(NoInput());
  if ( argc < 4 )
    throw("Wrong number of args: see --help");

  const std::string ints = "0123456789";
  int nextc = 1;
  const std::string todo = argv[nextc++];
  std::string next = argv[nextc++];
  if ( todo == "train" || todo == "train-and-decode" ) {
    if ( (argc < 5) || (argc > 7) )
      throw("Wrong number of args for '" + todo + ".  See --help");
    _operation = Ops::TRAIN;
    if ( todo == "train-and-decode" )
      _operation = Ops::TRAIN_AND_DECODE;
    int count = argc;
    while ( next.find_first_of("--seed") == 0 || next.find_first_of("--verbose") == 0 ) {
      if ( --count == 0 )
        break;
      if ( next == "--verbose" ) {
        _verbose = true;
      } else {
        auto v = split(next, "=");
        if ( v.size() != 2 )
          throw("Bad number.  Expect a +integer for " + next + ".  See --help");
        if ( v[1].find_first_not_of(ints) != std::string::npos )
          throw("Bad number. Expect a +integer for " + next + ".  See --help");
        _seed = std::atoi(v[1].c_str());
        std::srand(_seed);
      }
      if ( nextc != argc )
        next = argv[nextc++];
      else
        break;
    } // while
    if ( count != 5 )
      throw("Wrong number (or order) of arguments for " + todo + ".  See --help");
    if ( next.find_first_not_of(ints) != std::string::npos )
      throw("Bad argument: expect a +integer for <number-states>.  See --help");
    _nstates = std::atoi(next.c_str());
    next = argv[nextc++];
    if ( next.find_first_not_of(ints) != std::string::npos )
      throw("Bad argument - expect a +integer for <number-iterations>.  See --help");
    _niters = std::atoi(next.c_str());
  } else if ( todo == "probability" ) {
    if ( argc != 4 )
      throw("Wrong number of args for '" + todo + ".  See --help");
    _operation = Ops::PROB;
    _params = next;
    std::ifstream f(_params.c_str());
    if (!f)
      throw("Input file not found: " + _params);
    read_parameters();
  } else if ( todo == "decode" ) {
    if ( argc != 4 )
      throw("Wrong number of args for '" + todo + ".  See --help");
    _operation = Ops::DECODE;
    _params = next;
    std::ifstream f(_params.c_str());
    if (!f)
      throw("Input file not found: " + _params);
    read_parameters();
  } else {
    throw("Unknown operation: '" + todo + "'.  See --help.");
  }

  if ( _niters <= 0 || _niters > _MAXITER )
    throw("Bad number of '" + todo + "' iterations");
  else if ( _nstates <= 0 || _nstates > _MAXSTATES )
    throw("Bad number of '" + todo + "' states");

  _src = argv[nextc++];
  std::ifstream f(_src.c_str());
  if (!f)
    throw("Input file not found: " + _src);

  read_data(); // read observations; get _nsymbols from the data

  if ( todo == "train" || todo == "train-and-decode" ) {
    initialize_parameters(); // only after read_data() due to _nsymbols
    if ( _nsymbols == 0 )
      throw("Didn't find any data");
  }
}

void Input::read_data() {
  std::ifstream f(_src.c_str());
  std::string s;
  _observed.clear();
  std::set<std::string> other;
  if ( !_read_params )
    _mapID.clear();
  auto iter = _mapID.end();

  int counter = 0;
  while ( f>>s ) {
    if ( (iter = _mapID.find(s)) != _mapID.end() )
      _observed.push_back(iter->second);
    else {
      if ( _read_params ) { // we have the mapping for internal state labels; stay consistent
        if ( other.find(s) == other.end() ) {
          std::cerr << "Warning! Found a new label that was not in the training set for this HMM" << std::endl;
          std::cerr << "New Label: " << s << " assigned to " << _mapID.begin()->first << std::endl;
          other.insert(s);
        }
        _observed.push_back(_mapID.begin()->second); // this label was not there during training
      } else // this create a new ID for label s
        _observed.push_back(_mapID[s] = counter++);
    }
  } // while
  if ( _nsymbols == 0 )
    _nsymbols = _mapID.size();
  else {
    if ( static_cast<std::size_t>(_nsymbols) < _mapID.size() )
      std::cerr << "Warning!  1 or more labels in the training data were not found in: " << _src << std::endl;
  }
}

void Input::read_parameters() {
  const std::string ints = "0123456789";
  const std::string reals = ints + "e-+.";
  bool in_trans = false;
  bool in_emission = false;
  bool in_label = false;

  _read_params = true;
  _nstates = -1;
  std::ifstream infile(_params.c_str());
  ByLine bl;
  while ( infile >> bl ) {
    auto vec = split(bl, " ");
    if ( !vec.empty() ) {
      if ( vec[0] == "#" ) { // comment
        continue;
      } else if ( vec[0] == nstate_header ) {
        if ( vec.size() != 2 || vec[1].find_first_not_of(ints) != std::string::npos )
          throw("Bad parameters input file.  See NStates:");
        _nstates = std::atoi(vec[1].c_str());
      } else if ( vec[0] == nsymbol_header ) {
        if ( vec.size() != 2 || vec[1].find_first_not_of(ints) != std::string::npos )
          throw("Bad parameters input file.  See NStates:");
        _nsymbols = std::atoi(vec[1].c_str());
      } else if ( vec[0] == label_header ) {
        in_label = true;
        in_emission = false;
        in_trans = false;
      } else if ( vec[0] == initial_header ) {
        for ( std::size_t j = 1; j < vec.size(); ++j ) {
          if ( vec[j].find_first_not_of(reals) != std::string::npos )
            throw("Bad parameters input file. See Initial:");
          _initial.push_back(std::stof(vec[j]));
        } // for
        do_log(_initial);
      } else if ( bl == transitional_header ) {
        in_trans = true;
        in_emission = false;
        in_label = false;
      } else if ( bl == emission_header ) {
        in_emission = true;
        in_trans = false;
        in_label = false;
      } else if ( in_trans ) {
        if ( bl == "{" ) continue;
        else if ( bl == "}" ) in_trans = false;
        else {
          std::vector<T> tmp;
          for ( std::size_t j = 0; j < vec.size(); ++j ) {
            if ( vec[j].find_first_not_of(reals) != std::string::npos )
              throw("Bad parameters input file.  See " + vec[j] + " in " + transitional_header);
            tmp.push_back(std::stof(vec[j]));
          } // for
          _transition.push_back(tmp);
        }
      } else if ( in_emission ) {
        if ( bl == "{" ) continue;
        else if ( bl == "}" ) in_emission = false;
        else {
          std::vector<T> tmp;
          for ( std::size_t j = 0; j < vec.size(); ++j ) {
            if ( vec[j].find_first_not_of(reals) != std::string::npos )
              throw("Bad parameters input file.  See " + vec[j] + " in " + emission_header);
            tmp.push_back(std::stof(vec[j]));
          } // for
          _emission.push_back(tmp);
        }
      } else if ( in_label ) {
        if ( bl == "{" ) continue;
        else if ( bl == "}" ) in_label = false;
        else {
          if ( vec.size() != 2 )
            throw("Bad parameters input file.  Expect 2 columns in " + label_header);
          if ( vec[0].find_first_not_of(ints) != std::string::npos )
            throw("Bad parameters input file.  Expect integer in first column of " + label_header);
          _mapID[vec[1]] = std::atoi(vec[0].c_str());
        }
      } else {
        std::cerr << "Unexpected garbage row in (could just be whitespace) in " << _params << "\nSee: " << bl << std::endl;
        std::cerr << "Continuing..." << std::endl;
      }
    } else {
       std::cerr << "Unexpected line with nothing on it (other than spaces perhaps) in " << _params << std::endl;
       std::cerr << "Continuing...." << std::endl;
    }
  } // while

  if ( _initial.empty() )
    throw("Did not find " + initial_header + " in " + _params);
  if ( _transition.empty() )
    throw("Did not find " + transitional_header + " in " + _params);
  if ( _emission.empty() )
    throw("Did not find " + emission_header + " in " + _params);
  if ( _mapID.empty() )
    throw("Did not find " + label_header + " in " + _params);
  if ( _nstates <= 0 || _nstates > _MAXSTATES )
    throw("Problem with (may be missing) " + nstate_header + " in " + _params);
}

void Input::initialize_parameters() {
  const int MOD = 100;
  for ( int i = 0; i < _nstates; ++i ) {
    _initial.push_back(std::rand()%MOD);
    std::vector<T> tmp;
    for (int j = 0; j < _nstates; ++j )
      tmp.push_back(std::rand()%MOD);
    auto sum = std::accumulate(tmp.begin(), tmp.end(), (T)0);
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), std::bind2nd(std::divides<T>(), sum));
    _transition.push_back(tmp);
  } // for

  auto sum = std::accumulate(_initial.begin(), _initial.end(), (T)0);
  std::transform(_initial.begin(), _initial.end(), _initial.begin(), std::bind2nd(std::divides<T>(), sum));

  for ( int i = 0; i < _nstates; ++i ) {
    std::vector<T> tmp;
    for ( int j = 0; j < _nsymbols; ++j )
      tmp.push_back(std::rand()%MOD);
    auto sum = std::accumulate(tmp.begin(), tmp.end(), (T)0);
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), std::bind2nd(std::divides<T>(), sum));
    _emission.push_back(tmp);
  } // for

  do_log(_initial);
  do_log(_transition);
  do_log(_emission);
}
