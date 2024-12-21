import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.util.ArrayList;

public class FlightGroupPanel extends JPanel {
    public JTextField flightNumberField = new JTextField(20);
    public JTextField departureField = new JTextField(20);
    public JTextField arrivalField = new JTextField(20);
    public JTextField travelTimeField = new JTextField(10);
    public JTextField distanceField = new JTextField(10);
    public JTextField aircraftTypeField = new JTextField(20);
    public JTextField ticketPriceField = new JTextField(10);
    public JButton addButton = new JButton("Добавить");
    public JButton sortTravelTimeButton = new JButton("Сортировать");
    public JButton displayFlightsButton = new JButton("Вывести рейсы");
    public JButton averageTravelTimeButton = new JButton("Среднее время");
    public JTextArea flightTextArea = new JTextArea(10, 30);
    private FlightGroup group;
    private ArrayList<Flight> flights;

    FlightGroupPanel(FlightGroup group) {
        this.group = group;
        this.flights = group.flights;
        setLayout(new BorderLayout());
        JPanel inputPanel = new JPanel(new GridLayout(8, 2));
        inputPanel.add(new JLabel("Номер рейса:"));
        inputPanel.add(flightNumberField);
        inputPanel.add(new JLabel("Отправление:"));
        inputPanel.add(departureField);
        inputPanel.add(new JLabel("Прибытие:"));
        inputPanel.add(arrivalField);
        inputPanel.add(new JLabel("Время в пути:"));
        inputPanel.add(travelTimeField);
        inputPanel.add(new JLabel("Расстояние:"));
        inputPanel.add(distanceField);
        inputPanel.add(new JLabel("Тип самолета:"));
        inputPanel.add(aircraftTypeField);
        inputPanel.add(new JLabel("Цена билета:"));
        inputPanel.add(ticketPriceField);
        add(inputPanel, BorderLayout.NORTH);
        JPanel buttonPanel = new JPanel(new FlowLayout());
        buttonPanel.add(addButton);
        buttonPanel.add(sortTravelTimeButton);
        buttonPanel.add(displayFlightsButton);
        buttonPanel.add(averageTravelTimeButton);
        add(buttonPanel, BorderLayout.SOUTH);
        JScrollPane scrollPane = new JScrollPane(flightTextArea);
        flightTextArea.setEditable(false);
        add(scrollPane, BorderLayout.CENTER);

        addButton.addActionListener(this::addFlight);
        sortTravelTimeButton.addActionListener(this::sortByTravelTime);
        displayFlightsButton.addActionListener(this::displayFlights);
        averageTravelTimeButton.addActionListener(this::displayAverageTravelTime);

        group.addFlight(new Flight("Рейс 101", "Москва", "Санкт-Петербург", 15, 650, "Боинг 737", 5000));
        group.addFlight(new Flight("Рейс 102", "Москва", "Казань", 12, 800, "А320", 4500));
        group.addFlight(new Flight("Рейс 103", "Москва", "Сочи", 20, 1400, "Боинг 747", 8000));
        group.addFlight(new Flight("Рейс 104", "Москва", "Екатеринбург", 29, 1400, "А320", 6000));
        group.addFlight(new Flight("Рейс 105", "Москва", "Рязань", 25, 1000, "А320", 4500));

        updateList();
    }

    void updateText(String text) {
        flightTextArea.setText(text);
    }

    void clearFields() {
        flightNumberField.setText("");
        departureField.setText("");
        arrivalField.setText("");
        travelTimeField.setText("");
        distanceField.setText("");
        aircraftTypeField.setText("");
        ticketPriceField.setText("");
    }

    private void addFlight(ActionEvent e) {
        String flightNumber = flightNumberField.getText();
        String departure = departureField.getText();
        String arrival = arrivalField.getText();
        int travelTime = Integer.parseInt(travelTimeField.getText());
        int distance = Integer.parseInt(distanceField.getText());
        String aircraftType = aircraftTypeField.getText();
        double ticketPrice = Double.parseDouble(ticketPriceField.getText());

        Flight flight = new Flight(flightNumber, departure, arrival, travelTime, distance, aircraftType, ticketPrice);
        group.addFlight(flight);
        updateList();
        clearFields();
    }

    private void sortByTravelTime(ActionEvent e) {
        group.sortByTravelTime();
        updateList();
    }

    private void displayFlights(ActionEvent e) {
        String departure = departureField.getText();
        String aircraftType = aircraftTypeField.getText();
        double averageTravelTime = group.calculateAverageTravelTime();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < flights.size(); i++) {
            Flight flight = flights.get(i);
            if (flight.getDeparture().equals(departure) && flight.getAircraftType().equals(aircraftType)
                    && flight.getTravelTime() > averageTravelTime) {
                sb.append(flight.toString()).append("\n");
            }
        }
        updateText(sb.toString());
    }

    private void displayAverageTravelTime(ActionEvent e) {
        double averageTravelTime = group.calculateAverageTravelTime();
        updateText("Среднее время в пути: " + averageTravelTime + " часов");
    }

    private void updateList() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < flights.size(); i++) {
            sb.append(flights.get(i).toString()).append("\n");
        }
        updateText(sb.toString());
    }
}
import javax.swing.*;

public class FlightGroupApp extends JFrame {
    public FlightGroupApp() {
        FlightGroup group = new FlightGroup();
        FlightGroupPanel panel = new FlightGroupPanel(group);
        add(panel);
        setTitle("Группа Рейсов");
        setSize(600, 400);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
public class FlightGroupPanelMain {
    public static void main(String[] args) {
        FlightGroupApp app = new FlightGroupApp();
    }
}
