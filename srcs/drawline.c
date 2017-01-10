#include "fdf.h"

#define max(x,y) ( \
    { __auto_type __x = (x); __auto_type __y = (y); \
      __x > __y ? __x : __y; })

void		buffer_plot(t_fdf_data fdf_data, int x, int y) {
	int opp;
	int pos;
	int color;
	
	if (x < 0 || x > 512 || y < 0 || y > 512)
		return;
	opp = fdf_data.bpp / 8;
	color = mlx_get_color_value(fdf_data.mlx, 65535);
	pos = y * fdf_data.sl + x * opp;
	fdf_data.data[pos] = color;
}

int Sign(int dxy)
{
	if (dxy<0)
		return -1;
	else if (dxy>0)
		return 1;
	else
		return 0;
}

void		drawline(t_fdf_data fdf_data, int x1, int y1, int x2, int y2)
{
    int Dx = x2 - x1;
    int Dy = y2 - y1;

    //# Increments
    int Sx = Sign(Dx); 
    int Sy = Sign(Dy);

    //# Segment length
    Dx = abs(Dx); 
    Dy = abs(Dy); 
    int D = max(Dx, Dy);

    //# Initial remainder
    double R = D / 2;

    int X = x1;
    int Y = y1;
    if(Dx > Dy)
    {   
        //# Main loop
        for(int I=0; I<D; I++)
        {   

			buffer_plot(fdf_data, X, Y);
//            Set(X, Y, color)..................;
            //# Update (X, Y) and R
            X+= Sx; R+= Dy; //# Lateral move
            if (R >= Dx)
            {
                Y+= Sy; 
                R-= Dx; //# Diagonal move
            }
        }
    }
    else
    {   
        //# Main loop
        for(int I=0; I<D; I++)
        {    
			buffer_plot(fdf_data, X, Y);
            //# Update (X, Y) and R
            Y+= Sy; 
            R+= Dx; //# Lateral move
            if(R >= Dy)
            {    
                X+= Sx; 
                R-= Dy; //# Diagonal move
            }
        }
    }
}
