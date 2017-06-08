#include <cstdio>
#include <cstring>

char first_word[1005];
char second_word[1005];
int fst_len, scd_len;
int tab[1005][1005];
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
    // printf("%d\n",tab[fst_len][scd_len] );
    get_word();
    for(int i=0; i< it; i++)
    {
      printf("%c",word[it-i -1] );
    }
    show_tab();
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
  int licznik=0;
  for(int i=0; i<=fst_len; i++)
  {
    for(int j=0; j<=scd_len; j++)
    {
      if(tab[i][j] == tab[fst_len][scd_len])
      {
        licznik = (licznik +1 % M);
      }
    }
  }
  return licznik;
}
void get_word()
{
  int i=fst_len, j= scd_len;
  while(i>0 && j>0)
  {
    if(first_word[i-1] == second_word[j-1])
    {
      word[it++] = first_word[i-1] ;
      i--;
      j--;
    }
    else
    {
      if(tab[i][j-1] > tab[i-1][j])
      {
        j--;
      }
      else
      {
        i--;
      }
    }
  }
}
