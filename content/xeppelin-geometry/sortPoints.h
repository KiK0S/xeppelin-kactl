/**
 * Author: kikos
 * Description: Sort set of points around some point.
 * Time: O(n log n)
 */

sort(points.begin(), points.end(), [&](const Point& a, const Point& b) {
    Point v1 = a - center, v2 = b - center;
    int side1 = sideOf(center, center + Point(1, 0), a);
    int side2 = sideOf(center, center + Point(1, 0), b);
    return {side1, -v1.cross(v2), v1.dist2()} < {side2, 0, v2.dist2()};
});
