#include <limits>
#include <cstdio>
#include <algorithm>
struct kom
{
  size_t sum;
  size_t left;
  size_t right;
};
struct kom tab[205][205];
unsigned int data_tab[205];
size_t n;
void read_data();
size_t cyk();
void show_tab();
void show_matrixes();

int main()
{
  size_t T;
  scanf("%zu",&T );
  for(size_t i=0; i<T; i++)
  {
    read_data();
    // show_matrixes();
    // show_tab();
    printf("%zu\n",cyk() );
    // show_tab();
  }

  return 0;
}
void read_data()
{
  scanf("%zu",&n );
  for(size_t i=0; i<n+1; i++)
  {
    scanf("%u",&data_tab[i]);
  }
  for(size_t i=0; i<n; i++)
  {
    tab[0][i].left = data_tab[i];
    tab[0][i].right = data_tab[i+1];
    tab[0][i].sum = 0;
  }
}

size_t cyk()
{
  for(size_t h=1; h<n; h++)
  {
    for(size_t s=0 ; s < n-h; s++)
    {
      tab[h][s].sum = std::numeric_limits<std::size_t>::max() ;
      for(size_t i=0; i < h; i++ )
      {
        size_t i1 = i, j1= s, i2=h-i-1 , j2 = s+i+1;
        size_t new_sum = tab[i1][j1].sum + tab[i2][j2].sum +
            tab[i1][j1].left * tab[i1][j1].right * tab[i2][j2].right;
        if(new_sum < tab[h][s].sum)
        {
          // printf("new_sum:%zu\n",tab[i2][j2].right );
          tab[h][s].sum = new_sum;
          tab[h][s].left = tab[i1][j1].left;
          tab[h][s].right = tab[i2][j2].right;
        }
      }
    }
  }
  return tab[n-1][0].sum;
}
void show_tab()
{    puts("");
puts("");

  for(size_t i=0; i<n; i++)
  {
    for(size_t j=0; j<n;j++)
    {
      printf("%zu ",tab[i][j].sum );
    }
    puts("");
  }
  puts("");
  puts("");

}
void show_matrixes()
{
  for(size_t i=0; i<n; i++)
  {
    printf("(%3zu,%3zu,%3zu)\n",tab[0][i].left, tab[0][i].sum, tab[0][i].right );
  }
}
