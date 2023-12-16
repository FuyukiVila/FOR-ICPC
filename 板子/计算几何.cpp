#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1.0);
constexpr double eps = 1e-7;

constexpr int sgn(double x) {
    if (abs(x) < eps) {
        return 0;
    }
    if (x < 0) {
        return -1;
    } else {
        return 1;
    }
}

double radian(double degree) {
    return degree * PI / 180.0;
}

namespace Dimension2 {

    class Point {
    public:
        typedef Point Vector;
        double x, y;

        constexpr Point() : x(), y() {};

        constexpr Point(double x, double y) : x(x), y(y) {};

        //加
        constexpr Vector operator+(const Vector &p) const {
            return {x + p.x, y + p.y};
        }

        //减
        constexpr Vector operator-(const Vector &p) const {
            return {x - p.x, y - p.y};
        }

        //叉积
        constexpr double operator^(const Vector &p) const {
            return x * p.y - y * p.x;
        }

        //点积
        constexpr double operator*(const Vector &p) const {
            return x * p.x + y * p.y;
        }

        //数乘
        constexpr Vector operator*(double b) const {
            return {x * b, y * b};
        }

        constexpr Vector operator/(double b) const {
            return {x / b, y / b};
        }

        //等于
        constexpr bool operator==(const Point &p) const {
            return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
        }

        //绕着点p逆时针旋转弧度b
        constexpr Point &rotate(double b, const Point &p = {0, 0}) {
            double newX = (x - p.x) * cos(b) - (y - p.y) * sin(b) + p.x;
            double newY = (x - p.x) * cos(b) + (y - p.y) * cos(b) + p.y;
            x = newX;
            y = newY;
            return *this;
        }

        //模
        constexpr double norm() const {
            return sqrt(*this * *this);
        }

        //点距
        constexpr double distance(Point p) const {
            return (*this - p).norm();
        }


    };

    using Vector = Point;

    class Line {
    public:
        typedef Line Seg;
        Point a, b;

        constexpr Line() : a(), b() {}

        constexpr Line(Point a, Point b) : a(a), b(b) {}

        //两直线相交求交点
        //第一个值为0表示直线重合，为1表示平行,为2是相交
        //只有第一个值为2时，交点才有意义
        constexpr pair<int, Point> operator&(const Line &l) const {
            Point res;
            if (sgn((a - b) ^ (l.a - l.b)) == 0) {
                if (sgn((a - l.b) ^ (l.a - l.b)) == 0) {
                    return {0, res}; //重合
                } else {
                    return {1, res}; //平行
                }
            }
            double t = ((a - l.a) ^ (l.a - l.b)) / ((a - b) ^ (l.a - l.b));
            res.x += (b.x - a.x) * t;
            res.y += (b.y - a.y) * t;
            return {2, res};
        }

        //判断点在线段上
        constexpr bool pointOnSeg(const Point &p) const {
            return sgn((a - p) ^ (b - p)) == 0 &&
                   sgn((p.x - a.x) * (p.x - b.x)) <= 0 &&
                   sgn((p.y - a.y) * (p.y - b.y)) <= 0;
        }

        //判断线段是否相交
        //返回1表示相交,0表示不相交
        constexpr bool seg_inter_seg(const Seg &l) const {
            auto [res, intersectionPoint] = *this & l;
            return res == 2 && pointOnSeg(intersectionPoint) && l.pointOnSeg(intersectionPoint);
        }

        //判断直线与线段l是否相交
        //返回1表示相交,0表示不相交
        constexpr bool line_inter_seg(const Seg &l) const {
            auto [res, intersectionPoint] = *this & l;
            return res == 2 && l.pointOnSeg(intersectionPoint);
        }

        //求点到直线的距离
        //返回点到直线上最近的点，垂足
        constexpr Point pointToLine(const Point &p) const {
            Point res;
            double t = ((p - a) * (b - a)) / ((b - a) * (b - a));
            res.x = a.x + (b.x - a.x) * t;
            res.y = a.y + (b.y - a.y) * t;
            return res;
        }

        constexpr double distance(const Point &p) const {
            return p.distance(pointToLine(p));
        }

        constexpr double distance(const Line &l) const {
            auto [result, intersectionPoint] = *this & l;
            if (result != 1) {
                return 0;
            } else {
                return distance(l.a);
            }
        }

        //判断点在直线上
        constexpr bool pointOnLine(const Point &p) const {
            return sgn(pointToLine(p).distance(p)) == 0;
        }

        //求点到线段的距离
        //返回点到线段最近的点
        constexpr Point nearestPointToSeg(const Point &p) const {
            Point res;
            double t = ((p - a) * (b - a)) / ((b - a) * (b - a));
            if (t >= 0 && t <= 1) {
                res.x = a.x + (b.x - a.x) * t;
                res.y = a.y + (b.y - a.y) * t;
            } else {
                if (p.distance(a) < p.distance(b))
                    res = a;
                else
                    res = b;
            }
            return res;
        }

    };

    using Seg = Line;

    //计算多边形面积
    constexpr static double calcArea(const vector<Point> &p) {
        double res = 0;
        for (int i = 0; i < p.size(); i++) {
            res += (p[i] ^ p[(i + 1) % p.size()]) / 2;
        }
        return res;
    }

    //对点p极角排序，按逆时针排序
    class AngleSort {
    public:
        Point p;

        AngleSort() : p() {}

        explicit AngleSort(const Point &p) : p(p) {}

        bool operator()(const Point &a, const Point &b) const {
            if (a.x >= 0 && b.x < 0)
                return true;
            if (a.x == 0 && b.x == 0)
                return a.y > b.y;
            //向量OA和向量OB的叉积
            double det = (a - p) ^ (b - p);
            if (det < 0)
                return true;
            if (det > 0)
                return false;
            //向量OA和向量OB共线，以距离判断大小
            return a.distance(p) > b.distance(p);
        }
    };

    //判断点在凸多边形内
    //要求
    // 点形成一个凸包，而且按逆时针排序
    // 如果是顺时针把里面的 <0 改为 >0
    // 点的编号:0~n-1
    //返回值：
    // -1:点在凸多边形外
    // 0:点在凸多边形边界上
    // 1:点在凸多边形内
    constexpr static int pointInConvexPoly(const Point &a, const vector<Point> &p) {
        int n = p.size();
        for (int i = 0; i < n; i++) {
            if (sgn((p[i] - a) ^ (p[(i + 1) % n] - a)) < 0)
                return -1;
            else if (Seg(p[i], p[(i + 1) % n]).pointOnSeg(a))
                return 0;
        }
        return 1;
    }

    //判断点是否在凸包内
    constexpr static bool pointInConvex(const Point &a, const vector<Point> &p) {
        int l = 1, r = p.size() - 2;
        while (l <= r) {
            int mid = (l + r) >> 1;
            double a1 = (p[mid] - p[0]) ^ (a - p[0]);
            double a2 = (p[mid + 1] - p[0]) ^ (a - p[0]);
            if (a1 >= 0 && a2 <= 0) {
                if (((p[mid + 1] - p[mid]) ^ (a - p[mid])) >= 0)
                    return true;
                return false;
            } else if (a1 < 0)
                r = mid - 1;
            else
                l = mid + 1;
        }
        return false;
    }

    //判断点在任意多边形内
    //射线法，poly[]的顶点数要大于等于3,点的编号0~n-1
    //返回值
    // -1:点在凸多边形外
    // 0:点在凸多边形边界上
    // 1:点在凸多边形内
    static int PointInPoly(const Point &p, const vector<Point> &poly) {
        int n = poly.size();
        int cnt;
        Line ray, side;
        cnt = 0;
        ray.a = p;
        ray.b.y = p.y;
        ray.b.x = -100000000000.0; //-INF,注意取值防止越界
        for (int i = 0; i < n; i++) {
            side.a = poly[i];
            side.b = poly[(i + 1) % n];

            if (side.pointOnSeg(p))
                return 0;

            //如果平行轴则不考虑
            if (sgn(side.a.y - side.b.y) == 0) {
                continue;
            }

            if (ray.pointOnSeg(side.a)) {
                if (sgn(side.a.y - side.b.y) > 0) {
                    cnt++;
                }
            } else if (ray.pointOnSeg(side.b)) {
                if (sgn(side.b.y - side.a.y) > 0) {
                    cnt++;
                }
            } else if (ray.seg_inter_seg(side)) {
                cnt++;
            }
        }
        if (cnt % 2 == 1)
            return 1;
        else
            return -1;
    }

    //判断凸多边形
    //允许共线边
    //点可以是顺时针给出也可以是逆时针给出
    constexpr static bool isConvex(const vector<Point> &poly) {
        int n = poly.size();
        bitset<3> s;
        for (int i = 0; i < n; i++) {
            s[sgn((poly[(i + 1) % n] - poly[i]) ^ (poly[(i + 2) % n] - poly[i])) + 1] = true;
            if (s[0] && s[2])
                return false;
        }
        return true;
    }

    //判断凸包是否相离
    //凸包a：n个点,凸包b：m个点
    // 凸包上的点不能出现在另一个凸包内
    // 凸包上的线段两两不能相交
    static bool isConvexHullSeparate(const vector<Point> &a, const vector<Point> &b) {
        int n = a.size(), m = b.size();
        for (int i = 0; i < n; i++)
            if (PointInPoly(a[i], b) != -1)
                return false;

        for (int i = 0; i < m; i++)
            if (PointInPoly(b[i], a) != -1)
                return false;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                Line l1 = Line(a[i], a[(i + 1) % n]);
                Line l2 = Line(b[j], b[(j + 1) % m]);
                if (l1.seg_inter_seg(l2))
                    return false;
            }
        }
        return true;
    }

}

namespace Dimension3 {
    class Point {
    public:
        typedef Point Vector;
        double x, y, z;

        constexpr Point() : x(), y(), z() {}

        constexpr Point(double x, double y, double z) : x(x), y(y), z(z) {}

        //加
        constexpr Vector operator+(const Vector &v) const {
            return {x + v.x, y + v.y, z + v.z};
        }

        //减
        constexpr Vector operator-(const Vector &v) const {
            return {x - v.x, y - v.y, z - v.z};
        }

        //点积
        constexpr double operator*(const Vector &v) const {
            return x * v.x + y * v.y + z * v.z;
        }

        //叉积
        constexpr Vector operator^(const Vector &v) const {
            return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
        }

        //数乘
        constexpr Vector operator*(double b) const {
            return {x * b, y * b, z * b};
        }

        constexpr Vector operator/(double b) const {
            return {x / b, y / b, z / b};
        }

        //等于
        constexpr bool operator==(const Vector &v) const {
            return sgn(x - v.x) == 0 && sgn(y - v.y) && sgn(z - v.z);
        }

        //绕点p逆时针旋转弧度b
        constexpr Point &rotate(double radian, const Point &p = {0, 0, 0}) {
            // 将点平移到原点
            double translatedX = x - p.x;
            double translatedY = y - p.y;
            double translatedZ = z - p.z;

            // 使用旋转矩阵进行三维旋转
            double cosTheta = cos(radian);
            double sinTheta = sin(radian);

            double newX = translatedX * cosTheta - translatedY * sinTheta;
            double newY = translatedX * sinTheta + translatedY * cosTheta;
            double newZ = translatedZ;

            // 将点平移到原始位置
            x = newX + p.x;
            y = newY + p.y;
            z = newZ + p.z;

            return *this;
        }

        //模
        constexpr double norm() const {
            return sqrt(*this * *this);
        }

        //点距
        constexpr double distance(const Point &p) const {
            return (*this - p).norm();
        }

    };

    using Vector = Point;

    class Line {
    public:
        Point a, b;
        typedef Line Seg;

        constexpr Line() : a(), b() {}

        constexpr Line(const Point &a, const Point &b) : a(a), b(b) {}

        //线段长度
        constexpr double length() const {
            return (b - a).norm();
        }

        //求点到直线的距离
        //返回点到直线上最近的点，垂足
        constexpr Point pointToLine(const Point &p) const {
            Point direction = b - a;
            Point vector = p - a;

            // 使用向量的投影计算垂足的位置
            double t = (vector * direction) / direction.norm();
            return a + direction * (t / direction.norm());
        }

        constexpr double distance(const Point &p) const {
            return p.distance(pointToLine(p));
        }

        constexpr double distance(const Line &l) const {
            auto [result, intersectionPoint] = *this & l;
            if (result == 1) {
                return distance(l.a);
            } else if (result == 3) {
                return (a - l.a) * ((l.a - l.b) ^ (a - b)) / ((l.a - l.b) ^ (a - b)).norm();
            } else {
                return 0;
            }
        }

        //判断点在直线上
        constexpr bool pointOnLine(const Point &p) const {
            return sgn(distance(p)) == 0;
        }

        //两直线相交求交点
        //第一个值为0表示直线重合，为1表示平行,为2是相交，为3是相离
        //只有第一个值为2时，交点才有意义
        constexpr std::pair<int, Point> operator&(const Line &l) const {
            Point direction1 = b - a;
            Point direction2 = l.b - l.a;
            // 判断两直线是否平行
            Point crossProduct = direction1 ^ direction2;
            if (sgn(crossProduct.norm()) == 0) {
                // 平行或重合
                if (pointOnLine(l.a) && pointOnLine(l.b)) {
                    // 重合
                    return {0, Point()};
                } else {
                    // 平行
                    return {1, Point()};
                }
            }

            // 计算参数 t1 和 t2，使得两直线上的点满足参数方程
            double t1 = ((l.a - a) ^ direction2).norm() / crossProduct.norm();
            double t2 = ((a - l.a) ^ direction1).norm() / crossProduct.norm();
            // 计算交点
            Point intersectionPoint = a + direction1 * t1;
            if (!pointOnLine(intersectionPoint) || !l.pointOnLine(intersectionPoint)) {
                return {3, Point()};
            }
            return {2, intersectionPoint};
        }

        // 判断点p是否在线段上
        constexpr bool pointOnSeg(const Point &p) const {

            // 判断点到线段两端点的投影是否在线段上，且点到线段两端点的距离之和等于线段的长度
            return pointOnLine(p) && p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x) && p.y >= min(a.y, b.y) &&
                   p.y <= max(a.y, b.y) && p.z >= min(a.z, b.z) && p.z <= max(a.z, b.z);
        }

        // 判断线段是否相交
        constexpr bool seg_inter_seg(const Seg &l) const {
            auto [result, intersectionPoint] = *this & l;

            if (result == 2) {
                // 两线段相交，再判断交点是否在两线段上
                return l.pointOnSeg(intersectionPoint) && pointOnSeg(intersectionPoint);
            }

            return false;
        }

        //判断直线与线段l是否相交
        constexpr bool line_inter_seg(const Seg &l) const {
            auto [result, intersectionPoint] = *this & l;

            if (result == 2) {
                // 两线段相交，再判断交点是否在线段上
                return l.pointOnSeg(intersectionPoint);
            }

            return false;
        }

        // 求点到线段的距离，返回点到线段最近的点
        constexpr Point nearestPointToSeg(const Point &p) const {
            Point vectorAP = p - a;
            Point vectorAB = b - a;

            // 计算点到线段的投影位置
            double t = (vectorAP * vectorAB) / vectorAB.norm();

            // 如果投影位置小于等于0，则最近的点是线段的起点a
            if (sgn(t) <= 0) {
                return a;
            }

            // 如果投影位置大于等于线段长度，则最近的点是线段的终点b
            if (sgn(t - vectorAB.norm()) >= 0) {
                return b;
            }

            // 否则，最近的点是线段上的投影点
            return a + vectorAB * (t / vectorAB.norm());
        }
    };

    class Plane {
    public:
        Point a, b, c;

        // 无参构造函数
        constexpr Plane() : a(), b(), c() {}

        // 有参构造函数
        constexpr Plane(const Point &a, const Point &b, const Point &c) : a(a), b(b), c(c) {}

        // 面到点的距离
        constexpr double distance(const Point &p) const {
            Point normal = (b - a) ^ (c - a);
            double d = -normal.x * a.x - normal.y * a.y - normal.z * a.z;
            return abs(normal.x * p.x + normal.y * p.y + normal.z * p.z + d) / normal.norm();
        }

        // 面到线的距离
        constexpr double distance(const Line &l) const {
            auto [res, intersectionPoint] = intersectWithLine(l);
            if (res != 0) {
                return 0;
            } else {
                return distance(l.a);
            }
        }

        // 面到面的距离
        constexpr double distance(const Plane &p) const {
            auto [res, intersectionPoint] = intersectWithPlane(p);
            if (res != 0) {
                return 0;
            } else {
                return distance(p.a);
            }
        }

        // 面和线的交点
        constexpr pair<int, Point> intersectWithLine(const Line &line) const {
            Point normal = (b - a) ^ (c - a);

            // 如果线和面平行，返回空点
            if (sgn((normal * (line.b - line.a)) == 0)) {
                return {0, Point()};
            }

            // 计算交点
            double t = -((normal.x * (line.a.x - a.x) + normal.y * (line.a.y - a.y) + normal.z * (line.a.z - a.z)) /
                         (normal * (line.b - line.a)));
            return {1, line.a + (line.b - line.a) * t};
        }

        // 面和面的交线，0为不存在，1为存在
        constexpr std::pair<int, Line> intersectWithPlane(const Plane &other) const {
            Point normal1 = (b - a) ^ (c - a);
            Point normal2 = (other.b - other.a) ^ (other.c - other.a);
            Point direction = normal1 ^ (normal2);

            // 如果两平面平行，返回空线段
            if (sgn(direction.norm()) == 0) {
                return {0, Line()};
            }

            // 选择交线上的一点
            Point pointOnLine = a;

            // 计算交线的方向
            Point lineDirection = normal1 ^ (direction);

            // 计算交线的终点
            Point endPoint = pointOnLine + lineDirection;

            return {1, Line(pointOnLine, endPoint)};
        }

    };
}