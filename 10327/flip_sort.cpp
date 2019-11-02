#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll merge(size_t N, vector<int>::iterator first, vector<int>::iterator middle, vector<int>::iterator last)
{
  auto begin = first, central = middle;
  vector<int> temp(N);

  ll k = 0, inversions = 0;

  // Descomente tudo que tiver cout abaixo para entender melhor o funcionamento do código

  /*
  for (auto i = begin; i != last; i++)
    cout << *i << " ";

  cout << endl;
  */

  while (begin != middle and central != last)
  {
    // cout << *begin << " x " << *central << endl;

    temp[k++] = min(*begin, *central);

    /*
    Se o da esquerda for o menor(E), significa que os elementos menores do segundo array
    que já estão no array temporário estão invertidos em relação ao elemento E e dessa forma
    basta contabilizar esse elementos que já foram inseridos no array temporário para saber as inversões desse caso
    */

    if (temp[k - 1] == *begin)
    {
      /*
      if (central - middle > 0)
      {
        cout << "Inversão à esquerda dos elementos já inseridos do array da direita" << endl;
        cout << central - middle << " inversões com o elemento " << *begin << endl;
      }
      */

      inversions += (central - middle);
    }

    temp[k - 1] == *begin ? ++begin : ++central;
  }

  while (begin != middle)
  {
    /*
    cout << "Inversão à direita dos elementos já inseridos do array da direita" << endl;
    cout << last - middle << " inversões com o elemento " << *begin << endl;
    */

    /*
    Se algum elemento do array da esquerda ficar sem ser inserido no array temporário,
    significa que ele é maior que todos os elementos do array da direita e dessa forma a inversão é relacionado
    a quantidade de elementos do segundo array
    */

    temp[k++] = *begin++;
    inversions += (last - middle);
  }

  // Nesse caso basta inserir ao fim pois não há inversões

  while (central != last)
    temp[k++] = *central++;

  for (const auto &elem : temp)
    *first++ = elem;

  return inversions;
}

ll mergesort(vector<int>::iterator first, vector<int>::iterator last)
{
  auto N = last - first;

  if (N == 1)
    return 0;

  auto middle = first + (N + 1) / 2;
  ll inversions = 0;

  inversions += mergesort(first, middle);
  inversions += mergesort(middle, last);
  inversions += merge(N, first, middle, last);

  return inversions;
}

int main()
{
  ios::sync_with_stdio(false);

  int N, aux;

  while (cin >> N)
  {
    vector<int> elements;

    while (N--)
      cin >> aux, elements.push_back(aux);

    /*
    A contagem de Flips necessários para ordenação também pode ser
    interpretada como a quantidade de inversões do array, de forma que
    se as inversões forem desfeitas o array fica ordenado, por isso o uso do mergesort
    */

    auto inversions = mergesort(elements.begin(), elements.end());

    cout << "Minimum exchange operations : " << inversions << '\n';
  }

  return 0;
}