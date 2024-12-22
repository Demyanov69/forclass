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
        // Реализация проверки пересечения
        return false; // Заглушка, нужно реализовать
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
        // Реализация проверки пересечения
        return false; // Заглушка, нужно реализовать
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
            // Проверка пересечения треугольника с пятиугольником
            return t1.collides(new Triangle(p2.points[0], p2.points[1], p2.points[2])) ||
                    t1.collides(new Triangle(p2.points[1], p2.points[2], p2.points[3])) ||
                    t1.collides(new Triangle(p2.points[2], p2.points[3], p2.points[4])) ||
                    t1.collides(new Triangle(p2.points[3], p2.points[4], p2.points[0])) ||
                    t1.collides(new Triangle(p2.points[4], p2.points[0], p2.points[1]));
        } else if (first instanceof Pentagon p1 && second instanceof Triangle t2) {
            // Проверка пересечения пятиугольника с треугольником
            return intersects((T1) t2, (T2) p1); // Используем ту же логику, что и выше
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

        // Создание экземпляра FigureComparator
        FigureComparator<Triangle, Pentagon> comparator = new FigureComparator<>();

        // Проверка пересечения
        boolean intersects = comparator.intersects(triangle, pentagon);
        System.out.println("Пересекаются ли фигуры? " + intersects);

        // Перемещение треугольника
        comparator.move(triangle, 1, 1);
        System.out.println("Треугольник после перемещения: " + triangle);

        // Перемещение пятиугольника
        comparator.move(pentagon, -1, -1);
        System.out.println("Пятиугольник после перемещения: " + pentagon);
    }
}
