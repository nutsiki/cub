#include "minilibx/mlx.h"

#include <math.h>
#include <string.h>
// #include <vector>
// #include <iostream>

int 	new_fram(void* param)
{
	printf("coucou [%p]\n", param);
	return 0;
}

int	main()
{
	void	*mlx_ptr;
	void 	*win_ptr;
	void 	*img_ptr;
	int		size_x;
	int 	size_y;
	char 	*title;
	int 	width;
	int 	height;
	int i;
	int j;
	int id;
	double position_p_x;
	double position_p_y;
	double dir_v_x;
	double dir_v_y;
	double plan_2d_x;
	double plan_2d_y;
	double time;
	double oldtime;

	size_x = 500;
	size_y = 500;
	width = 300;
	height = 300;
	position_p_y = 200;
	position_p_x = 200;
	dir_v_x = -1;
	dir_v_y = 0;
	plan_2d_x = 0;
	plan_2d_y = 0.66;
	time = 0;
	oldtime = 0;
	title = "Test";
	if (!(mlx_ptr = mlx_init()))
		return (-1);
	if (!(win_ptr = mlx_new_window(mlx_ptr, size_x, size_y, title)))
		return (-1);
	if (!(img_ptr = mlx_new_image(mlx_ptr, width, height)))
		return (-1);
	int *kk = (int *)mlx_get_data_addr(img_ptr, &id, &id, &id);
	j = height;
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	// mlx_loop_hook(mlx_ptr, new_fram, &map);
	mlx_loop(mlx_ptr);

	return (0);
}


// #define screenWidth 640
// #define screenHeight 480
// #define mapWidth 24
// #define mapHeight 24

// int worldMap[mapWidth][mapHeight]=
// 		{
// 				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
// 				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// 		};

// int main(int /*argc*/, char */*argv*/[])
// {
// 	double posX = 22, posY = 12;  //x and y start position
// 	double dirX = -1, dirY = 0; //initial direction vector
// 	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

// 	double time = 0; //time of current frame
// 	double oldTime = 0; //time of previous frame



// //	screen(screenWidth, screenHeight, 0, "Raycaster");
// 	void	*mlx_ptr;
// 	void 	*win_ptr;
// 	void 	*img_ptr;
// 	int		size_x;
// 	int 	size_y;
// 	char 	*title;
// 	int 	width;
// 	int 	height;
// 	int i;
// 	int j;
// 	int id;

// 	size_x = 500;
// 	size_y = 500;
// 	width = 300;
// 	height = 300;
// 	title = "Test";
// 	if (!(mlx_ptr = mlx_init()))
// 		return (-1);
// 	if (!(win_ptr = mlx_new_window(mlx_ptr, size_x, size_y, title)))
// 		return (-1);
// 	if (!(img_ptr = mlx_new_image(mlx_ptr, width, height)))
// 		return (-1);
// 	int *kk = (int *)mlx_get_data_addr(img_ptr, &id, &id, &id);
// 	while(!done())
// 	{
// 		for(int x = 0; x < w; x++)
// 		{
// 			//calculate ray position and direction
// 			double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
// 			double rayDirX = dirX + planeX * cameraX;
// 			double rayDirY = dirY + planeY * cameraX;
// 			//which box of the map we're in
// 			int mapX = int(posX);
// 			int mapY = int(posY);

// 			//length of ray from current position to next x or y-side
// 			double sideDistX;
// 			double sideDistY;

// 			//length of ray from one x or y-side to next x or y-side
// 			double deltaDistX = std::abs(1 / rayDirX);
// 			double deltaDistY = std::abs(1 / rayDirY);
// 			double perpWallDist;

// 			//what direction to step in x or y-direction (either +1 or -1)
// 			int stepX;
// 			int stepY;

// 			int hit = 0; //was there a wall hit?
// 			int side; //was a NS or a EW wall hit?
// 			//calculate step and initial sideDist
// 			if(rayDirX < 0)
// 			{
// 				stepX = -1;
// 				sideDistX = (posX - mapX) * deltaDistX;
// 			}
// 			else
// 			{
// 				stepX = 1;
// 				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
// 			}
// 			if(rayDirY < 0)
// 			{
// 				stepY = -1;
// 				sideDistY = (posY - mapY) * deltaDistY;
// 			}
// 			else
// 			{
// 				stepY = 1;
// 				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
// 			}
// 			//perform DDA
// 			while (hit == 0)
// 			{
// 				//jump to next map square, OR in x-direction, OR in y-direction
// 				if(sideDistX < sideDistY)
// 				{
// 					sideDistX += deltaDistX;
// 					mapX += stepX;
// 					side = 0;
// 				}
// 				else
// 				{
// 					sideDistY += deltaDistY;
// 					mapY += stepY;
// 					side = 1;
// 				}
// 				//Check if ray has hit a wall
// 				if(worldMap[mapX][mapY] > 0) hit = 1;
// 			}
// 			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
// 			if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
// 			else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

// 			//Calculate height of line to draw on screen
// 			int lineHeight = (int)(h / perpWallDist);

// 			//calculate lowest and highest pixel to fill in current stripe
// 			int drawStart = -lineHeight / 2 + h / 2;
// 			if(drawStart < 0)drawStart = 0;
// 			int drawEnd = lineHeight / 2 + h / 2;
// 			if(drawEnd >= h)drawEnd = h - 1;

// 			//choose wall color
// 			ColorRGB color;
// 			switch(worldMap[mapX][mapY])
// 			{
// 				case 1:  color = RGB_Red;    break; //red
// 				case 2:  color = RGB_Green;  break; //green
// 				case 3:  color = RGB_Blue;   break; //blue
// 				case 4:  color = RGB_White;  break; //white
// 				default: color = RGB_Yellow; break; //yellow
// 			}

// 			//give x and y sides different brightness
// 			if(side == 1) {color = color / 2;}

// 			//draw the pixels of the stripe as a vertical line
// 			verLine(x, drawStart, drawEnd, color);
// 		}
// 		//timing for input and FPS counter
// 		oldTime = time;
// 		time = getTicks();
// 		double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
// 		print(1.0 / frameTime); //FPS counter
// 		redraw();
// 		cls();

// 		//speed modifiers
// 		double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
// 		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
// 		readKeys();
// 		//move forward if no wall in front of you
// 		if(keyDown(SDLK_UP))
// 		{
// 			if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
// 			if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
// 		}
// 		//move backwards if no wall behind you
// 		if(keyDown(SDLK_DOWN))
// 		{
// 			if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
// 			if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
// 		}
// 		//rotate to the right
// 		if(keyDown(SDLK_RIGHT))
// 		{
// 			//both camera direction and camera plane must be rotated
// 			double oldDirX = dirX;
// 			dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
// 			dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
// 			double oldPlaneX = planeX;
// 			planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
// 			planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
// 		}
// 		//rotate to the left
// 		if(keyDown(SDLK_LEFT))
// 		{
// 			//both camera direction and camera plane must be rotated
// 			double oldDirX = dirX;
// 			dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
// 			dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
// 			double oldPlaneX = planeX;
// 			planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
// 			planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
// 		}
// 	}
// }
