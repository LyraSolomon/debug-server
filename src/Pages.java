import java.io.IOException;
import java.nio.charset.*;
import java.nio.file.*;
import java.util.Map;

import dynamicPages.*;


public class Pages {
	static DynamicPage []pages;
	public static void init()
	{
		pages=new DynamicPage[1];
		pages[0]=new Graphs();
	}
	public static String loadFromFile(String fileName) throws IOException
	{
		String[] lines = Files.readAllLines(Paths.get(fileName), Charset.defaultCharset()).toArray(new String[1]);
		String retval="";
		for(int i=0; i<lines.length; i++) retval+=lines[i]+"\n";
		return retval;
	}
	public static String get(String URL, Map<String, String> moreData) throws IOException
	{
		for(int i=0; i<pages.length; i++)
		{
			String retval=pages[i].getContent(URL, moreData);
			if (retval!=null) return retval;
		}
		return loadFromFile("site/"+URL);
	}
}
