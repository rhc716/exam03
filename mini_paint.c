#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_puterr(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	main(int argc, char **argv)
{
	FILE 	*file;
	char	*image;
	int		read;

	// 배경
	int		bg_w;
	int		bg_h;
	char	bg_c;
	int		x;
	int		y;
	float	distance;

	// 그림 (픽셀)
	char	pix_type;
	float	pix_x;
	float	pix_y;
	float	pix_r;
	char	pix_c;

	if (argc != 2)
		return (ft_puterr("Error: argument\n"));
	if (!(file = fopen(argv[1], "r")))
		return (ft_puterr("Error: Operation file corrupted\n"));
	if ((read = fscanf(file, "%d %d %c\n", &bg_w, &bg_h, &bg_c) != 3))
		return (ft_puterr("Error: Operation file corrupted\n"));
	if (!(bg_w > 0 && bg_w <= 300) || !(bg_h > 0 && bg_h <= 300))
		return (ft_puterr("Error: Operation file corrupted\n"));
	image = (char *)malloc(sizeof(char) * (bg_w * bg_h));
	// 배경 채우기
	memset(image, bg_c, bg_w * bg_h);
	read = fscanf(file, "%c %f %f %f %c\n", &pix_type, &pix_x, &pix_y, &pix_r, &pix_c);
	// 그림 채우기
	while (read == 5)
	{
		y = 0;
		while (y < bg_h)
		{
			x = 0;
			while (x < bg_w)
			{
				distance = sqrtf(powf((float)x - pix_x, 2.0) * powf((float)y - pix_y, 2.0));
				// 공통 조건
				if (distance <= pix_r)
				{
					if (pix_type == 'c') // 테두리만
					{
						if (distance > pix_r - 1.0000000)
							image[y * bg_h + x] = pix_c;
					}
					else if (pix_type == 'C') // 채워진
						image[y * bg_h + x] = pix_c;
				}
				x++;
			}
			y++;
		}
		read = fscanf(file, "%c %f %f %f %c\n", &pix_type, &pix_x, &pix_y, &pix_r, &pix_c);
	}
	// EOF
	if (read != -1)
	{
		return (ft_puterr("Error: Operation file corrupted\n"));
		free(image);
		fclose(file);
		return (1);
	}
	// 그리기
	y = 0;
	while (y < bg_h)
	{
		write(1, &image[y * bg_w], bg_w);
		write(1, "\n", 1);
		y++;
	}
	free(image);
	fclose(file);
	return (0);
}