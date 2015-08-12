package dynamicPages;

import java.text.*;
import java.util.*;

public class Text extends DynamicPage {
	private ArrayList<Message> data;
	int historySize=20;
	SimpleDateFormat dateFormat=new SimpleDateFormat("HH:mm:ss.SSS");
	public Text()
	{
		data=new ArrayList<Message>();
		data.add(new Message());
		data.get(0).message="test";
		data.get(0).category="elevator";
		data.get(0).time=new Date();
		data.get(0).color="red";
	}
	@Override
	public String getContent(String URL, Map<String, String> moreData) {
		if(URL.equals("text.html"))
		{
			if(moreData.containsKey("size")) historySize=Integer.parseInt(moreData.get("size"));
			return "<!doctype html><html><head><script src=\"jquery-2.1.4.min.js\"></script>"
				+ "<script>$(function(){setInterval(function(){"
				+ "$('#include').load('dynamic_text.html');}, 300);});</script>"
				+ "<style>table, th, td { border:1px solid black; border-collapse:collapse; }"
				+ "th, td {padding:5px}</style></head>"
				+ "<body><div id=\"foo\"></div><form id=\"history\">"
				+ "history size:<input type=\"text\" name=\"size\">"
				+ "<input type=\"submit\"></input></form>"
				+ "<div id=\"include\"></div></body></html>";
		}
		if(URL.equals("add_text_data.html"))
		{
			if(moreData.containsKey("message")&&moreData.containsKey("category")&&
					moreData.containsKey("color"))
			{
				Message m=new Message();
				m.message=moreData.get("message");
				m.category=moreData.get("category");
				m.color=moreData.get("color");
				m.time=new Date();
				data.add(m);
			}
			return "<html><body><form>message:<input type=\"text\" name=\"message\" /><br />"
				+ "category:<input type=\"text\" name=\"category\" value=\""
				+ moreData.get("category")+"\" /><br />color:<input type=\"text\""
				+ "name=\"color\" value=\"black\"/><input type=\"submit\" /></form></html>";
		}
		if(URL.equals("dynamic_text.html"))
		{
			String retval="<table><tr><th>category</th><th>message</th><th>time</th></tr><br />";
			for(int i=Math.min(data.size()-1, historySize-1); i>=0; i--)
			{
				retval+="<tr style=\"color:"+data.get(i).color+";\">"
					+ "<td>["+data.get(i).category+"]</td>"
					+"<td>"+data.get(i).message+"</td><td>"
					+dateFormat.format(data.get(i).time)+"</td></tr>";
			}
			retval+="</table>";
			return retval;
		}
		return null;
	}
}

class Message {
	String message;
	String category;
	Date time;
	String color;
}