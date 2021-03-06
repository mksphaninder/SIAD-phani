import java.io.*;
import java.net.*;
public class	NewtcpClient{
	public static void main(String[] args) throws IOException {
		if(args.length != 2)
		{
			System.err.println("usage: java newtcpClient <hostname> <portnumber>");
			System.exit(1);
		}
		
		String hostname = args[0];
		int portnumber = Integer.parseInt(args[1]);
		try{
			Socket socket = new Socket(hostname, portnumber);
			System.out.println("connected to the server\""+hostname+"\'at port" +portnumber);
			// print formatted representation of objects to a text output stream
			PrintWriter out = new PrintWriter(socket.getOutputStream(),true);
			new TCPClientThread(socket).start();
			//buffered reader to read from user
			BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
			String userInput;
			while((userInput = stdIn.readLine()) != null)
			{
				out.println(userInput);
				System.out.println("Received from Server:"+ stdIn.readLine());
				String message = stdIn.readLine();
				if(message.equals("exit"))
				{
					socket.close();
					System.exit(0);
				}
			}
		}
		
		catch(UnknownHostException e){
			System.err.println("Don't know about the host" +hostname);
			System.exit(1);
			}
		catch(IOException e){
			System.err.println("culdn't get to the I/O connection to " +hostname);
			
			System.exit(1);
			}
		}
	}
class TCPClientThread extends Thread{
	private Socket clientSocket = null;
	TCPClientThread(Socket clientSocket) {
	super("TCPClientThread");
	this.clientSocket = clientSocket;
	}
	public void run(){
		try{
			BufferedReader in = new BufferedReader(
			new InputStreamReader(clientSocket.getInputStream()));
			while(true){
				String inputLine = in.readLine();
				while((inputLine!= null) && !inputLine.isEmpty())
					{
						System.out.println("received from Client:" + inputLine);
						inputLine = in.readLine();
					}
				}
			}
			catch(IOException e){
				e.printStackTrace();
			}
		}
	}
						
