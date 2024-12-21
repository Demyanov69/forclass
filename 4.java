import java.util.Comparator;

public class Flight {
    private String flightNumber;
    private String departure;
    private String arrival;
    private int travelTime;
    private int distance;
    private String aircraftType;
    private double ticketPrice;

    Flight(String flightNumber, String departure, String arrival, int travelTime, int distance, String aircraftType, double ticketPrice) {
        this.flightNumber = flightNumber;
        this.departure = departure;
        this.arrival = arrival;
        this.travelTime = travelTime;
        this.distance = distance;
        this.aircraftType = aircraftType;
        this.ticketPrice = ticketPrice;
    }

    String getFlightNumber() {
        return flightNumber;
    }

    String getDeparture() {
        return departure;
    }

    String getArrival() {
        return arrival;
    }

    int getTravelTime() {
        return travelTime;
    }

    int getDistance() {
        return distance;
    }

    String getAircraftType() {
        return aircraftType;
    }

    double getTicketPrice() {
        return ticketPrice;
    }

    void setFlightNumber(String flightNumber) {
        this.flightNumber = flightNumber;
    }

    void setDeparture(String departure) {
        this.departure = departure;
    }

    void setArrival(String arrival) {
        this.arrival = arrival;
    }

    void setTravelTime(int travelTime) {
        this.travelTime = travelTime;
    }

    void setDistance(int distance) {
        this.distance = distance;
    }

    void setAircraftType(String aircraftType) {
        this.aircraftType = aircraftType;
    }

    void setTicketPrice(double ticketPrice) {
        this.ticketPrice = ticketPrice;
    }

    public String toString() {
        return "Рейс: " + flightNumber + ", Отправление: " + departure + ", Прибытие: " + arrival +
                ", Время в пути: " + travelTime + " часов, Расстояние: " + distance + " км, Тип самолета: " +
                aircraftType + ", Цена билета: " + ticketPrice + " руб.";
    }
    public static Comparator<Flight> travelTimeComparator = new Comparator<Flight>() {
        public int compare(Flight f1, Flight f2) {
            return Double.compare(f1.getTravelTime(), f2.getTravelTime());
        }
    };

}
import java.util.ArrayList;
public class FlightGroup {
    ArrayList<Flight> flights;

    FlightGroup() {
        flights = new ArrayList<Flight>();
    }

    void addFlight(Flight f) {
        flights.add(f);
    }

    void print() {
        System.out.println("Список рейсов:");
        for (int i = 0; i < flights.size(); i++) {
            System.out.println(flights.get(i).toString());
        }
    }

    ArrayList<Flight> searchByDepartureAndAircraft(String departure, String aircraftType) {
        ArrayList<Flight> found = new ArrayList<>();
        for (int i = 0; i < flights.size(); i++) {
            Flight flight = flights.get(i);
            if (departure.equals(flight.getDeparture()) && aircraftType.equals(flight.getAircraftType())) {
                found.add(flight);
            }
        }
        return found;
    }

    double calculateAverageTravelTime() {
        double totalTime = 0;
        for (int i = 0; i < flights.size(); i++) {
            totalTime += flights.get(i).getTravelTime();
        }
        return totalTime / flights.size();
    }

    void sortByTravelTime() {
        flights.sort(Flight.travelTimeComparator);
    }
}
import java.util.ArrayList;

public class FlightGroupMain {
    public static void main(String[] args) {
        FlightGroup group = new FlightGroup();
        group.addFlight(new Flight("Рейс 101", "Москва", "Санкт-Петербург", 15, 650, "Боинг 737", 5000));
        group.addFlight(new Flight("Рейс 102", "Москва", "Казань", 12, 800, "А320", 4500));
        group.addFlight(new Flight("Рейс 103", "Москва", "Сочи", 20, 1400, "Боинг 747", 8000));
        group.addFlight(new Flight("Рейс 104", "Москва", "Екатеринбург", 29, 1400, "А320", 6000));
        group.addFlight(new Flight("Рейс 102", "Москва", "Рязань", 25, 1000, "А320", 4500));

        group.print();

        System.out.println("Среднее время в пути: " + group.calculateAverageTravelTime() + " ч");

        System.out.println("\nРейсы из Москвы, выполняемые типом самолета 'А320', время в пути больше среднего:");
        ArrayList<Flight> filteredFlights = group.searchByDepartureAndAircraft("Москва", "А320");
        ArrayList<Flight> longFlights = new ArrayList<>();
        double averageTime = group.calculateAverageTravelTime();
        for (int i = 0; i < filteredFlights.size(); i++) {
            Flight flight = filteredFlights.get(i);
            if (flight.getTravelTime() > averageTime) {
                longFlights.add(flight);
            }
        }


        longFlights.sort(Flight.travelTimeComparator);
        for (int i = 0; i < longFlights.size(); i++) {
            System.out.println(longFlights.get(i));
        }

    }
}
