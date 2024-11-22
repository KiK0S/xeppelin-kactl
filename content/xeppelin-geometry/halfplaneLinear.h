/**
 * Author: isaf27
 * Description: Halfplane intersection; get one point of intersection
 * Time: O(n)
 */


template <typename T>
bool intersection(const line<T>& l1, const line<T>& l2, vect<ld>& p) {
    auto pr = l1.a * l2.b - l1.b * l2.a;
    if (abs(pr) == 0) { return false; }
    auto prx = l1.b * l2.c - l1.c * l2.b;
    auto pry = l1.c * l2.a - l1.a * l2.c;
    p.x = (ld)prx / pr;
    p.y = (ld)pry / pr;
    return true;
}

// ax + by + c >= 0
template <typename T>
bool checkPlaneInt(vector<line<T>> l, vect<ld>& A) {
    shuffle(l.begin(), l.end(), rnd);
    auto f = [&](int i, const vect<ld>& a) {
        return a.x * l[i].a + a.y * l[i].b + l[i].c;
    };
    auto some_point = [&](int i) {
        if (abs(l[i].a) > abs(l[i].b)) {
            return vect<ld>(-(ld)l[i].c / l[i].a, 0.0);
        } else {
            return vect<ld>(0.0, -(ld)l[i].c / l[i].b);
        }
    };
    A = some_point(0);
    for (int i = 1; i < (int)l.size(); i++) {
        if (f(i, A) < -eps) {
            bool has_mn = false;
            bool has_mx = false;
            vect<ld> mn, mx;
            A = some_point(i);
            for (int j = 0; j < i; j++) {
                auto vj = l[j].normal();
                auto vi = l[i].normal();
                auto vec = (vj ^ vi);
                if (abs(vec) < eps) {
                    auto p = some_point(i);
                    if ((vj * vi) < -eps && f(j, p) < -eps) {
                        return false;
                    }
                } else {
                    vect<ld> cur;
                    intersection(l[i], l[j], cur);
                    if (vec < 0) {
                        if (!has_mx || f(j, mx) < 0) {
                            mx = cur;
                        }
                        has_mx = true;
                        if (has_mn && f(j, mn) < -eps) {
                            return false;
                        }
                    } else {
                        if (!has_mn || f(j, mn) < 0) {
                            mn = cur;
                        }
                        has_mn = true;
                        if (has_mx && f(j, mx) < -eps) {
                            return false;
                        }
                    }
                }
            }
            if (has_mx && has_mn) {
                if (make_pair(mx.y, mx.x) > make_pair(mn.y, mn.x)) {
                    A = mx;
                } else {
                    A = mn;
                }
            } else if (has_mx) A = mx;
            else if (has_mn) A = mn;
        }
    }
    return true;
}
