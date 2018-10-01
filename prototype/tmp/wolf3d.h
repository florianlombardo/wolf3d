#ifndef WOLF3D_H
# define WOLF3D_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <SDL/SDL.h>

# define WID 320
# define HEI 200

typedef struct	s_plyr
{
	double		posx;
	double		posy;
	double		mid_angle;
	//double		dist_plane;
}				t_plyr;

#endif