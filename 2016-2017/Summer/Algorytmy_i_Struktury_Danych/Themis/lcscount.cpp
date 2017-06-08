#include <cstdio>
#include <cstring>

char first_word[1005];
char second_word[1005];
int fst_len, scd_len;
int tab[1005][1005];
int D[1005][1005];
int M;
char word[1005];
int it=0;

void read_data();
void lcs();
void show_tab();
int how_many();
void get_word();

int main()
{
  // int T;
  scanf("%d\n",&M );
  // for(int i=0; i<T; i++)
  // {
    read_data();
    lcs();
    printf("%d %d\n",tab[fst_len][scd_len], how_many() );
    // show_tab();
  // }
  return 0;
}

void lcs()
{
  for(int i=0; i<=fst_len; i++ )
  {
    tab[i][0] = 0;
  }
  for(int j=0; j<=scd_len; j++)
  {
    tab[0][j] = 0;
  }
  for(int i=1; i<=fst_len; i++)
  {
    for(int j=1; j<=scd_len; j++)
    {
      if(first_word[i-1] == second_word[j-1])
      {
        tab[i][j] = tab[i-1][j-1]+1;
      }
      else
      {
        if(tab[i-1][j] > tab[i][j-1])
        {
          tab[i][j] = tab[i-1][j];
        }
        else
        {
          tab[i][j] = tab[i][j-1];
        }
      }
    }
  }
}

void read_data()
{
  // scanf("%d\n" ,&fst_len);
  scanf("%s\n", first_word);
  // scanf("%d\n", &scd_len);
  fst_len = strlen(first_word);
  scanf("%s\n", second_word);
  scd_len = strlen(second_word);
}

void show_tab()
{
  puts("");puts("");
  for(int i=0; i<=fst_len; i++)
  {
    for(int j=0; j<=scd_len; j++)
    {
      printf("%d ", tab[i][j]);
    }
    puts("");
  }
  puts("");puts("");
}

int how_many()
{
  for(int i=0; i<=fst_len; i++)
  {
    for(int j=0; j<=scd_len; j++)
    {
      if(i==0 || j==0)
      {
        D[i][j] =1;
      }
      else
      {
        D[i][j]=0;
        if(first_word[i-1] == second_word[j-1])
        {
          D[i][j] = D[i-1][j-1];
        }
        else
        {
          if (tab[i-1][j] == tab[i][j]) D[i][j] = (D[i][j]+D[i-1][j]) % M;
          if (tab[i][j-1] == tab[i][j]) D[i][j] =(D[i][j] + D[i][j-1] ) % M;
          if (tab[i-1][j-1] == tab[i][j]) D[i][j] = (D[i][j] - D[i-1][j-1])%M;
        }
      }
    }
  }
  return D[fst_len][scd_len];
}
