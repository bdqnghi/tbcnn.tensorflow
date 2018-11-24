std::vector<Point> convex_hull(std::vector<Point> point) {
    std::sort(point.begin(), point.end());
    std::vector<Point> convex;
    {
        std::vector<Point> stack;
        for (int i = 0; i < (int)point.size(); ++i) {
            while ((int)stack.size() >= 2 &&
                    sgn(det(stack[(int)stack.size() - 2], stack.back(), point[i])) <= 0) {
                stack.pop_back();
            }
            stack.push_back(point[i]);
        }
        for (int i = 0; i < (int)stack.size(); ++i) {
            convex.push_back(stack[i]);
        }
    }
    {
        std::vector<Point> stack;
        for (int i = (int)point.size() - 1; i >= 0; --i) {
            while ((int)stack.size() >= 2 &&
                    sgn(det(stack[(int)stack.size() - 2], stack.back(), point[i])) <= 0) {
                stack.pop_back();
            }
            stack.push_back(point[i]);
        }
        for (int i = 1; i < (int)stack.size() - 1; ++i) {
            convex.push_back(stack[i]);
        }
    }
    return convex;
}
