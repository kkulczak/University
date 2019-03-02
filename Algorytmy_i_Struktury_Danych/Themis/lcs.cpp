#include <cstdio>

char first_word[1005];
char second_word[1005];
int fst_len, scd_len;

int tab[1005][1005];
void read_data();
void lcs();
void show_tab();
int main()
{
  int T;
  scanf("%d\n",&T );
  for(int i=0; i<T; i++)
  {
    read_data();
    lcs();
    printf("%d\n",tab[fst_len][scd_len] );
    //show_tab();
  }
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
  scanf("%d\n" ,&fst_len);
  scanf("%s\n", first_word);
  scanf("%d\n", &scd_len);
  scanf("%s\n", second_word);
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
