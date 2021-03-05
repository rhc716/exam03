#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_puterr(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	main(int argc, char **argv)
{
	FILE 	*file;
	char    *image;
	int		read;

	// 배경
	int		bg_w;
	int		bg_h;
	char	bg_c;
	int		x;
	int		y;

	// 도형 (픽셀)
	char	pix_type;
	float	pix_x;
	float	pix_y;
	float	pix_w;
	float	pix_h;
	char	pix_c;

	if (argc != 2)
		return (ft_puterr("Error: argument\n"));
	if (!(file = fopen(argv[1], "r")))
		return (ft_puterr("Error: Operation file corrupted\n"));
	if (fscanf(file, "%d %d %c\n", &bg_w, &bg_h, &bg_c) != 3)
		return (ft_puterr("Error: Operation file corrupted\n"));
	if (!(bg_w > 0 && bg_w <= 300 && bg_h > 0 && bg_h <= 300))
		return (ft_puterr("Error: Operation file corrupted\n"));
	image = (char *)malloc(sizeof(char) * (bg_w * bg_h));
	// 배경 채우기
	memset(image, bg_c, bg_w * bg_h);
	// 도형 채우기
	read = fscanf(file, "%c %f %f %f %f %c\n", &pix_type, &pix_x, &pix_y, &pix_w, &pix_h, &pix_c);
	while (read == 6)
	{
		// type과 가로 세로 에러
		if (!(pix_type == 'R' || pix_type == 'r') || !(pix_w > 0 && pix_h > 0))
		{
			free(image);
			return (ft_puterr("Error: Operation file corrupted\n"));
		}
		y = 0;
		while (y < bg_h)
		{
			x = 0;
			while (x < bg_w)
			{
				// 공통 조건
				if ((float)x >= pix_x && (float)x <= pix_x + pix_w && 
					(float)y >= pix_y && (float)y <= pix_y + pix_h)
				{
					if (pix_type == 'r') // 테두리만
					{
						if ((float)x < pix_x + 1.0000000 || (float)x > (pix_x + pix_w) - 1.0000000 ||
							(float)y < pix_y + 1.0000000 || (float)y > (pix_y + pix_h) - 1.0000000)
							image[y * bg_w + x] = pix_c;
					}
					else if (pix_type == 'R') // 채워진
						image[y * bg_w + x] = pix_c;
				}
				x++;
			}
			y++;
		}
		read = fscanf(file, "%c %f %f %f %f %c\n", &pix_type, &pix_x, &pix_y, &pix_w, &pix_h, &pix_c);
	}
	// EOF
	if (read != -1)
	{
		free(image);
		return (ft_puterr("Error: Operation file corrupted\n"));
	}
	// 그리기
	y = 0;
	while (y < bg_h)
	{
		write(1, image + y * bg_w, bg_w);
		write(1, "\n", 1);
		y++;
	}
	free(image);
	fclose(file);
	return (0);
}