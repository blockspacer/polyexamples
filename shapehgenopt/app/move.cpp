#include "rectangle.h"
#include "scene.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <tuple>
#include <random>

void print_error(std::string msg, int argc, const char ** argv) {
  using namespace std;
  cerr << msg << endl;
  cerr << "\t" << argv[0] << " infile outfile dx dy" << endl;
  copy_n(argv, argc, ostream_iterator<std::string>{cout, " "});
}

std::tuple<std::string, std::string, int, int>
parse_args(int argc, const char ** argv) {
  using namespace std;
  if (argc != 5) {
    print_error("Wrong format", argc, argv);
    exit(-1);
  }
  
  try {
    int dx = stoi(argv[3]);
    int dy = stoi(argv[4]);
    return make_tuple(argv[1], argv[2], dx, dy);
  }
  catch (...) {
    print_error("Wrong numeric argument",argc,argv);
    exit(-1);
  }
}

int main(int argc, const char ** argv) {
  using namespace std;

  auto arg = parse_args(argc,argv); 

  cout << "Reading gfile " << get<0>(arg) << endl;

  dsl::scene s;
  ifstream in{get<0>(arg)};
  in >> s;
  if (!in) {
    cerr << "Error reading scene file" << endl;
    return -1;
  }

  s.move_shapes(get<2>(arg), get<3>(arg));

  ofstream out{get<1>(arg)};
  out << s;
  if (!out) {
    cerr << "Error writing scene file" << endl;
    return -1;
  }

  cout << s.size() << " shapes written to file " << get<1>(arg) << endl;

  return 0;
}
