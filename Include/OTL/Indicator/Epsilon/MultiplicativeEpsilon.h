/*!
Copyright (C) 2014, 申瑞珉 (Ruimin Shen)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <vector>
#include <cmath>
#include <limits>
#include <numeric>
#include "Epsilon.h"

namespace otl
{
namespace indicator
{
namespace epsilon
{
template <typename _TReal>
class MultiplicativeEpsilon : public Epsilon<_TReal>
{
public:
	typedef _TReal TReal;
	typedef Epsilon<_TReal> TSuper;
	typedef typename TSuper::TReal TMetric;
	typedef typename TSuper::TPoint TPoint;
	typedef typename TSuper::TFront TFront;

	MultiplicativeEpsilon(const std::vector<TPoint> &front);
	virtual ~MultiplicativeEpsilon(void);

protected:
	TMetric _DoEvaluate(const TFront &front);
	TReal _Epsilon(const TPoint &point) const;
	static TReal _Epsilon(const TPoint &point, const TPoint &reference);
};

template <typename _TReal>
MultiplicativeEpsilon<_TReal>::MultiplicativeEpsilon(const std::vector<TPoint> &front) : TSuper(front)
{
}

template <typename _TReal>
MultiplicativeEpsilon<_TReal>::~MultiplicativeEpsilon(void)
{
}

template <typename _TReal>
typename MultiplicativeEpsilon<_TReal>::TMetric MultiplicativeEpsilon<_TReal>::_DoEvaluate(const TFront &front)
{
	TReal epsilon = 0;
	for (size_t i = 0; i < front.size(); ++i)
	{
		const TReal _epsilon = _Epsilon(*front[i]);
		assert(_epsilon >= 0);
		if (epsilon < _epsilon)
			epsilon = _epsilon;
	}
	return epsilon;
}

template <typename _TReal>
_TReal MultiplicativeEpsilon<_TReal>::_Epsilon(const TPoint &point) const
{
	TReal epsilon = 0;
	for (size_t i = 0; i < this->GetFront().size(); ++i)
	{
		const TReal _epsilon = _Epsilon(point, this->GetFront()[i]);
		assert(_epsilon >= 0);
		if (epsilon < _epsilon)
			epsilon = _epsilon;
	}
	return epsilon;
}

template <typename _TReal>
_TReal MultiplicativeEpsilon<_TReal>::_Epsilon(const TPoint &point, const TPoint &reference)
{
	TReal epsilon = 0;
	for (size_t i = 0; i < point.size(); ++i)
	{
		const TReal _epsilon = reference[i] / point[i];
		if (epsilon < _epsilon)
			epsilon = _epsilon;
	}
	return epsilon;
}
}
}
}
