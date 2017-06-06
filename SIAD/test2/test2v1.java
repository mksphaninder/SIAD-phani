import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;
import java.lang.*;


public class test2v1{

	public static void join(){
		System.out.println("join method");
	}
	
	public static void chatroom(){
		System.out.println("chat method");
	}
	public static void listofclient(){
		System.out.println("list method");
	}
	
	public static void main(String[] args) throws IOException {
		System.out.println("MyTCPServer");


	int portNumber=8123;
	int clientNumber = 0;

	//creation of a server socket
	ServerSocket serverSocket = new ServerSocket(portNumber);
	System.out.println("MyTCPServer is running at port " + serverSocket.getLocalPort());


	//System.out.println("A client is connected from IP: " + clientSocket.getInetAddress().getHostAddress());
	

	while(true){

	Socket clientSocket = serverSocket.accept();
	new TCPServerThread(clientSocket).start();

	}

	}

	}

	class TCPServerThread extends Thread {

		private Socket clientSocket= null;

		TCPServerThread(Socket clientSocket){

			super("TCPServerThread");
			this.clientSocket = clientSocket;
			}
			//new TCPClientThread(Socket).start();
			public void run(){
				try{
				BufferedReader in = new BufferedReader( new InputStreamReader(clientSocket.getInputStream()));


				String inputLine=in.readLine();
				String receivedData = inputLine;
				String input,command,response;

				while(true){
				inputLine=in.readLine();
						while(!inputLine.isEmpty()) {
						response = inputLine;
							System.out.println("receivedfrom Client");
							if(inputLine.length()<4){
								System.out.println("Incorrect command usage <join>\n<chat>\n<list>\n<>");
								response = "bad command try again later! \nusage <join>\n<chat>\n<list>\n";
								clientSocket.getOutputStream().write(response.getBytes("UTF-8"));
							}
							if (inputLine.equals("join")) {
								response = "you have joined the chat";
								clientSocket.getOutputStream().write(response.getBytes("UTF-8"));
								test2v1.join();
								//continue;
							}
							if (inputLine.equals("chat")) {
								response = "Enter your message";
								clientSocket.getOutputStream().write(response.getBytes("UTF-8"));
								test2v1.chatroom();
								//continue;
							}
							if(inputLine.equals("list")){
								response = "the List of users";
								clientSocket.getOutputStream().write(response.getBytes("UTF-8"));
								test2v1.listofclient();
								//continue;
							}
							if (inputLine.equals("exit")) {
								response = "Bye";
								clientSocket.getOutputStream().write(response.getBytes("UTF-8"));
								//clientSocket.close();
							}
							inputLine=in.readLine();
							receivedData += inputLine + "\n";
							response = "MyTCPServer\n" + (new Date()).toString() + "\n" + "You have sent: " + receivedData ;
							clientSocket.getOutputStream().write(response.getBytes("UTF-8"));
							continue;
						}

					System.out.println("A Client is sconnected");

					//System.out.println("Data received from client : " + receivedData);

					response = "MyTCPServer\n" + (new Date()).toString() + "\n" + "You have sent: " + receivedData ;
					clientSocket.getOutputStream().write(response.getBytes("UTF-8"));
					//clientSocket.getOutputStream().write(response.getBytes("usage keywords \n join \n chat message \n list of users \n exit "));
					clientSocket.close();
				}
			}
			catch (Exception e){

				System.out.println("Exception occured");

		}
	   }
}

