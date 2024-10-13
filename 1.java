public class Point {
    private int x, y;

    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    // Определение координатной четверти
    String getQuadrant() {
        if (x > 0 && y > 0) {
            return "Первая четверть";
        } else if (x < 0 && y > 0) {
            return "Вторая четверть";
        } else if (x < 0 && y < 0) {
            return "Третья четверть";
        } else if (x > 0 && y < 0) {
            return "Четвертая четверть";
        } else {
            return "На оси координат";
        }
    }

    // Перемещение точки
    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    // Нахождение расстояния между 2 точками
    double distance(Point p) {
        int dx = x - p.getX();
        int dy = y - p.getY();
        return Math.sqrt(dx * dx + dy * dy);
    }

    // Проверка симметричности 2 точек относительно начала координат
    boolean isSymmetric(Point p) {
        return (x == -p.getX() && y == -p.getY());
    }

    void print() {
        System.out.print("Коорды: " + x + " " + y);
    }
}

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Введите координаты точки 1 (x y): ");
        int x1 = scanner.nextInt();
        int y1 = scanner.nextInt();
        Point point1 = new Point(x1, y1);

        System.out.print("Введите координаты точки 2 (x y): ");
        int x2 = scanner.nextInt();
        int y2 = scanner.nextInt();
        Point point2 = new Point(x2, y2);

        point1.print();
        System.out.println(" Четверть: " + point1.getQuadrant());
        System.out.println("Расстояние до другой точки: " + point1.distance(point2));
        System.out.println("Симметричны ли точки: " + point1.isSymmetric(point2));

        System.out.print("Введите смещение для точки 1 (dx dy): ");
        int dx = scanner.nextInt();
        int dy = scanner.nextInt();
        point1.move(dx, dy);
        point1.print();
    }
}
