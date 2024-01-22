/**
 * Description:\\
\begin{minipage}{75mm}
\includegraphics[width=\textwidth]{../src/geometry/ccw}
\end{minipage}
 * Source: Gifted Infants library
 * Status: Tested with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_C
 */

#pragma once

#include "geometry/base.hpp"

namespace geometry {

// CGL_1_C
// 1: COUNTER_CLOCKWISE (1)
// -1: CLOCKWISE (2)
// 2: ONLINE_BACK (3)
// -2: ONLINE_FRONT (4)
// 0: ON_SEGMENT (5)
inline int ccw(const P& a, const P& b) { /// start-hash
	int s = sgncrs(a, b);
	if (s) return s;
	if (!sgn(rabs(b)) || !sgn(rabs(b-a))) return 0;
	if (dot(a, b) < 0) return 2;
	if (dot(-a, b-a) < 0) return -2;
	return 0;
} /// end-hash

inline int ccw(const P& a, const P& b, const P& c) {
	return ccw(b-a, c-a);
}

} // namespace geometry