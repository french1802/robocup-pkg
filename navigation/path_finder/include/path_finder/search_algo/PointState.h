/**
 * \file 		PointState.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2015-11-21
 * \copyright	PyroTeam, Polytech-Lille
 * \license
 * \version
 */


#ifndef PATH_FINDER_POINTSTATE_H_
#define PATH_FINDER_POINTSTATE_H_

#include <functional>

#include <geometry_msgs/Point.h>
#include "AStarState.h"

class PointState : public AStarState
{
public:
    PointState() : AStarState()
    {

    }
    virtual ~PointState()
    {

    }
    void set(double x, double y)
    {
        m_point.x = x;
        m_point.y = y;
    }
    const geometry_msgs::Point &get() const
    {
        return m_point;
    }

    virtual bool compare(const State &s) const override
    {
        const PointState &ps = dynamic_cast<const PointState&>(s);
        static double const epsilon = 0.001;
        return (std::abs(m_point.x - ps.get().x) < epsilon &&
                std::abs(m_point.y - ps.get().y) < epsilon);
    }

    virtual std::size_t hash() const override
    {
        std::size_t const h1 (std::hash<double>()(m_point.x));
        std::size_t const h2 (std::hash<double>()(m_point.y));
        return h1 ^ (h2 << h1);
    }

    virtual std::ostream& toStream(std::ostream& os) const override
    {
        os << m_point << "\nfCost = " << m_cost
                      << "\nstepCost = "<< m_stepCost
                      << "\ngCost = " << m_gCost;
        return os;
    }
protected:
    geometry_msgs::Point m_point;
};


#endif /* PATH_FINDER_POINTSTATE_H_ */
