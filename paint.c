#include "paint.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void image_print(int I[NROWS][NCOLS])
{
	for (int row = 0; row < NROWS; ++row)
	{
		for (int col = 0; col < NCOLS; ++col)
		{
			printf("%c", I[row][col]);
		}
		
		printf("\n");
	}
}

void image_init(int I[NROWS][NCOLS], symbols_t symbol)
{
	for (int row = 0; row < NROWS; ++row)
	{
		for (int col = 0; col < NCOLS; ++col)
		{
			I[row][col] = symbol;
		}
	}
}

void add_point(int I[NROWS][NCOLS], symbols_t symbol, int col, int row)
{
	if (row > NROWS - 1 || row < 0)
		return;
	if (col > NCOLS - 1 || col < 0)
		return;

	I[row][col] = symbol;
}

void add_line_hori(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int length)
{
	for (int col = 0; col < length; ++col)
	{
		add_point(I, symbol, col0 + col, row0);
	}
}

void add_line_vert(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int length)
{
	for (int row = 0; row < length; ++row)
	{
		add_point(I, symbol, col0, row0 + row);
	}
}

void add_rectangle(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int lcol, int lrow)
{
	add_line_hori(I, symbol, col0, row0, lcol);
	add_line_vert(I, symbol, col0, row0, lrow);

	add_line_hori(I, symbol, col0, row0 + lrow - 1, lcol - 1);
	add_line_vert(I, symbol, col0 + lcol - 1, row0 + 1, lrow - 1);
}

void add_points(int I[NROWS][NCOLS], symbols_t symbol, int cols[], int rows[], int n)
{
	for (int i = 0; i < n; i++)
	{
		add_point(I, symbol, cols[i], rows[i]);
	}
}

void add_line_up(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int length)
{
	for (int i = 0; i < length; i++)
	{
		add_point(I, symbol, col0 + i, row0 - i);
	}
}

void add_line_down(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int length)
{
	for (int i = 0; i < length; i++)
	{
		add_point(I, symbol, col0 + i, row0 + i);
	}
}

void add_circle(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, double r)
{
	for (int row = 0; row < NROWS; row++)
	{
		for (int col = 0; col < NCOLS; col++)
		{
			double distance = sqrt(pow(row - row0, 2.0) + pow(col - col0, 2.0));

			if (distance <= r)
			{
				add_point(I, symbol, col, row);
			}
		}
	}
}