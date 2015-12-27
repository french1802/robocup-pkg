/**
 * \file        occupancy_grid_utils.cpp
 *
 * \brief       bibliothèque de fonctions de manipulation des nav_msgs::OccupancyGrid
 *
 * \author      Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date        2015-11-21
 * \copyright   PyroTeam, Polytech-Lille
 * \license
 * \version
 */

#include "occupancy_grid_utils.h"


namespace occupancy_grid_utils {

void createEmptyMap(nav_msgs::OccupancyGrid &map, const geometry_msgs::Point &size, const geometry_msgs::Point &origin, const std::string &frame_id, double resolution)
{
	map.header.frame_id = frame_id;
	map.info.origin.position.x = origin.x;
	map.info.origin.position.y = origin.y;
	map.info.origin.position.z = 0;
	map.info.origin.orientation.x = 0;
	map.info.origin.orientation.y = 0;
	map.info.origin.orientation.z = 0;
	map.info.origin.orientation.w = 1;
	map.info.map_load_time = ros::Time::now();
	map.info.resolution = resolution;
	map.info.width = size.x/resolution;
	map.info.height = size.y/resolution;
	map.data.assign(map.info.width * map.info.height, 0);
}

/**
 * fonction qui calcule la position dans le vecteur de donnée d'un OccupancyGrid
 * d'un point fourni en coordonnées métrique
 *
 * \param grid la grille
 * \param x abscisse du point en m
 * \param y ordonnée du point en m
 *
 * \return index du tableau data de l'occupancyGrid
 *         -1 si le point n'est pas sur la gridMap
 */
int getCell(const nav_msgs::OccupancyGrid &grid, float x, float y)
{
    //code from navigation/path_tracker/src/map.cpp
	//modifié pour ajouter des protections
	float res = grid.info.resolution;
	int width = grid.info.width;
	int height = grid.info.height;
	float x0 = grid.info.origin.position.x;
	float y0 = grid.info.origin.position.y;

	float xMin = x0;
	float xMax = x0 + res*width;
	float yMin = y0;
	float yMax = y0 + res*height;
	if (!(xMin < x && x < xMax) || !(yMin < y && y < yMax))
	{
		return -1;
	}

	int hCell = 0;
	int wCell = 0;
	int cell = 0;

	hCell = round((y - y0) / res);
	wCell = round((x - x0) / res);
	cell = hCell * width + wCell;

	return cell;
}

/**
 * fonction qui retourne la valeur d'un point fourni en coordonnées métrique
 * dans une OccupancyGrid
 *
 * \param grid la grille
 * \param x abscisse du point en m
 * \param y ordonnée du point en m
 *
 * \return valeur du point, 255 si le point n'est pas sur la map
 */
int getCellValue(const nav_msgs::OccupancyGrid &grid, float x, float y)
{
	int cell = 0;
	if ((cell = getCell(grid, x, y)) < 0)
	{
		return 255;
	}
	else
	{
		return grid.data[cell];
	}

}

/**
 * fonction qui retourne la valeur d'un point fourni en coordonnées métrique
 * dans une OccupancyGrid
 *
 * \param grid la grille
 * \param p point en coordonnées métrique
 *
 * \return valeur du point, 255 si le point n'est pas sur la map
 */
int getCellValue(const nav_msgs::OccupancyGrid &grid, const geometry_msgs::Point &p)
{
    return getCellValue(grid, p.x, p.y);
}

/**
 * fonction qui retourne la valeur d'un point fourni en coordonnées métrique
 * dans une OccupancyGrid
 *
 * \param grid la grille
 * \param p pose en coordonnées métrique
 *
 * \return valeur du point, 255 si le point n'est pas sur la map
 */
int getCellValue(const nav_msgs::OccupancyGrid &grid, const geometry_msgs::Pose2D &p)
{
    return getCellValue(grid, p.x, p.y);
}

geometry_msgs::Point getCellAsPixelCoord(nav_msgs::OccupancyGrid &grid, float x, float y)
{

	//TODO redondance de code à regler avec la fonction getCell
	geometry_msgs::Point p;
	p.x = -1;
	p.y = -1;
	float res = grid.info.resolution;
	int width = grid.info.width;
	int height = grid.info.height;
	float x0 = grid.info.origin.position.x;
	float y0 = grid.info.origin.position.y;

	float xMin = x0;
	float xMax = x0 + res*width;
	float yMin = y0;
	float yMax = y0 + res*height;
	if (!(xMin < x && x < xMax) || !(yMin < y && y < yMax))
	{
		return p;
	}

	p.y = round((y - y0) / res);
	p.x = round((x - x0) / res);

	return p;

}

geometry_msgs::Point getCellAsPixelCoord(nav_msgs::OccupancyGrid &grid, const geometry_msgs::Point &p)
{
	return getCellAsPixelCoord(grid, p.x, p.y);
}

void setCell(nav_msgs::OccupancyGrid &grid, float x, float y, int value)
{
	geometry_msgs::Point p= getCellAsPixelCoord(grid, x, y);
	setPixelCell(grid, p, value);
}

void setPixelCell(nav_msgs::OccupancyGrid &grid, unsigned int x, unsigned int y, const int& value)
{

	if (x < grid.info.width && y < grid.info.height)
	{
		int valueSaturated = 0;
		if (value < 0)
		{
			valueSaturated = 0;
		}
		else if (value > 100)
		{
			valueSaturated = 100;
		}
		else
		{
			valueSaturated = value;
		}
		grid.data[y * grid.info.width + x] = valueSaturated;

	}

}
void setPixelCell(nav_msgs::OccupancyGrid &grid, const geometry_msgs::Point &p, const int& value)
{
	setPixelCell(grid, p.x, p.y, value);
}

void addGradient(nav_msgs::OccupancyGrid &grid, double distance_max, int min_value)
{
	const float &resolution = grid.info.resolution;
	const int &width = grid.info.width;
	const int &height = grid.info.height;
	std::vector<signed char> &data = grid.data;

	//on cherche les points bordures
	std::set<std::pair<int,int>> borderPoints;

	for(int x = 1; x < width-1; x++)
	{
		for(int y = 1; y < height; y++)
		{
			if (data[y * width + x] ==100)
			{
				if (data[y * width + x-1] != data[y * width + x] ||
					data[y * width + x+1] != data[y * width + x] ||
					data[(y-1) * width + x] != data[y * width + x] ||
					data[(y+1) * width + x] != data[y * width + x] ||
					data[(y-1) * width + x-1] != data[y * width + x] ||
					data[(y+1) * width + x-1] != data[y * width + x] ||
					data[(y-1) * width + x+1] != data[y * width + x] ||
					data[(y+1) * width + x+1] != data[y * width + x])
				{
					borderPoints.insert(std::make_pair(x, y));
				}
			}
		}
	}

	double a = double(min_value - 100)/distance_max;
	for(int x = 1; x < width-1; x++)
	{
		for(int y = 1; y < height; y++)
		{
			if (borderPoints.find(std::make_pair(x,y)) == borderPoints.end())
			{
				for (const auto &borderPoint : borderPoints)
				{
					int x1 = borderPoint.first;
					int y1 = borderPoint.second;
					double d = sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1))*resolution;
					signed char value = 0;
					if (d < distance_max)
					{
						value = (signed char)(d * a) + 100;
					}

					data[y * width + x] = std::max(value, data[y * width + x]);
				}
			}
		}
	}


}


} // namespace occupancy_grid_utils
