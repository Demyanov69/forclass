class Point {
    private double x;
    private double y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getY() {
        return y;
    }

    public void setY(double y) {
        this.y = y;
    }

    public double distance(Point other) {
        return Math.sqrt(Math.pow(this.x - other.x, 2) + Math.pow(this.y - other.y, 2));
    }

    @Override
    public String toString() {
        return String.format("Point(%.2f, %.2f)", x, y);
    }
}
class Triangle {
    private Point p1;
    private Point p2;
    private Point p3;
    private final String id;
    private static int idCounter = 0; // Счетчик для генерации уникальных идентификаторов

    public Triangle(Point p1, Point p2, Point p3) {
        this.p1 = p1;
        this.p2 = p2;
        this.p3 = p3;
        this.id = "Triangle-" + (++idCounter); // Генерация уникального идентификатора
    }

    public String getId() {
        return id;
    }

    public void move(double dx, double dy) {
        this.p1 = new Point(p1.getX() + dx, p1.getY() + dy);
        this.p2 = new Point(p2.getX() + dx, p2.getY() + dy);
        this.p3 = new Point(p3.getX() + dx, p3.getY() + dy);
    }

    // Метод для проверки пересечения с другим треугольником
    public boolean collides(Triangle other) {
        // Проверяем, находится ли одна из вершин другого треугольника внутри текущего треугольника
        if (isInsideTriangle(other.p1) || isInsideTriangle(other.p2) || isInsideTriangle(other.p3)) {
            return true;
        }
        // Проверяем, находится ли одна из вершин текущего треугольника внутри другого треугольника
        if (other.isInsideTriangle(this.p1) || other.isInsideTriangle(this.p2) || other.isInsideTriangle(this.p3)) {
            return true;
        }
        // Проверяем пересечение сторон треугольников
        return edgesIntersect(this.p1, this.p2, other.p1, other.p2) ||
                edgesIntersect(this.p1, this.p2, other.p2, other.p3) ||
                edgesIntersect(this.p1, this.p2, other.p3, other.p1) ||
                edgesIntersect(this.p2, this.p3, other.p1, other.p2) ||
                edgesIntersect(this.p2, this.p3, other.p2, other.p3) ||
                edgesIntersect(this.p2, this.p3, other.p3, other.p1) ||
                edgesIntersect(this.p3, this.p1, other.p1, other.p2) ||
                edgesIntersect(this.p3, this.p1, other.p2, other.p3) ||
                edgesIntersect(this.p3, this.p1, other.p3, other.p1);
    }

    // Метод для проверки, находится ли точка внутри треугольника
    private boolean isInsideTriangle(Point p) {
        double area = getArea(p1, p2, p3);
        double area1 = getArea(p, p2, p3);
        double area2 = getArea(p1, p, p3);
        double area3 = getArea(p1, p2, p);
        return Math.abs(area - (area1 + area2 + area3)) < 1e-10; // Используем небольшую погрешность
    }

    // Метод для вычисления площади треугольника
    private double getArea(Point a, Point b, Point c) {
        return Math.abs((a.getX() * (b.getY() - c.getY()) +
                b.getX() * (c.getY() - a.getY()) +
                c.getX() * (a.getY() - b.getY())) / 2.0);
    }

    // Метод для проверки пересечения двух отрезков
    private boolean edgesIntersect(Point a1, Point a2, Point b1, Point b2) {
        return orientation(a1, a2, b1) != orientation(a1, a2, b2) &&
                orientation(b1, b2, a1) != orientation(b1, b2, a2);
    }

    // Метод для определения ориентации трех точек
    private int orientation(Point p, Point q, Point r) {
        double val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
                (q.getX() - p.getX()) * (r.getY() - q.getY());
        if (val == 0) return 0; // Коллинеарные
        return (val > 0) ? 1 : 2; // 1 - по часовой стрелке, 2 - против часовой стрелки
    }


    @Override
    public String toString() {
        return String.format("Triangle(%s, %s, %s)", p1, p2, p3);
    }
}
class Pentagon {
    Point[] points;
    private final String id;
    private static int idCounter = 0; // Счетчик для генерации уникальных идентификаторов

    public Pentagon(Point[] points) {
        if (points.length != 5) {
            throw new IllegalArgumentException("Пятиугольник должен иметь 5 вершин");
        }
        this.points = points;
        this.id = "Pentagon-" + (++idCounter); // Генерация уникального идентификатора
    }

    public String getId() {
        return id;
    }

    public void move(double dx, double dy) {
        for (Point point : points) {
            point.setX(point.getX() + dx);
            point.setY(point.getY() + dy);
        }
    }

    // Метод для проверки пересечения с другим пятиугольником
    public boolean collides(Pentagon other) {
        // Проверяем пересечение сторон текущего пятиугольника с сторонами другого пятиугольника
        for (int i = 0; i < 5; i++) {
            Point a1 = this.points[i];
            Point a2 = this.points[(i + 1) % 5]; // Следующая точка, с учетом цикличности
            for (int j = 0; j < 5; j++) {
                Point b1 = other.points[j];
                Point b2 = other.points[(j + 1) % 5]; // Следующая точка, с учетом цикличности
                if (edgesIntersect(a1, a2, b1, b2)) {
                    return true; // Если стороны пересекаются, возвращаем true
                }
            }
        }

        // Проверяем, находится ли хотя бы одна из вершин другого пятиугольника внутри текущего пятиугольника
        for (Point point : other.points) {
            if (isInsidePentagon(point)) {
                return true;
            }
        }

        // Проверяем, находится ли хотя бы одна из вершин текущего пятиугольника внутри другого пятиугольника
        for (Point point : this.points) {
            if (other.isInsidePentagon(point)) {
                return true;
            }
        }

        return false; // Если ничего не пересекается, возвращаем false
    }

    // Метод для проверки, находится ли точка внутри пятиугольника
    private boolean isInsidePentagon(Point p) {
        int intersections = 0;
        for (int i = 0; i < 5; i++) {
            Point a1 = points[i];
            Point a2 = points[(i + 1) % 5];
            if (doIntersect(a1, a2, p, new Point(Double.MAX_VALUE, p.getY()))) {
                intersections++;
            }
        }
        return (intersections % 2) == 1; // Если количество пересечений нечетное, точка внутри
    }

    // Метод для проверки пересечения двух отрезков
    private boolean edgesIntersect(Point a1, Point a2, Point b1, Point b2) {
        return orientation(a1, a2, b1) != orientation(a1, a2, b2) &&
                orientation(b1, b2, a1) != orientation(b1, b2, a2);
    }

    // Метод для определения ориентации трех точек
    private int orientation(Point p, Point q, Point r) {
        double val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
                (q.getX() - p.getX()) * (r.getY() - q.getY());
        if (val == 0) return 0; // Коллинеарные
        return (val > 0) ? 1 : 2; // 1 - по часовой стрелке, 2 - против часовой стрелки
    }

    // Метод для проверки пересечения отрезков
    private boolean doIntersect(Point p1, Point q1, Point p2, Point q2) {
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        // Общий случай
        if (o1 != o2 && o3 != o4) {
            return true;
        }

        return false; // Не пересекаются
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Pentagon(");
        for (Point point : points) {
            sb.append(point).append(", ");
        }
        sb.setLength(sb.length() - 2); // Удаляем последнюю запятую и пробел
        sb.append(")");
        return sb.toString();
    }
}
public class FigureComparator<T1, T2> {

    public boolean intersects(T1 first, T2 second) {
        if (first instanceof Triangle t1 && second instanceof Pentagon p2) {
            return t1.collides(new Triangle(p2.points[0], p2.points[1], p2.points[2])) ||
                    t1.collides(new Triangle(p2.points[1], p2.points[2], p2.points[3])) ||
                    t1.collides(new Triangle(p2.points[2], p2.points[3], p2.points[4])) ||
                    t1.collides(new Triangle(p2.points[3], p2.points[4], p2.points[0])) ||
                    t1.collides(new Triangle(p2.points[4], p2.points[0], p2.points[1]));
        } else if (first instanceof Pentagon p1 && second instanceof Triangle t2) {
            return intersects((T1) t2, (T2) p1);
        } else if (first instanceof Triangle t1 && second instanceof Triangle t2) {
            return t1.collides(t2);
        } else if (first instanceof Pentagon p1 && second instanceof Pentagon p2) {
            return p1.collides(p2);
        }
        return false;
    }

    public void move(Object figure, double dx, double dy) {
        if (figure instanceof Triangle t) {
            t.move(dx, dy);
        } else if (figure instanceof Pentagon p) {
            p.move(dx, dy);
        }
    }
}
public class Main {
    public static void main(String[] args) {
        // Создание точек для треугольника
        Point p1 = new Point(0, 0);
        Point p2 = new Point(3, 0);
        Point p3 = new Point(1.5, 2);
        Triangle triangle = new Triangle(p1, p2, p3);

        // Создание точек для пятиугольника
        Point[] pentagonPoints = {
                new Point(1, 1),
                new Point(2, 3),
                new Point(4, 2),
                new Point(3, 0),
                new Point(2, 0)
        };
        Pentagon pentagon = new Pentagon(pentagonPoints);

        // Создание второго треугольника
        Point p4 = new Point(4, 3);
        Point p5 = new Point(6, 3);
        Point p6 = new Point(5, 5);
        Triangle triangle2 = new Triangle(p4, p5, p6);

        // Создание второго пятиугольника
        Point[] pentagonPoints2 = {
                new Point(0, 0),
                new Point(1, 2),
                new Point(3, 1),
                new Point(2, -1),
                new Point(0, -1)
        };
        Pentagon pentagon2 = new Pentagon(pentagonPoints2);

        // Создание экземпляра FigureComparator
        FigureComparator<Object, Object> comparator = new FigureComparator<>();

        // Проверка пересечения треугольника и пятиугольника
        boolean intersects = comparator.intersects(triangle, pentagon);
        System.out.println("Пересекаются ли треугольник и пятиугольник? " + intersects);

        // Проверка пересечения двух треугольников
        boolean intersectsTriangles = comparator.intersects(triangle, triangle2);
        System.out.println("Пересекаются ли два треугольника? " + intersectsTriangles);

        // Проверка пересечения двух пятиугольников
        boolean intersectsPentagons = comparator.intersects(pentagon, pentagon2);
        System.out.println("Пересекаются ли два пятиугольника? " + intersectsPentagons);

        // Перемещение треугольника
        comparator.move(triangle, 1, 1);
        System.out.println("Треугольник после перемещения: " + triangle);

        // Перемещение пятиугольника
        comparator.move(pentagon, -1, -1);
        System.out.println("Пятиугольник после перемещения: " + pentagon);
    }
}
