class Samolet {
    private String marka;
    private double obemTopl;
    private double maxDaly;

    Samolet(String marka, double obemTopl, double maxDaly) {
        this.marka = marka;
        this.obemTopl = obemTopl;
        this.maxDaly = maxDaly;
    }

    public String toString() {
        return "Марка: " + marka + "\nОбъем топливного бака: " + obemTopl + "\nМаксимальная дальность полета: " + maxDaly;
    }

    String getMarka() {
        return marka;
    }

    double getObemTopl() {
        return obemTopl;
    }

    double getMaxDaly() {
        return maxDaly;
    }

    void setObemTopl(double obemTopl) {
        this.obemTopl = obemTopl;
    }

    void setMaxDaly(double maxDaly) {
        this.maxDaly = maxDaly;
    }

    void refuel(double amount) {
        this.obemTopl += amount;
    }

    boolean canFly(double distance) {
        return distance <= maxDaly;
    }

    void fly(double distance) {
        if (canFly(distance)) {
            System.out.println("Самолет полетел на " + distance + " км.");
        } else {
            System.out.println("Недостаточно топлива для полета на " + distance + " км.");
        }
    }
    void displayInfo() {
        System.out.println(this.toString());
    }
}

class PassazhirskySamolet extends Samolet {
    private int kolMest;

    PassazhirskySamolet(String marka, double obemTopl, double maxDaly, int kolMest) {
        super(marka, obemTopl, maxDaly);
        this.kolMest = kolMest;
    }

    public String toString() {
        return super.toString() + "\nКоличество посадочных мест: " + kolMest;
    }

    int getKolMest() {
        return kolMest;
    }

    void setKolMest(int kolMest) {
        this.kolMest = kolMest;
    }

    void displayPassengerInfo() {
        System.out.println(this.toString());
    }

    void increaseSeats(int additionalSeats) {
        this.kolMest += additionalSeats;
    }

    void decreaseSeats(int removedSeats) {
        this.kolMest -= removedSeats;
    }

    boolean isFull() {
        return kolMest <= 0;
    }

    void resetSeats() {
        this.kolMest = 0;
    }
}

import java.util.Scanner;

public class ExtendsSamolet {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Введите марку самолета: ");
        String marka = sc.nextLine();
        System.out.println("Введите объем топливного бака: ");
        double obemTopl = sc.nextDouble();
        System.out.println("Введите максимальную дальность полета: ");
        double maxDaly = sc.nextDouble();
        Samolet s = new Samolet(marka, obemTopl, maxDaly);
        System.out.println("Данные самолета: ");
        s.displayInfo();

        // Заправка самолета
        System.out.println("Введите количество топлива для заправки: ");
        double fuelAmount = sc.nextDouble();
        s.refuel(fuelAmount);
        System.out.println("После заправки: ");
        s.displayInfo();

        // Проверка возможности полета
        System.out.println("Введите расстояние для полета: ");
        double distance = sc.nextDouble();
        s.fly(distance);

        System.out.println("Введите количество посадочных мест: ");
        int kolMest = sc.nextInt();
        PassazhirskySamolet ps = new PassazhirskySamolet(marka, obemTopl, maxDaly, kolMest);
        System.out.println("Данные пассажирского самолета: ");
        ps.displayPassengerInfo();

        System.out.println("Введите количество дополнительных мест: ");
        int additionalSeats = sc.nextInt();
        ps.increaseSeats(additionalSeats);
        System.out.println("Обновленные данные пассажирского самолета: ");
        ps.displayPassengerInfo();

        // Уменьшение количества мест
        System.out.println("Введите количество мест для удаления: ");
        int removedSeats = sc.nextInt();
        ps.decreaseSeats(removedSeats);
        System.out.println("Данные после уменьшения мест: ");
        ps.displayPassengerInfo();

        // Проверка, заполнен ли самолет
        if (ps.isFull()) {
            System.out.println("Самолет полностью заполнен.");
        } else {
            System.out.println("Самолет не заполнен.");
        }

        // Сброс мест
        ps.resetSeats();
        System.out.println("ОШИБКА. ОШИБКА. САМОЛЕТ ПАДАЕТ. СИДЕНЬЯ ПРЕВРАЩАЮТСЯ В РАКЕТЫ И УЛЕТАЮТ В КОСМОС!!!");
        System.out.println("Данные после сброса мест: ");
        ps.displayPassengerInfo();
    }
}
