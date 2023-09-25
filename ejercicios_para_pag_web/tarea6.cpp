/*
 * Tarea 6 en la página web, en la sección C++, agregar un ejemplo de un programa en consola reciba un número entero n,
 * se generen n números aleatorios enteros entre 1 y 100 y después se impriman los números ordenados de menor a mayor
 * */

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> generator(int);

int main(int argc, char *argv[])
{
  int n;
  std::vector<int> randoms;

  std::cout << "Digite un número: ";
  std::cin >> n;

  randoms = generator(n);

  std::cout << "Números antes de ser ordenados: ";

  for (int number : randoms)
    std::cout
        << number << " ";

  std::cout << "\n";

  std::sort(randoms.begin(), randoms.end());

  std::cout << "Números después de ser ordenados: ";

  for (int number : randoms)
    std::cout
        << number << " ";

  std::cout << "\n";

  return 0;
}

std::vector<int> generator(int n)
{
  std::vector<int> randoms;

  for (int i = 0; i <= n; i++)
    randoms.push_back(rand() % 101);

  return randoms;
}
