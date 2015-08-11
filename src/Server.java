import java.io.*;
import java.net.*;
import java.util.*;

public class Server implements Runnable{
	Thread t;
	public Server()
	{
		t=new Thread(this);
		t.start();
	}
	
	@SuppressWarnings("resource")
	@Override
	public void run() {
		ServerSocket s;

		System.out.println("Webserver starting up on port 80");
		System.out.println("(press ctrl-c to exit)");
		try {
			// create the main server socket
			s = new ServerSocket(80);
		} catch (Exception e) {
			System.out.println("Error: " + e);
			return;
		}
		Pages.init();
		System.out.println("Waiting for connection");
		for (;;) {
			try {
				// wait for a connection
				Socket remote = s.accept();
				// remote is now the connected socket
				BufferedReader in = new BufferedReader(new InputStreamReader(remote.getInputStream()));
				PrintWriter out = new PrintWriter(remote.getOutputStream());
				String []strings = null;
				try{strings=splitReq(in.readLine());}
				catch(Exception e)
				{
					out.println(e.toString().substring(21));
					out.println();
					out.println(e.toString().substring(21));
					out.flush();
					remote.close();
				}
				String URL="";
				try
				{
					URL=strings[0].substring(1);
				}
				catch(NullPointerException e)
				{
					out.println("HTTP/1.1 400 Bad Request");
					out.println("Please fill out all parts of the form");
					continue;
				}
				HashMap<String, String> vars=new HashMap<String, String>();
				for(int i=1; i<strings.length-1; i+=2)
				{
					vars.put(strings[i], strings[i+1]);
				}
				String response="";
				try
				{
					response=Pages.get(URL, vars);
					out.println("HTTP/1.1 200 OK");
					out.println("");
					out.println(response);
				}
				catch(IOException e)
				{
					out.println("HTTP/1.1 404 Not Found");
					out.println("");
					out.println("Error 404: resource not found.");
				}
				out.flush();
				remote.close();
			} catch (Exception e) {
				System.out.println("Error: " + e);
				e.printStackTrace();
			}
		}
	}

	private String[] splitReq(String str) throws Exception {
		StringTokenizer tokenizer=new StringTokenizer(str, " ");
		ArrayList<String> retval=new ArrayList<String>();
		if(!(tokenizer.countTokens()>2)) throw new Exception("HTTP/1.1 400 Bad Request");
		if(!tokenizer.nextToken().equals("GET")) throw new Exception("HTTP/1.1 501 Not Implemented");
		tokenizer=new StringTokenizer(tokenizer.nextToken(), "?");
		retval.add(tokenizer.nextToken());
		if(tokenizer.hasMoreElements())
		{
			tokenizer=new StringTokenizer(tokenizer.nextToken(), "=&");
			if(tokenizer.countTokens()%2!=0) throw new Exception("HTTP/1.1 400 Fill out all parts of the form");
			while(tokenizer.hasMoreElements()) retval.add(tokenizer.nextToken());
		}
		return retval.toArray(new String[1]);
	}
}
