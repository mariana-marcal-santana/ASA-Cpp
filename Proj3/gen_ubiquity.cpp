#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_set>

using namespace std;

#define randomValue(m) (rand() % m)

int _T , _P;
int _Tcmin, _Tcmax, _Tlmax;
int _Pok;

void printUsage(char *progname) {
  cerr << "Usage: " << progname << " <T> <P> <Tcmin> <Tcmax> <Tlmax> <Pok> <seed>" << endl;
  cerr << "  T: number of toys" << endl;
  cerr << "  P: number of packs" << endl;
  cerr << "  Tcmin: Toy min capacity" << endl;
  cerr << "  Tcmax: Toy max capacity" << endl;
  cerr << "  Tlmax: Toy max profit" << endl;
  cerr << "  Pok: % valid packs [0,100]" << endl;
  cerr << "  seed: random seed generator (optional)" << endl;
  exit(1);
}

void parseArgs(int argc, char **argv) {
  int seed = 0;

  if (argc < 7 || argc > 8) {
    cerr << "ERROR: Wrong number of arguments" << endl;
    printUsage(argv[0]);
  }

  sscanf(argv[1], "%d", &_T);
  sscanf(argv[2], "%d", &_P);
  sscanf(argv[3], "%d", &_Tcmin);
  sscanf(argv[4], "%d", &_Tcmax);
  sscanf(argv[5], "%d", &_Tlmax);
  sscanf(argv[6], "%d", &_Pok);

  if (_P > _T) {
    cerr << "ERROR: Packs cannot be greater than toys" << endl;
    printUsage(argv[0]);
    exit(0);
  }
  if (_Tcmin > _Tcmax) {
    cerr << "ERROR: Toy min capacity cannot be greater than max capacity" << endl;
    printUsage(argv[0]);
    exit(0);
  }

  if (_Pok < 0 || _Pok > 100) {
    cerr << "ERROR: Pok must be between [0, 100]" << endl;
    printUsage(argv[0]);
    exit(0);
  }

  if (argc == 8) {
    sscanf(argv[7], "%d", &seed);
    srand(seed);
  } else { // pseudo-random seed
    srand((unsigned int)time(NULL));
  }
}

int main(int argc, char *argv[]) {


  ofstream outFile("output.out"); // Abre o arquivo de saída

  vector<pair<int, int>> instances = {
    {10, 5},
    {15, 10},
    {20, 15},
    {25, 20},
    {30, 15},
    {40, 20},
    {50, 25},
    {60, 30},
    {70, 35},
    {80, 40},
    {90, 45},
    {100, 50},
    {110, 55},
    {120, 60},
    {130, 65},
    {140, 70}
  };

  for (auto &instance : instances) {
    int nToys = instance.first;
    int nSets = instance.second;
    int maxCap = 0;

    vector<pair<int, int>> toys;
    vector<int> randomToys;
    for (int i = 0; i < nToys; i++) {
      int profit_i = randomValue(_Tlmax + 1);
      int max_i = randomValue(_Tcmax - _Tcmin + 1) + _Tcmin;
      toys.push_back(make_pair(profit_i, max_i));
      randomToys.push_back(i + 1);
      maxCap += max_i;
    }

    // limit max capacity to [75, 95]% of Sum(toy_i_cap)
    maxCap = (float)maxCap * (95 - randomValue(10)) / 100;
    outFile << nToys << " " << nSets << " " << maxCap << endl; // Escreve no arquivo

    // Print Toys
    for (pair<int, int> p : toys) {
      outFile << p.first << " " << p.second << endl; // Escreve no arquivo
    }

    // Print packs
    int p_profit;
    for (int i = 0; i < nSets; i++) {
      random_shuffle(randomToys.begin(), randomToys.end());
      p_profit = (toys[randomToys[0]].first + toys[randomToys[1]].first + toys[randomToys[2]].first) * 1.1;
      int v = randomValue(100 + 1);
      if (v > _Pok)
        p_profit *= 0.9;
      else
        p_profit *= 1.1;
      outFile << randomToys[0] << " " << randomToys[1] << " " << randomToys[2] << " " << p_profit << endl; // Escreve no arquivo
    }
    outFile << endl;  // Adiciona uma linha em branco para separar as instâncias
  }

  outFile.close(); // Fecha o arquivo de saída

  return 0;
}
