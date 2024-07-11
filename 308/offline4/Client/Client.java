package Client;

import Server.Notification;

import java.io.*;
import java.net.*;
import java.util.Scanner;

class Client implements Runnable {
    private Socket socket;
    private ObjectOutputStream outputStream;
    private ObjectInputStream inputStream;
    Scanner scn=new Scanner(System.in);
    public Client(Socket socket) {
        this.socket = socket;
        try {
            this.outputStream = new ObjectOutputStream(socket.getOutputStream());
            this.inputStream = new ObjectInputStream(socket.getInputStream());
        } catch (IOException e) {
            System.out.println(e);
        }
    }
    @Override
    public void run() {
        try {
            new Thread(() -> {
                try {
                    while (true) {
                        // Read object from the server
                        Notification notification = (Notification) inputStream.readObject();
                        System.out.println(notification.getMessage());
                    }
                } catch (IOException | ClassNotFoundException e) {
                    System.out.println(e);
                }
            }).start();

            while (true) {
                System.out.print("Enter message: ");
                String content = scn.nextLine();

                // Create a Message object and send it to the server
                Message message = new Message(content);
                outputStream.writeObject(message);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        try {
            Socket socket = new Socket("localhost", 5000);
            System.out.println("Connected to server.");
            Client client = new Client(socket);
            new Thread(client).start();
        } catch (IOException e) {
            System.out.println(e);
        }
    }
}
