#include "ft_ping.h"

float   moy(float *tab)
{
    float   final = 0;
    int     x;

    for(x = 0; tab[x] != -1; x++)
        final += tab[x];
    final /= x;
    return final;
}

float   deviation(float *tab)
{
    float   final = 0, m = moy(tab);
    int     x;

    for(x = 0; tab[x] != -1; x++)
        final += powf(tab[x] - m, 2);
    final = sqrtf(final / x);
    return final;
}

float*  add_time(float *tab, float time)
{
    float*  new_tab;
    if(tab[0] == -1)
    {
        new_tab = malloc(2 * sizeof(float));
        new_tab[0] = time;
        new_tab[1] = -1;
    }
    else
    {
        int x;
        for(x = 0; tab[x] != -1; x++);
        new_tab = malloc((x + 2) * sizeof(float));
        for(x = 0; tab[x] != -1; x++)
            new_tab[x] = tab[x];
        new_tab[x++] = time;
        new_tab[x] = -1;
    }
    free(tab);
    return new_tab;
}

void    manage_time(struc *global, float time)
{
    if (time > global->time_max)
        global->time_max = time;
    if (time < global->time_min)
        global->time_min = time;
    global->time = add_time(global->time, time);
}