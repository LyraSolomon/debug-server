import java.io.IOException;
import java.nio.charset.*;
import java.nio.file.*;


public class Pages {
	public static String loadFromFile(String fileName) throws IOException
	{
		String[] lines = Files.readAllLines(Paths.get(fileName), Charset.defaultCharset()).toArray(new String[1]);
		String retval="";
		for(int i=0; i<lines.length; i++) retval+=lines[i];
		return retval;
	}
}
