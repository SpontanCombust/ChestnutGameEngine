#include "chestnut/engine/maths/curves.hpp"

#include <algorithm>


namespace chestnut::engine
{
    static std::vector<std::vector<int>> pascalTriangle {
        {1},
        {1,1},
        {1,2,1},
        {1,3,3,1},
        {1,4,6,4,1},
        {1,5,10,10,5,1}
    };

    static const std::vector<int>& expandPascalTriangle(unsigned int degree)
    {
        if(degree < pascalTriangle.size())
        {
            return pascalTriangle[degree];
        }

        static std::vector<int> newRow;
        while(degree >= pascalTriangle.size())
        {
            newRow.clear();
            newRow.reserve(degree + 1);

            const std::vector<int>& prevRow = pascalTriangle.back();

            newRow.push_back(1);
            for (size_t i = 0; i < prevRow.size() - 1; i++)
            {
                newRow.push_back(prevRow[i] + prevRow[i + 1]);
            }
            newRow.push_back(1);

            pascalTriangle.push_back(newRow);
        }

        return pascalTriangle[degree];
    }


    std::vector<vec3f> plotBezierCurve(const std::vector<SBezierCurvePoint>& points, unsigned int segmentCount)
    {
        std::vector<vec3f> result;

        if(points.size() < 2)
        {
            return result;
        }

        if(points.size() == 2 || segmentCount == 0 || segmentCount == 1)
        {
            result.push_back(points[0].position);
            result.push_back(points[1].position);
            return result;
        }


        const unsigned int BEZIER_DEGREE = points.size() - 1;
        const float STEP = 1.f / segmentCount;

        result.reserve(segmentCount + 1);
        result.push_back(points[0].position);

        float t = STEP;
        const std::vector<int>& pascalRow = expandPascalTriangle(BEZIER_DEGREE);
        for(size_t i = 0; i < segmentCount - 1; i++)
        {
            float sum(0.f);
            vec3f sumWeighed(0.f);

            for (size_t j = 0; j < pascalRow.size(); j++)
            {
                float component = points[j].ratio * (float)pascalRow[j] * (float)std::pow((1 - t), BEZIER_DEGREE - j) * (float)std::pow(t, j);
                sum += component;
                sumWeighed += points[j].position * component;
            }

            result.push_back(sumWeighed / sum);
            t += STEP;
        }

        result.push_back(points[points.size() - 1].position);


        return result;
    }

} // namespace chestnut::engine
