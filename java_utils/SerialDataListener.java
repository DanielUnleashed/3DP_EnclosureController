package java_utils;

import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

import com.fazecast.jSerialComm.SerialPort;

public class SerialDataListener extends Thread{

    public static boolean exitThread = false;
    public static FileWriter csvFile;

    public static String fileName;

    public static void main (String[] args) {
        System.out.println("Available devices: ");

        SerialPort[] devicePorts = SerialPort.getCommPorts();
        for (int i = 0; i < devicePorts.length; i++){
            SerialPort each_port = devicePorts[i];
            System.out.println("[" + i + "]: " +each_port.getSystemPortName());
        }
        System.out.print("Select a COM port: ");
        Scanner sc = new Scanner(System.in);
        int index = sc.nextInt();
        if(index > devicePorts.length){
            System.err.println("Index out of bounds");
            sc.close();
            return;
        }
        sc.close();
        
        SerialPort selectedPort = devicePorts[index];
        selectedPort.setBaudRate(9600);

        selectedPort.openPort();
        selectedPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 0, 0);

        System.out.println("****************" + selectedPort.getSystemPortName() + "****************");

        /*
        // Start routine for listening to quit message
        System.out.println("Press q to exit!");
        SerialDataListener thread = new SerialDataListener();
        thread.start();*/

        try {
            fileName = ".\\data_"+ System.currentTimeMillis() +".csv";
            csvFile = new FileWriter(fileName);
            csvFile.write("Time,Temp,DHT,TMP,Humidity,DHT_Check\n");
            csvFile.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        while(!exitThread){
            receiveDataBlock(selectedPort);
        }

        selectedPort.closePort();
    }

    public static void receiveDataBlock(SerialPort port){
        StringBuilder strInput = new StringBuilder();
        while(true){
            if(port.bytesAvailable() == 0) continue;

            byte[] input = new byte[port.bytesAvailable()];
            port.readBytes(input, input.length);
            String strIn = new String(input, StandardCharsets.UTF_8);
            strInput.append(strIn);
            if(input[input.length-1] == '\n') break;
        }

        String input = strInput.toString();
        if(!input.startsWith("Time=")) return;

        String timeStr = input.substring(6, input.indexOf(" Temp"));
        String tempStr = input.substring(input.indexOf("Temp=")+6, input.indexOf(" (DHT"));
        String dhtStr = input.substring(input.indexOf("DHT=")+5, input.indexOf(", TMP"));
        String tmpStr = input.substring(input.indexOf("TMP= ")+5, input.indexOf(") Humidity"));
        String humidityStr = input.substring(input.indexOf("Humidity= ")+10, input.indexOf(" CheckDHT="));
        String checkDHT = input.substring(input.indexOf("CheckDHT= ")+10);

        String csvString = timeStr+";"+tempStr+";"+dhtStr+";"+tmpStr+";"+humidityStr+";"+checkDHT;
        for(int i = 0; i < csvString.length(); i++){
            if(csvString.charAt(i) == '.') csvString = csvString.substring(0, i) + ',' + csvString.substring(i+1);
        }
        try {
            csvFile = new FileWriter(fileName, true);
            csvFile.append(csvString);
            System.out.println(csvString);
            csvFile.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
